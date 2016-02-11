
void readFreq(float[], char[]);
void calcFreq(float[], char[]);
char rotate( char, int);
int findKey(float[], float[]);
void decrypt(int, char[]);

int main (int argc, char * argv[]) {

return 0;

}

// Load array given with the letter frequencies for English from file LetFreq.txt
void readFreq(float given[], char fname[]){

}

// Read the encoded text from an input file and accumulate the letter frequency            // data for the encoded text. Store the frequency data in array found.
void calcFreq(float found[], char fname[]){

}

// Rotate the character in parameter ch down the alphabet for the number of   
// positions as given in parameter num and return the resulting character.
char rotate ( char ch, int num) {
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
