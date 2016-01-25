
#include <stdio.h>
#include <stdlib.h>

int found (char list[], int num, char ch);

int main ()
{
	char alp[26];
	char key[20];
	char ch = ' ';
	int i, j, size = 0;

	char rev[26] = {'z','y','x','w','v','u','t','s','r','q','p','o','n','m','l','k','j','i','h','g','f','e','d','c','b','a'};

	// read the key from the keyboard into array key
	// (length of the key is less than 20 characters
	

	while (ch=getchar(), size<20 && ch!='\n')
	   key[size++] = ch;
	

	// write code below to store the key in array alp 
	// after removing duplicate letters
	
	size = 0;

	for (i =0; i < 20; i++){
	
		ch=key[i];

		ch = (tolower(ch));

		for (j = 0; j < 26; j++) {
			
			//If the char is already in alp, stop 
			if ( ch == alp[j] ) { break; }

			//If the current spot is not empty, skip it
			if ( alp[j] != '\0' ) { /* Do nothing */ }

			else {
				alp[j] = ch;
				size++;
				break;	
			}
		}
	}

	// write code below to fill up the rest of array alp wiht
	// other characters in the alphabet in reverse order
	
	for (i = 0; i < 26; i++ ){

		ch = rev[i];

		j = found(alp, 26, ch);

		if ( j == 0) {
			alp[size] = ch;
			size++;
		}

	}

	// print characters in array alp
	
	for (i=0; i < 26; i++)
	   printf("%c", alp[i]);
	printf("\n");

	return 0;
}


// search the first num characters in array list for character ch
// return true if it is found; false otherwise

int found(char list[], int num, char ch) 
{
	int i;
	for (i=0; i<num; i++)
	   if (list[i] == ch)
	      return 1;
	return 0;
}
