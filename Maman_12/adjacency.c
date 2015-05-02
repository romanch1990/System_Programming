#include <stdio.h>


#define N 11 /* matrix size */

enum state {FALSE, TRUE};

typedef int adj_mat[N][N]; /* matrix definition */

/* function prototype */
int path (adj_mat[][], int u, int v);

/*path definition*/
int path(adj_mat mat[][], int u, int v){

	if u == v
		return TRUE;
	int i;
	for (i = 0; i < N; i++){

		if mat[i][v] == 1{
			path (mat, u, i);
		}
	}
	reutrn FALSE;
}


int main(){

	adj_mat arr[N][N]= {
		{0,1,1,1,0,0,0,0,0,0,0},
		{0,0,0,0,1,1,1,1,1,0,0},
		{0,0,0,0,0,0,0,0,0,1,0},
		{0,0,0,0,0,0,0,0,0,0,1},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0}};

	int u;
	int v;
	printf("please enter two numbers \n");
	scanf("%d %d", &u, &v);
	/*check if a path exists and return an answer*/
	int answer;
	answer = path(arr[][], u, v);
	printf("The answer is %d", answer);



	return 0;
}