#include "permut.h"

extern char *err_msgs[];

typedef struct MACRO *macroptr;
/*Contains all the info about the marco that we will handle*/
typedef struct MACRO {
	char name[LINE_LEN];
	char parm[MAX_PARM][PARM_LEN];
	char body[PARM_LEN];
	int num_of_parm;
	macroptr next;
} T_macro;

/*Pointers that will point to the head of macros and to the last in the list*/
macroptr M_head = NULL, M_ptr = NULL;


int add_macro_node(void);
int add_macro_name(char *line);
void add_macro_body(char *line);
int add_macro_parm(char *line);
macroptr last_in_macro_list(void);
int replace_macro(char *line, char *updated_line);
int replace_parm(macroptr M_temp, char **parm, char *body);
int check_macro_substring(char *line, char *ptr, int sub_len);
void print_macro_list(void);

/*add a new macro to the list */
int add_macro(char *line) {
	int i = 0, c, type, status;
	enum type {COMPLEX, SIMPLE};
	macroptr M_temp;
	if ((status = add_macro_node()) < 0)
		return status;
	M_temp = last_in_macro_list();
	i += add_macro_name(line);
	((c = line[i]) == '(') ? (type = COMPLEX) : (type = SIMPLE);
	if (type == COMPLEX)
		i += add_macro_parm(line + (i + 1)) + 1;
	add_macro_body(line + i);
	return SUCCESS;
}

/*adding a new macro to the list */
int add_macro_node() { 
	macroptr M_temp = (macroptr) malloc (sizeof(T_macro));
	if (M_temp) {
		/*if the list is empty */
		if (M_head == NULL) {
			M_head = M_temp;
			M_head->num_of_parm = 0;
			M_head->next = NULL;
		}
		else {
			/*if there is only one element in the list */
			if (M_ptr == NULL)
				M_head->next = M_temp;
			/*at least two elements in the list */
			else
				M_ptr->next = M_temp;
			M_ptr = M_temp;
			M_ptr->num_of_parm = 0;
			M_ptr->next = NULL;
		}
		return SUCCESS;
	} 
	else {
		fprintf(stderr, "part3: %s", err_msgs[(-1) * OUT_OF_SPACE]);
		return OUT_OF_SPACE;
	}
}


/*add the name of the macro and return its length */
int add_macro_name(char *line) {
	int c, j = 0, i = kill_spaces(line);
	macroptr M_temp = last_in_macro_list();
	while (isalnum(c = line[i])) {
		M_temp->name[j++] = c;
		i++;
	}
	M_temp->name[j] = '\0';
	return i;
}

/*adding the macro's body */
void add_macro_body(char *line) {
	int c, j = 0, i = kill_spaces(line);
	macroptr M_temp = last_in_macro_list();
	while ((c = line[i++]) != '\n')
		M_temp->body[j++] = c;
	M_temp->body[j] = '\0';
}

/*add the macro's parameters */
int add_macro_parm(char *line) {
	macroptr M_temp = last_in_macro_list();
	int i = 0, j = 0, c, parm_cnt = 0, b_cnt = 1;
	while (b_cnt) {
		if ((c = line[i++]) == ',') {
			M_temp->parm[parm_cnt++][j] = '\0';
			j = 0;
		}
		else if (c == '(')
			b_cnt++;
		else if (c == ')')
			b_cnt--;
		else
			M_temp->parm[parm_cnt][j++] = c;
	}
	M_temp->parm[parm_cnt][j] = '\0';
	M_temp->num_of_parm = ++parm_cnt;
	return i;
}


/*print the macro list*/
void print_macro_list() {
	macroptr M_temp;
	int i = 1, j;
	if (M_head == NULL) {
		printf("**Macro list is empty**\n\n");
		return;
	}
	for (M_temp = M_head; M_temp; M_temp = M_temp->next) {
		printf("%d) Macro's  name: %s\n", i++, M_temp->name);
		printf("The amount of parm is: %d\n", M_temp->num_of_parm);
		printf("The macro's body is: %s\n", M_temp->body);
		for (j = 0; j < MAX_PARM; j++)
			printf("parm num %d is: %s\n\n", j, M_temp->parm[j]);
	}
	printf("**End of macro list**\n\n");
}

/*put in loc the loction of the name in the array and check if the name if in a string or not return SUCCESS if in a string return the q_mark counter*/
int check_q_mark(char *line, char *ptr, int *loc) {
	int q_mark = 0;
	while (line + *loc != ptr) {
		if (line[*loc] == '\"') {
			if (*loc == 0)
				q_mark++;
			else if (line[*loc-1] != '\\')
				q_mark++;
		}
		(*loc)++;
	}
	if (q_mark % 2 == 0)
		return SUCCESS;
	else
		return q_mark;
}

