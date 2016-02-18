#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void readFreq(float[], char[]);
void calcFreq(float[], char[]);
char rotate( char, int);
int findKey(float[], float[]);
void decrypt(int, char[]);

int main (int argc, char * argv[]) {
	
	//The key
	int key = 0;

	//Frequency of letters 
	float freq [26];

	//Frequency of letters in the 2 inputs
	float actualFreq [26];
	float actualFreq2[26];

	//Read in the actual freq
	readFreq(freq, "/home/olearyt/Documents/CIS/361/proj1/LetFreq.txt");

	//calculate the observed freq
	calcFreq(actualFreq, "/home/olearyt/Documents/CIS/361/proj1/test.txt");

	//find the key
	key = findKey(freq, actualFreq);

	//Print it and decrpyt it
	printf("Key is %d\n", key);

	decrypt(key, "/home/olearyt/Documents/CIS/361/proj1/test.txt");

	//Same process but with 2nd test file
	calcFreq(actualFreq2, "/home/olearyt/Documents/CIS/361/proj1/test2.txt");

        key = findKey(freq, actualFreq2);

        printf("Key is %d\n", key);

        decrypt(key, "/home/olearyt/Documents/CIS/361/proj1/test2.txt");


	/* //Tests Rotate
	char input = 'z';
	int offset = 1;
	input = rotate(input, offset);
	printf("%c\n", input);	*/

return 0;

}

// Load array given with the letter frequencies for English from file LetFreq.txt
void readFreq(float given[], char fname[]){
	FILE *file;

	char ch;
	int i = 0;

	//Open the file and make sure it worked properly
	file = fopen(fname, "r");

	if ( file == NULL){
		printf("Error reading file\n");
		exit (0);
	}

	//Test to see what the file contains
	/*	
	printf("The contents of %s file are :\n", fname);
 
 	while( ( ch = fgetc(file) ) != EOF )
      		printf("%c",ch);
	*/
	
	//scan the file data into given
	for (i = 0; i < 26; i++)
    	{
        	fscanf(file, " %c%f", &ch, &given[i]);
    	}	

	/*
	for ( i = 0; i < 26; i++){
		printf("Number is: %f\n", given[i]);
	}*/

	//close the file
	fclose(file);
}

// Read the encoded text from an input file and accumulate the letter frequency
// data for the encoded text. Store the frequency data in array found.
void calcFreq(float found[], char fname[]){
	FILE *file;

	char array[256];
	int i =0;
	float total = 0.0;
	float inputFreq[26];

	//initialize the frequencies to 0
	for ( i = 0; i < 26; i++){
		inputFreq[i] = 0;
	}

	//open the file and make sure it worked properly
	file = fopen(fname, "r");

	if ( file == NULL ) {
		printf("Error reading file\n");
		exit(0);
	}

	i = 0;
	
	//load the file data into array
	while( fscanf(file, "%c", &array[i]) != EOF){
		i++;
	}

	//Test the input message
	/*	
	i = 0;
	
	while ( array[i] != '\0') {
		printf("%c\n", array[i]);
		i++;
	}*/

	i = 0;

	//increase the counter of each found char
	while ( array[i] != '\0'){
		if(tolower(array[i]) >= 'a' && tolower(array[i]) <= 'z'){
			inputFreq[tolower(array[i]) - 'a']++;
		}
		i++;
	}

	//Test the counters
	/*
	i=0;

	while ( i != 26 ) {
		printf("%c occurs %f times\n", i+'a', inputFreq[i]);
		i++;
	}*/

	//find how many total chars there were
	for ( i = 0; i < 26; i++){
		total = total + inputFreq[i];
	}

	//get the freq of each char 
	for ( i = 0; i < 26; i++){
		found[i] = inputFreq[i]/total;
	}
	
	//Test the frequency
	/*
	for ( i = 0; i < 26; i++) {
		printf("Frequency at %c is: %f\n", i+'a', found[i]);
	}*/

	//close the file
	fclose(file);

}

// Rotate the character in parameter ch down the alphabet for the number of   
// positions as given in parameter num and return the resulting character.
char rotate ( char ch, int num) {
	if(isupper(ch)){
		ch = ch - 65;
		ch = ch + num;
		ch = ch % 26;
		ch = ch + 65;	
	}
	else {
		ch = ch - 97;
                ch = ch + num;
                ch = ch % 26;
                ch = ch + 97;
	}
	return ch;
}

// Compare the data in array found with the frequency data in array given, looking
// for a key that will give you the best match. To do this, try each of the 26 rotations
// and remember which gives the smallest difference between the frequencies you
// observed and the frequencies given. Return the key.
int findKey ( float given[], float found[]){
	//float dif[26];
	int i =0, m = 0, min = 0;;
	char ch;
	float total = 0, data = 0, prev = 100;

	//run through each rotation
	for ( i = 0; i < 26; i++){
		total = 0;
	
		//run through each char 
		for ( m = 0; m < 26; m++){
	
			//find the differences of the squares
			data = (given[m] - found[(m + i)%26]);
			data = data * data;
			total += data;
		}

	//printf("total at %d is %f\n", i, total);
		
		//find the smallest difference
		if(total < prev){
			prev = total;
			min = i;
		}
	}

	//return 26 - the smallest's index
	return 26 - min;
}

// Decrypt the encoded text in the input file using the key and display the decoded text
void decrypt (int key, char fname[]){
	FILE *file;	
	char msg[256];
	int i = 0;

	//open the file and make sure it worked properly
	file = fopen(fname, "r");

	if (file == NULL){
		printf("Error reading file");
	}

	//scan the file data into msg
	while( fscanf(file, "%c", &msg[i]) != EOF){
                i++;
        }

	//Test the input message
	i = 0;
	while ( msg[i] != '\0') {
		printf("%c", msg[i]);
		i++;
	}

	//if the char is a letter, rotate it by the key
	for ( i = 0; i < 256; i++){
		if ( isupper(msg[i]) || islower(msg[i]))
		    msg[i] = rotate(msg[i], key);
	}

	i = 0;

	//print the new message
	while(msg[i] != '\0'){
		printf("%c", msg[i]);
		i++;
	}

	printf("\n");

	//close the file
	fclose(file);
}
