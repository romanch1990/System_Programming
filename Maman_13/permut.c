/* Name: Roman Chikunov


*/


#include "permut.h"

char *err_msgs[] = {"",
		"Out of space\n",
		"Wrong syntax\n",
		"Wrong file name\n",
		"Too many parameter\n"};

int check_name(char *name);
int part1(char *name);
int part2(char *name);
int part3(char *name);

/*get a file name and remove the comments and replace the includes, macros and enums with corresponding value*/
int main(int argc, char *argv[]) {
	char *prog_name;
	int status;
	
	if (argc != 2) {
		fprintf(stderr, "%s: %s", argv[0], err_msgs[(-1) * WRONG_SYNTAX]);
		exit(WRONG_SYNTAX);
	}
	
	prog_name = (char *) malloc (strlen(argv[1]));
	
	if (!prog_name) { 
		fprintf(stderr, "%s: %s", argv[0], err_msgs[(-1) * OUT_OF_SPACE]);
		exit(OUT_OF_SPACE);
	}
	
	strcpy(prog_name, argv[1]);
	
	if (check_name(prog_name) < SUCCESS) { 
		fprintf(stderr, "%s: The program name %s is invalid\n", argv[0], prog_name);
		exit(WRONG_SYNTAX);
	}
	
	/*activate all parts and check if all went well*/
	if ((status = part1(prog_name)) < SUCCESS)
		exit(status); 
	else if ((status = part2(prog_name)) < SUCCESS)
		exit(status);
	else if ((status = part3(prog_name)) < SUCCESS)
		exit(status);
	exit(SUCCESS);
}

/*check the name of the program. return 1 if not valid and 0 if is*/
int check_name(char *name) {
	int len = strlen(name), i = 0;
	
	while (i < len && isalnum(name[i]))
		i++;
	if (i >= len || name[i] != '.') {
		fprintf(stderr, "%s: %s", name, err_msgs[(-1) * WRONG_FILE_NAME]);
		return WRONG_FILE_NAME;
	}
	
	if (name[++i] == 'c')
		return SUCCESS;
	
	fprintf(stderr, "%s: %s", name, err_msgs[(-1) * WRONG_FILE_NAME]);
		return WRONG_FILE_NAME;
}

/*open a file. return a pointer to the memory location or NULL*/
FILE *open_file(char *name, char *mode) {
	FILE *file;
	if (!(file = fopen(name, mode))) {
		perror(name);
		return NULL;
	}
	return file;
}



