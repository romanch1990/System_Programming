#include <stdio.h> /*for getchar, printf*/
#include <ctype.h> /*for isdigit()*/
#include <stdlib.h> /*for atof, malloc...*/
#include <string.h> /*for strcmp*/
#include <stdarg.h> 

#define BYTE_SIZE	(sizeof(char)*8)
#define ARR_SIZE	(128/BYTE_SIZE) /*The array's size (=16)*/
#define NUM_OF_SETS	7
#define NUM_OF_FUNCS	6
#define LONGEST_FUNC	13
#define HELP_SET	NUM_OF_SETS-1

typedef struct {
	char name;
	char set_arr[ARR_SIZE];
} SET;

void start(void);
void print_msg(int loc);
int kill_spaces(void);	
void empty_set(int loc);	
void print_set(int setX);
void union_set(int setX, int setY, int setZ);
void intersect_set(int setX, int setY, int setZ);
void sub_set(int setX, int setY, int setZ);
void halt(void);



