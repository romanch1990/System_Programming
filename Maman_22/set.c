#include "set.h"

SET sets[NUM_OF_SETS]= {{'A', {""}},	/*0*/
			{'B', {""}},	/*1*/
			{'C', {""}},	/*2*/
			{'D', {""}},	/*3*/
			{'E', {""}},	/*4*/
			{'F', {""}},	/*5*/
			{'G', {""}}};	/*6 - a help set*/
			
char *func_names[] = {"read_set",		/*0*/
			"print_set",		/*1*/
			"union_set",		/*2*/
			"intersect_set",	/*3*/
			"sub_set",		/*4*/
			"halt"};		/*5*/
			
char *msgs[] = { "Error - No such set\n",	/*0*/
			"Error - No such command\n",	/*1*/
			"Error - Wrong syntax\n",	/*2*/
			"Error - Unown error\n",	/*3*/
			"Please enter a new command:\n"};/*4*/

enum {READ_SET, PRINT_SET, UNION_SET, INTERSECTION_SET, SUB_SET, HALT};

/*prompt the user to type a command and check whether it is valid.
If it's valid - execute it or call the right function, to do so. If it's not valid - print an error massage and prompt the user to type another command, until he types "halt"*/
void start(void) {
	char cmd[LONGEST_FUNC], EMPTY_SET[ARR_SIZE], mask;
	int i, temp, c, func, setX, setY, setZ, set, state, set_cnt, next_state, cnt, num, fraction, got_num_in_set;
	enum {READ_CMD, CHECK_CMD, READ_SET_NAME, CHECK_SET_NAME, CHECK_COMMA, READ_SET_NUM, CHECK_SET_NUM, PUT_NUM_IN_SET, RESET};
	state = set_cnt = next_state = cnt = got_num_in_set = 0;
	set = setX = setY = setZ = func = num = -1;
	
	for (i = 0; i < LONGEST_FUNC; i++)
		cmd[i] = '\0';
		
	for (i= 0; i < ARR_SIZE; i++)
		EMPTY_SET[i] = '\0';
	
	printf("Please enter a command, and then press Enter:\n");
	while (func != HALT) {
		switch (state) {
			case READ_CMD:
				scanf("%s", cmd);
				state = CHECK_CMD;
				break;
				
			case CHECK_CMD:
				for (i = 0; i < NUM_OF_FUNCS; i++) {
					if (!strcmp(cmd, func_names[i]))
						func = i;
				}
				/*no such func*/
				if (func == -1) {
					print_msg(1);
					state = RESET;
					break;
				}
				state = READ_SET_NAME;
				break;
			
			case READ_SET_NAME:
				c = kill_spaces();
				if (!isalpha(c)) {
					print_msg(0);
					state = RESET;
					break;
				}
				state = CHECK_SET_NAME;
				break;
				
			case CHECK_SET_NAME:
				for (i = 0; i < NUM_OF_SETS - 1; i++)
					if (sets[i].name == (char)c)
						set = i;
				/*no such set*/
				if (set == -1) {
					print_msg(0);
					state = RESET;
					break;
				}
				else {
					if (set_cnt == 0) {
						setX = set;
						set_cnt++;
						if (func == PRINT_SET) {
							print_set(setX);
							state = RESET;
							break;
						}
						if (func == READ_SET) {
							if (strcmp(sets[set].set_arr, EMPTY_SET)) {
								empty_set(setX);
							}
							next_state = READ_SET_NUM;
						}
						else
							next_state = READ_SET_NAME;
						state = CHECK_COMMA;
					}
					else if (set_cnt == 1) {
						setY = set;
						set_cnt++;
						state = CHECK_COMMA;
						next_state = READ_SET_NAME;
					}
					else if (set_cnt == 2) {
						setZ = set;
						set_cnt++;
						if (func == UNION_SET)
							union_set(setX, setY, setZ);
						else if (func == INTERSECTION_SET)
							intersect_set(setX, setY, setZ);
						else
							sub_set(setX, setY, setZ);
						state = RESET;
					}
					c = getchar();
					break;
				}
			
			case CHECK_COMMA:
				if (isspace(c) && c != '\n')
					c = kill_spaces();
				if (c == ',') {
					state = next_state;
					break;
				}
				if (c == '\n' && !got_num_in_set) {
					print_msg(2);
				}
				state = RESET;
				break;
			
			case READ_SET_NUM:
				if (isdigit(c = getchar())) {
					if ((c = ungetc(c, stdin)) != EOF) {
						scanf("%d", &num);
						state = CHECK_SET_NUM;
					}
					/*couldn't ungetc*/
					else
						print_msg(3);
					break;
				}
				if (c == '\n')
					print_msg(2);
				state = RESET;
				break;
				
			case CHECK_SET_NUM:
				if (num < 0 || num > 127) {
					printf("Error - %u is out of range\n", num);
					state = RESET;
					break;
				}
				/*if we got to here - it is a valid number*/
				c = getchar();
				state = PUT_NUM_IN_SET;
				break;
			
			case PUT_NUM_IN_SET:
				/*the whole number*/
				temp = (unsigned) num / BYTE_SIZE;
				/*the fraction*/
				fraction = (unsigned) (num - (temp * BYTE_SIZE));
				mask = 1 << fraction;
				/*save the new bit's number in the help set*/
				sets[HELP_SET].set_arr[temp] = sets[setX].set_arr[temp] | mask;
				/*update the set with the new number*/
				sets[setX].set_arr[temp] = sets[HELP_SET].set_arr[temp];
				got_num_in_set = 1;
				next_state = READ_SET_NUM;
				state = CHECK_COMMA;
				break;
				
			case RESET:
				setX = setY = setZ = set = func = -1;
				set_cnt = 0;
				if (c != '\n')
					while ((c = getchar()) != '\n')
						;
				putchar(c);
				print_msg(4);
				state = READ_CMD;
				break;
		}
	}
	halt();
}

void empty_set(int loc) {
	int i;
	for (i = 0; i < ARR_SIZE; i++)
		sets[loc].set_arr[i] = '\0';
}

void union_set(int setX, int setY, int setZ) {
	int i;
	for (i = 0; i < ARR_SIZE; i++)
		sets[setZ].set_arr[i] = sets[setX].set_arr[i] | sets[setY].set_arr[i];
}


void intersect_set(int setX, int setY, int setZ) {
	int i;
	for (i = 0; i < ARR_SIZE; i++)
		sets[setZ].set_arr[i] = sets[setX].set_arr[i] & sets[setY].set_arr[i];
}


void sub_set(int setX, int setY, int setZ) {
	int i;
	for (i = 0; i < ARR_SIZE; i++)
		sets[setZ].set_arr[i] = sets[setX].set_arr[i] ^ (sets[setX].set_arr[i] & sets[setY].set_arr[i]);
}


void print_set(int setX) {
	int i, j, val, empty = 1, cnt = 0;
	char mask;
	printf("The set is: ");
	for (i = 0; i < ARR_SIZE; i++)
		for (j = 0; j < BYTE_SIZE; j++) {
			val = BYTE_SIZE * i + j;
			mask = 1 << j;
			if (mask & sets[setX].set_arr[i]) {
				empty = 0;
				if (cnt == 15) {
					printf("%u\n", val);
					cnt = 0;
				}
				else {
					printf("%u, ", val);
					cnt++;
				}
			}
		}
	empty ? printf("Empty!\n") : printf("end of set!\n");
}


int kill_spaces() {
	int c;
	while (isspace(c = getchar()))
		;
	return c;
}


void print_msg(int loc) {
	printf("%s",msgs[loc]);
}


void halt() {
	exit(0);
}

			




