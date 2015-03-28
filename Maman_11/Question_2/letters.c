#include <stdio.h>
#include <ctype.h>

enum status {OUT, NEW_SENTENCE, IN_QUOTES, DIGITS};

void letters(int c) {
	int state = NEW_SENTENCE, buf = 0;
	
	while ((c = getchar()) != EOF) {
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
}



int main(){
	int c;
	
	while((c = getchar()) != EOF)
		letters(c);
	
	return 0;
}