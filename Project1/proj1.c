#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void readFreq(float[], char[]);
void calcFreq(float[], char[]);
char rotate( char, int);
int findKey(float[], float[]);
void decrypt(int, char[]);

int main (int argc, char * argv[]) {

	int i = 0;
	float freq [26];
	float found [26];
	readFreq(freq, "/home/olearyt/Documents/CIS/361/proj1/LetFreq.txt");

	calcFreq(found, "/home/olearyt/Documents/CIS/361/proj1/test.txt");

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
	
	for (i = 0; i < 26; i++)
    	{
        	fscanf(file, " %c%f", &ch, &given[i]);
    	}	

	/*
	for ( i = 0; i < 26; i++){
		printf("Number is: %f\n", given[i]);
	}*/

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

	for ( i = 0; i < 26; i++){
		inputFreq[i] = 0;
	}

	file = fopen(fname, "r");

	if ( file == NULL ) {
		printf("Error reading file\n");
		exit(0);
	}

	i = 0;
	
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

	for ( i = 0; i < 26; i++){
		total = total + inputFreq[i];
	}

	for ( i = 0; i < 26; i++){
		found[i] = inputFreq[i]/total;
	}
	
	//Test the frequency
	/*
	for ( i = 0; i < 26; i++) {
		printf("Frequency at %c is: %f\n", i+'a', found[i]);
	}*/

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
	return 0;
}

// Decrypt the encoded text in the input file using the key and display the decoded text
void decrypt (int key, char fname[]){

}
