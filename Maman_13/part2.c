#include "permut.h"

extern char *err_msgs[];

int get_include_name(char *line, char *str_inc);
int add_include(FILE *file, char *file_name, char *str_inc);

/*get a file name (*.c but use the *.c1) replace the includes and save it on the same name with 2 at the end (*.c2)  */
int part2(char *str_c) {
	/*The input file, output file and the "included" file*/
	FILE *file_c1, *file_c2;
	
	/*the files *.c1 , *.c2 and the include file's names */
	char *str_c1, *str_c2, *str_inc, *line;
	int i, status;
	
	str_c1 = (char *) malloc (strlen(str_c) + 2);
	str_c2 = (char *) malloc (strlen(str_c) + 2);
	str_inc = (char *) malloc (LINE_LEN);
	line = (char *) malloc (LINE_LEN);

	if (!str_c1 || !str_c2 || !str_inc || !line) {
		fprintf(stderr, "part2: %s", err_msgs[(-1) * OUT_OF_SPACE]);
		return OUT_OF_SPACE;
	}

	/*str_c1 = *.c1  */
	strcpy(str_c1, str_c);
	strcat(str_c1, "1");
	
	/*str_c2 = *.c2  */
	strcpy(str_c2, str_c);
	strcat(str_c2, "2");
	
	/*open the file *.c1 */
	if (!(file_c1 = open_file(str_c1, "r")))
		return FILE_ERROR;

	/*open the file *.c2 */
	if (!(file_c2 = open_file(str_c2, "w")))
		return FILE_ERROR;
	
	/*while it's not the EOF - get another line and check it out*/
	while ((fgets(line, LINE_LEN, file_c1))) {
		i = 0, status;
		/*if there is enough chars for the string "#include" */
		if (strlen(line) > 9) {
			if (strstr(line, "#include")) {
				strcpy(line, line + 8);
				i = kill_spaces(line);
				if ((status = get_include_name(line + i, str_inc)) != -1)
					i += status;
				else {
					fprintf(stderr, "part2: %s", err_msgs[(-1) * WRONG_SYNTAX]);
					return WRONG_SYNTAX;
				}
				if ((status = add_include(file_c2, str_c2, str_inc)) < SUCCESS)
					return status;
				strcpy(line, line + i);
			}
		}
		if (fputs(line, file_c2) == EOF) {
			perror(str_c2);
			return FILE_ERROR;
		}
	}
	/*if an error has occurred*/
	if (!feof(file_c1)) {
		perror(str_c1);
		return FILE_ERROR;
	}
	free(str_c1);
	free(str_c2);
	free(line);
	free(str_inc); 
	fclose(file_c1);
	fflush(file_c2);
	fclose(file_c2);
	return SUCCESS;
}

/*get a line and a valid string. put the included's file name in the string and return the file's name length + 2 for the "" */
int get_include_name(char *line, char *str_inc) {
	if (sscanf(line, "%s", str_inc)) {
		/*remove the " from the beginning*/
		strcpy(str_inc, str_inc + 1);
		/*remove the " from the end*/
		str_inc[strlen(str_inc) - 1] = '\0';
		return strlen(str_inc) + 2;
	}
	else
		return -1;
}

/*add to file *.c2 the contant of str_inc*/
int add_include(FILE *file, char *file_name, char *str_inc) {
	char *string = (char *) malloc (LINE_LEN);
	FILE *file_inc;
	if (!(file_inc = open_file(str_inc, "r")))
			return FILE_ERROR;
		/*while we are not in EOF of the included file put the line in *.c2 */
		while ((fgets(string, LINE_LEN, file_inc)) && !feof(file_inc)) {
				if (fputs(string, file) == EOF) {
					perror(file_name);
					return FILE_ERROR;
				}
		} 
		/*if it's not the EOF it's an error*/
		if (!feof(file_inc)) {
			perror(str_inc);
			return FILE_ERROR;
		}
		fflush(file_inc);
		fclose(file_inc); 
		free(string);
		return SUCCESS;
}
