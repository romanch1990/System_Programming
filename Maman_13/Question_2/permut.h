#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define LINE_LEN	256
#define PARM_LEN	128
#define MAX_PARM	3
/*exit status*/
#define SUCCESS			0
#define OUT_OF_SPACE	-1
#define WRONG_SYNTAX	-2
#define WRONG_FILE_NAME	-3
#define	TOO_MANY_PARM	-4
#define FILE_ERROR		-5
#define FALSE			-6

int kill_spaces(char *line);
FILE *open_file(char *name, char *mode);
