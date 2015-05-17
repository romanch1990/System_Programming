/*
 ============================================================================
 Name        : adjacency.c
 Author      : Roman Chikunov
 Description : Checks if there is directed path from the root to a node within a tree
 				that represented by a matrix. 
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define N 11
typedef enum boolean {
	FALSE, TRUE
} boolean;

int* getMat(int* A){
	int *p;
	for (p=A; p < A +((N+1)*(N+1)); p++)
		scanf("%d", &(*p));
	return A;
}

/* Prints the array*/
void printArray(int *A) {
	int *p, *p2;
	printf("The input array is:\n\n");
	for (p=A; p < A+((N+1)*(N+1)); ) {
		for (p2=p+N+1; p < p2 ; p++)
			printf("%d", *p);
		printf("\n");
	}
}

/*Gets the source to search from*/
int getSource() {
	int y;
	printf("\nPlease enter the source number: ");
	scanf("%d", &y);
	return y;
}

/*Gets the destination to search to*/
int getDestination() {
	int x;
	printf("\nPlease enter the destination number: ");
	scanf("%d", &x);
	return x;
}

/* Gets a directed tree from the user that represented as a matrix
	and prints a result which would be a path exists between two nodes or doesn't exist*/
int path(int *A, int u, int v) {
	int *p;
	int i;
	boolean bool;
	p = A;

	if (*(p+u*(N+1)+v) == 1)
		return TRUE;

	for(p=A+v+(N+1), i=1; p < A+((N+1)*(N+1)); i++, p+=(N+1)){
		if (*p==1){
			bool = path(A,u,i);
			return bool;
		}
	}
	return FALSE;
}

int main(void) {
	int *A;
	int u,v;
	boolean Answer;

	A = (int*) malloc((N+1)*(N+1)*sizeof(int));
	A = getMat(A);
	printArray(A);

	u = getSource();
	printf("\nYou entered %d (From the input file...)\n", u);
	v = getDestination();
	printf("\nYou entered %d (From the input file...)\n", v);

	Answer = path(A,u,v);
	if (Answer)
		printf("\nFound a path from %d to %d\n", u, v);
	else
		printf("\nCouldn't find a path from %d to %d\n", u, v);

/*The lines below show all available paths:*/
/*	for (u=1; u<12; u++){
		for (v=1; v<12; v++){
			Answer = path(A,u,v);
			if (Answer)
				printf("\nFound path from %d to %d", u, v);
		}
	}
*/
	return EXIT_SUCCESS;
}
