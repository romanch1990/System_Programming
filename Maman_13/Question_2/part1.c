#include "permut.h"

extern char *err_msgs[];

enum status {OUT, IN_STRING, SLASH, IN_COMMENT, RIGHT_STAR, IN_CPP_COM};

/*get a file (*.c) - remove the comments and save it as the same name with 1 at the end (*.c1)  */
int part1(char *str_c) { 
	/*The input file and output file*/
	FILE *file_c, *file_c1;
	int c, state = OUT;
	
	/*The file's name with 1 at the end (*.c1)  */
	char *str_c1 = (char *) malloc (strlen(str_c) + 2);
	
	if (!str_c1) {
		fprintf(stderr, "part1: %s", err_msgs[(-1) * OUT_OF_SPACE]);
		return OUT_OF_SPACE;
	}
	
	/*str_c1 = *.c1  */
	strcpy(str_c1, str_c);
	strcat(str_c1, "1");
	
	/*open *.c */
	if (!(file_c = open_file(str_c, "r")))
		return FILE_ERROR;

	/*open *.c1 */
	if (!(file_c1 = open_file(str_c1, "w")))
		return FILE_ERROR;
	
	/*copy all the content of file_c to file_c1 except the comments*/
	while ((c = getc(file_c)) != EOF) {
		switch (state) {
			case OUT:
				if (c == '/')
					state = SLASH;
				else {
					putc(c, file_c1);
					if (c == '\"')
						state = IN_STRING;
				}
				break;
			
			case SLASH:
				if (c == '*')
					state = IN_COMMENT;
				else if (c == '/')
					state = IN_CPP_COM;
				else {
					putc('/', file_c1);
					putc(c, file_c1);
					state = OUT;
				}
				break;
				
			case IN_COMMENT:
				if (c == '*')
					state = RIGHT_STAR;
				break;
				
			case IN_CPP_COM:
				if (c == '\n') {
					state = OUT;
					putc(c, file_c1);
				}
				break;
			
			case RIGHT_STAR:
				if (c == '/')
					state = OUT;
				else if (c != '*')
					state = IN_COMMENT;
				break;
				
			case IN_STRING:
				if (c == '\"')
					state = OUT;
				putc(c, file_c1);
				break;
		}
	}
	fflush(file_c1);
	fclose(file_c);
	fclose(file_c1);
	free(str_c1);
	return SUCCESS;
}
