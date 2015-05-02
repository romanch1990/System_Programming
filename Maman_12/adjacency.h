#define N 11 /* matrix size */

enum state {FALSE, TRUE};

typedef int adj_mat[N][N]; /* matrix definition */



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