/*get a line and look for an macro name. if find any - replace it by it's value and return the updated line else return NULL*/
int replace_macro(char *line, char *updated_line) {
	int loc = 0, i, j = 0, q_mark = 0, c, parm_cnt = 0;
	char *ptr, **parm = (char **) malloc (sizeof(char *) * MAX_PARM);
	macroptr M_temp;  printf("in replace_macro, line = %s\n", line);
	if (!parm) {
		fprintf(stderr, "par3: %s", err_msgs[(-1) * OUT_OF_SPACE]);
		return OUT_OF_SPACE;
	}
	/*malloc all the strings */
	for (i = 0 ; i < MAX_PARM; i++) {
		parm[i] = (char *) malloc (LINE_LEN);
		if (!parm[i]) {
			fprintf(stderr, "par3: %s", err_msgs[(-1) * OUT_OF_SPACE]);
				return OUT_OF_SPACE;
		}
	}
	for (M_temp = M_head; M_temp; M_temp = M_temp->next) {
		/*if there is a match*/
		if ((ptr = strstr(line, M_temp->name))) {
			char *temp_ptr = ptr;
			q_mark = check_q_mark(line, ptr, &loc);
			/*if it's in quotation mark - ignore it and update ptr */
			while (q_mark % 2 != SUCCESS && loc < strlen(line) && temp_ptr) {
				temp_ptr = strstr(line + (loc+1), M_temp->name);
				if (temp_ptr) {
					ptr = temp_ptr;
					loc++;
					q_mark += check_q_mark(line, ptr, &loc);
				}
			}
			if (loc >= strlen(line))
				return FALSE;
			if (q_mark % 2 == SUCCESS) {
				if (check_macro_substring(line, ptr, strlen(M_temp->name)) == SUCCESS) {
					/*if it's a simple macro */
					if (M_temp->num_of_parm == 0) { printf("before strcpy. updated_line = \n%s\nloc is = %d\nupdated_line[loc - 1] = '%c'\n", updated_line, loc, updated_line[loc - 1]); fflush(stdout);
						strncpy(updated_line, line, loc);
						updated_line[loc] = '\0'; printf("after strcpy. updated_line = \n%s\nloc is = %d\nupdated_line[loc - 1] = '%c'\n", updated_line, loc, updated_line[loc - 1]); fflush(stdout);
						strcat(updated_line, M_temp->body);
						loc += strlen(M_temp->body);
						updated_line[loc] = '\0'; printf("after the first strcat. updated_line = \n%s\nloc is = %d\nupdated_line[loc - 1] = '%c'\n", updated_line, loc, updated_line[loc - 1]); fflush(stdout);
						strcat(updated_line, ptr + strlen(M_temp->name));
						loc += strlen(M_temp->name);
						updated_line[loc] = '\0'; printf("after the second strcat. updated_line = \n%s\nloc is = %d\nupdated_line[loc - 5] = '%d'\n", updated_line, loc, (char)updated_line[loc - 5]); fflush(stdout);
						return SUCCESS;
					}
					/*if it's a complex macro */
					else {
						/*get the parms */
						int i = loc, b_cnt = 1;
						char *body = (char *) malloc (LINE_LEN);
						if (!body) {
							fprintf(stderr, "part3: %s", err_msgs[(-1) * OUT_OF_SPACE]);
							return OUT_OF_SPACE;
						}
						while ((c = line[i++]) != '(')
							;
						/*save the new parm name in parm[][]*/
						while(parm_cnt < (M_temp->num_of_parm) && b_cnt) {
							if ((c = line[i++]) == ',') {
								parm[parm_cnt++][j] = '\0';
								j = 0;
							}
							else if (c == '(')
								b_cnt++;
							else if (c == ')')
								b_cnt--;
							else
								parm[parm_cnt][j++] = c;
							
						}
						parm[parm_cnt][j] = '\0';
						if (replace_parm(M_temp, parm, body) == SUCCESS) {
							strncpy(updated_line, line, loc);
							updated_line[loc] = '\0';
							strcat(updated_line, body);
							/* i hold the location in the array after the parm */
							strcat(updated_line, line + i);
							for (i = MAX_PARM - 1; i > 0; i--)
								free(parm[i]);
							return SUCCESS;
						}
						free(body);
					}
				}
			}
		}
		loc = 0;
	} /* for's brackets */
	for (i = MAX_PARM - 1; i > 0; i--)
		free(parm[i]);
	return FALSE;
}

int replace_parm(macroptr M_temp, char **parm, char *new_body) {
	int i, j, k;
	char *ptr, *body = (char *) malloc (LINE_LEN);
	if (!body) {
		fprintf(stderr, "part3: %s", err_msgs[(-1) * OUT_OF_SPACE]);
		return OUT_OF_SPACE;
	}
	strcpy(body, M_temp->body);
	strcpy(new_body, body);
	/*search for the parameters in the body and replaces them with the new ones */
	for (i = 0; i < M_temp->num_of_parm; i++) {
		/*look for this parm in the body, to replace it with the new one */
		if ((ptr = strstr(body, M_temp->parm[i]))) {
			/*if we found the parm's location */
			if (check_macro_substring(body, ptr, strlen(M_temp->parm[i])) == SUCCESS) {
				/*j is where the old parm start in the array */
				j = 0;
				while (body + j != ptr)
					j++;
				k = 0;
				while (k < strlen(parm[i]))
					new_body[j++] = parm[i][k++];
				new_body[j] = '\0';
				strcat(new_body, ptr + strlen(M_temp->parm[i]));
				strcpy(body, new_body);
			}
			else
				strcpy(body, ptr + 1);
		}
	}
	free(body);
	return SUCCESS;
}


/*check if the substring is in a middle of a word or not*/
/*it's the same as check_enum_substring but this way all the related func are together*/
int check_macro_substring(char *line, char *ptr, int sub_len) {
	int c;
	if (line == ptr) {
		if (strlen(line) == strlen(ptr))
			return SUCCESS;
		else {
			c = *(ptr + sub_len + 1);
			if (isalnum(c))
				return FALSE;
			else
				return SUCCESS;
		}
	}
	else {
		c = *(ptr - 1);
		if (isalnum(c))
			return FALSE;
		else {
			if (strlen(line) > sub_len + 1) {
				c = *(ptr + sub_len);
				if (isalnum(c))
					return FALSE;
				else
					return SUCCESS;
			}
		}
	}
	return SUCCESS;
}

/*free the macro list*/
void free_macro_list() {
	while (M_head) {
		macroptr M_temp = M_head;
		M_head = M_head->next;
		free(M_temp);
	}
}

/*return the last in the list*/
macroptr last_in_macro_list() {
	if (M_head->next == NULL)
		return M_head;
	else
		return M_ptr;
}
