#include "permut.h"

extern char *err_msgs[];

typedef struct ENUM *enumptr;
/*contain all the info about the enum that we will handle*/
typedef struct ENUM {
	char name[PARM_LEN];
	char val;
	enumptr next;
} T_enum;

/*will point to the head of macros and a pointer to the last in the list*/
enumptr E_head = NULL, E_ptr = NULL;


int add_enum_node(void);
int add_enum_name(char *line);
void add_enum_val(int val);
enumptr last_in_enum_list(void);
int replace_enum(char *line, char *updated_line);
int check_enum_substring(char *line, char *ptr, int sub_len);
void print_enum_list(void);


/*add a new enum to the list */
int add_enum(char *line) {
		int i = 0, c, enum_cnt = 0, status;
		while (i < strlen(line) && (c = line[i]) != '{')
			i++;
		i++;
		if ((status = add_enum_node()) != SUCCESS)
			return status;
		while (i < strlen(line) && (c = line[i]) != '}') {
			if (isalnum(c)) {
				i += add_enum_name(line + i);
				add_enum_val(enum_cnt++);
			}
			else if (c == ','){
				if ((status = add_enum_node()) == SUCCESS)
					i++;
				else
					return status;
			}
			/*spaces - cause there are no errors in file */
			else
				i++;
		}
		return SUCCESS;
		/*no errors in file - so no errors in thos func*/
}

/*adding a new enum to the list */
int add_enum_node() { 
	enumptr E_temp = (enumptr) malloc (sizeof(T_enum));
	if (E_temp) {
		/*if the list is empty */
		if (E_head == NULL) {
			E_head = E_temp;
			E_head->next = NULL;
		}
		else {
			/*if there is only one element in the list */
			if (E_ptr == NULL)
				E_head->next = E_temp;
			/*at least two elements in the list */
			else
				E_ptr->next = E_temp;
			E_ptr = E_temp;
			E_ptr->next = NULL;
		}
		return SUCCESS;
	} 
	else {
		fprintf(stderr, "part3: %s", err_msgs[(-1) * OUT_OF_SPACE]);
		return OUT_OF_SPACE;
	}
}


/*add the enum's name and return it's length */
int add_enum_name(char *line) {
	int i = 0, j = 0, c;
	enumptr E_temp = last_in_enum_list();
	while (i < strlen(line) && isalnum(c = line[i])) {
		E_temp->name[j++] = c;
		i++;
	}
	E_temp->name[j] = '\0';
	return i;
}

/*add the enum's value*/
void add_enum_val(int val) {
	enumptr E_temp = last_in_enum_list();
	int zero = '0';
	E_temp->val = zero + val;
}



/*print the enum list*/
void print_enum_list() {
	enumptr E_temp;
	int i = 1;
	if (E_head == NULL) {
		printf("**The enum list is empty**\n\n");
		return;
	}
	for (E_temp = E_head; E_temp; E_temp = E_temp->next) {
		printf("%d) enum's  name: %s\n", i++, E_temp->name);
		printf("The enum's value is: %c\n\n", E_temp->val);
	}
	printf("**The end of enum list**\n\n");
}

/*get a line and look for an enum name. if find any - replace it by it's value and return the updated line else return NULL*/
int replace_enum(char *line, char *updated_line) {
	int loc = 0, q_mark = 0;
	char *ptr;
	enumptr E_temp;
	for (E_temp = E_head; E_temp; E_temp = E_temp->next) {
		/*if there is a mach*/
		if ((ptr = strstr(line, E_temp->name))) {
			while (line + loc != ptr) {
				if (line[loc] == '\"') {
					if (loc == 0)
						q_mark++;
					else if (line[loc-1] != '\\')
						q_mark++;
				}
				loc++;
			}
			/*if it's in quotation mark - ignor it*/
			if (q_mark % 2 != 0)
				break;
			if (check_enum_substring(line, ptr, strlen(E_temp->name)) == SUCCESS) {
				strncpy(updated_line, line, loc);
				updated_line[loc++] = E_temp->val;
				updated_line[loc] = '\0';
				strcat(updated_line, ptr + strlen(E_temp->name));
				return SUCCESS;
			}
			else
				strcpy(line, ptr + 1);
		}
	}
	return FALSE;
}

/*check if the substring is in a middle of a word or not*/
/*it's the same as check_macro_substring but this way all the related func are together*/
int check_enum_substring(char *line, char *ptr, int sub_len) {
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

/*free the enum list*/
void free_enum_list() {
	while (E_head) {
		enumptr E_temp = E_head;
		E_head = E_head->next;
		free(E_temp);
	}
}

/*return the last in the list*/
enumptr last_in_enum_list() {
	if (E_head->next == NULL)
		return E_head;
	else
		return E_ptr;
}
