#include "permut.h"

extern char *err_msgs[];

enum type {ENUM, MACRO};

int add_enum(char *line);
int add_macro(char *line);
void print_enum_list(void);
void print_macro_list(void);
void free_enum_list(void);
void free_macro_list(void);
int replace_enum(char *line, char *updated_line);
int replace_macro(char *line, char *updated_line);

/*get a file name (*.c but use the *.c2) - replace the macros and enums with corresponding value and save it as the same name with 3 at the end instead of 2(*.c3)
 note that you have maximum 3 parameters for each marco and maximum 9 variables for each enum */
int part3(char *str_c) {
	/*The input file and output file*/
	FILE *file_c2, *file_c3;
	
	int status;

	/*Files names (*.c2 and *.c3) */
	char	*str_c2 = (char *) malloc (strlen(str_c) + 2),
			*str_c3 = (char *) malloc (strlen(str_c) + 2),
			*line = (char *) malloc (LINE_LEN),
			*temp_line = (char *) malloc (LINE_LEN),
			*string = (char *) malloc (LINE_LEN);

	if (!str_c2 || !str_c3 || !line || !string || !temp_line) {
		fprintf(stderr, "part3: %s", err_msgs[(-1) * OUT_OF_SPACE]);
		return OUT_OF_SPACE;
	}

	/*str_c2 = *.c2  */
	strcpy(str_c2, str_c);
	strcat(str_c2, "2");
	
	/*str_c3 = *.c3  */
	strcpy(str_c3, str_c);
	strcat(str_c3, "3");
	
	/*open *.c2 */
	if (!(file_c2 = open_file(str_c2, "r")))
		return FILE_ERROR;

	/*open *.c3 */
	if (!(file_c3 = open_file(str_c3, "w")))
		return FILE_ERROR;
	
	/*read lines until its EOF*/
	while (fgets(line, LINE_LEN, file_c2)) {
		/*checks whether there is enough chars for the string "enum{};" and/or the string "#define"*/
		if (strlen(line) > 7) {
			if (strstr(line, "#define")) {
				if ((status = add_macro(line + 7)) < 0)
					return status;
				line[0] = '\0';
			}
			else if (strstr(line, "enum")) {
				if ((status = add_enum(line + 4)) < 0)
					return status;
				line[0] = '\0';
			}
		}
		/*if there are no new macros or enums*/
		if (line[0] == '\0' || kill_spaces(line) >= strlen(line))
			fputs("\n", file_c3);
		else if (line[0] != '\n') {
			strcpy(temp_line, line);
			while (replace_macro(temp_line, string) == SUCCESS)
				strcpy(temp_line, string); 
			while (replace_enum(temp_line, string) == SUCCESS)
				strcpy(temp_line, string);
			fputs(temp_line, file_c3);
			line[0] = '\0';
		}
		else
			fputs(line, file_c3);
	}
	if (!feof(file_c2)) {
		perror(str_c2);
		return FILE_ERROR;
	}
	free_enum_list();
	free_macro_list();
	free(str_c2);
	free(str_c3);
	free(temp_line);
	free(line);
	free(string);
	fclose(file_c2);
	fflush(file_c3);
	fclose(file_c3);
	return SUCCESS;
}

/*remove white spaces*/
int kill_spaces(char *line) {
	int i;
	for (i = 0; i < strlen(line) && isspace(line[i]); i++)
		;
	return i;
}
