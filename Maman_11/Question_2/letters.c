/*
 ============================================================================
 Name        : letters.c
 Author      : Roman Chikunov
 Version     :
 Copyright   : 
 Description : This program edit text with the following rules:
 			   1. A capital letter will begin every sentence.
 			   2. Every sentence between quotes will be capitalized
 			   3. Every other letters will be lower cased. 
 			   4. Numbers shall not be printed. 
 			   5. A blank line should be printed after each input line.
 ============================================================================
 */
#include <stdio.h>
#include <ctype.h>


/* A main function that invokes letters fucntion in order 
	to edit the sentence as required*/
int main(){

	int c;

	/*states of the switch, each states validate the required 
	rules as mentioned beforehand*/
	enum status {OUT, NEW_SENTENCE, IN_QUOTES, DIGITS};

	int state = NEW_SENTENCE, buf = 0;
	
	while ((c = getchar()) != EOF){
		switch (state) {
			case OUT:
				if (c == '.'|| c == '\n') {
					putchar(c);
					if (c == '\n')
						putchar('\n');
					state = NEW_SENTENCE;
					break;
					}
				else if (isdigit(c))
					break;
				else if (isalpha(c))
					putchar(tolower(c));
				else if (c == ' ') {
					if (buf != ' ')
						putchar(c);			
					buf = c;
					break;
				}
				else if (c == '"') {
					putchar(c);
					state = IN_QUOTES;
					buf = c;
					break;
				}
				else
					putchar(c);
				buf = c;				
				break;
			
			case NEW_SENTENCE:
				if (isdigit(c))
					break;
				else if (c == '"') {
					putchar(c);
					state = IN_QUOTES;
					buf = c;
					break;
				}
				else if (c == ' ') {
					if (buf != ' ')
						putchar(c);			
					buf = c;
					break;
				}
				else if (c == '\n'){
					putchar(c);
					putchar('\n');
				}
				else {
					putchar(toupper(c));
					state = OUT;
					buf = c;
				}
				break;
			
			case IN_QUOTES:
				if (c == '"') {
					putchar(c);
					if (buf == '.')
						state = NEW_SENTENCE;
					else
						state = OUT;
					break;
				}
				else if (isdigit(c))
					break;
				else if (c == ' ') {
					if (buf != ' ')
						putchar(c);			
					buf = c;
					break;
				}
				else if (c == '\n'){
					putchar(c);
					putchar('\n');
				}
				else if (isalpha(c)) {
					putchar(toupper(c));
					buf = c;
					break;
				}
				putchar(c);
				buf = c;
				break;
		}
	}	
	return 0;
}