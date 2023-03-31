#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int check(int i, int j, int **mat, int n, int m){
    if(i < 0 || i >= n) return 0;
    if(j < 0 || j >= m) return 0;
    if(mat[i][j] != 1) return 0;
    if(i > 0 && mat[i-1][j] == 0) return 0;
    if(i < n-1  && mat[i+1][j] == 0) return 0;
    if(j > 0 && mat[i][j-1] == 0) return 0;
    if(j < m-1  && mat[i][j+1] == 0) return 0;
    
    return 1;
}

int check2(int i, int j, int **mat, int n, int m, int min, int lun_att){
    if(check(i,j,mat,n,m) && (lun_att+m-j-1)<min) return 1;
    else return 0;
}

void step(int i, int j, int **mat, int n, int m, int count, int *min){
    mat[i][j] = -1;
    
    if(j == m-1){
        if(count < *min) *min = count;
    }
    else{
        if(check2(i,j+1,mat,n,m,*min,count+1)) step(i,j+1,mat,n,m,count+1,min);
        if(check2(i+1,j,mat,n,m,*min,count+1)) step(i+1,j,mat,n,m,count+1,min);
        if(check2(i-1,j,mat,n,m,*min,count+1)) step(i-1,j,mat,n,m,count+1,min);
        if(check2(i,j-1,mat,n,m,*min,count+1)) step(i,j-1,mat,n,m,count+1,min);
    }

    mat[i][j] = 1;
}

int shortest_path(int **mat, int n, int m){
    int min = INT_MAX;
    
    for(int i = 0; i < n; i++){
        if(check2(i,0,mat,n,m,min,1)){;
            step(i,0,mat,n,m,1,&min);
        }
    }
    
    if(min == INT_MAX) min = -1;
    
    return min;
}

int main(void) {
	// your code goes here
	int n, m, ntest;
	int **mat;
	int ris;
	
	scanf("%d",&ntest);
	while(ntest > 0){
	    scanf("%d %d",&n,&m);
	    mat = (int**)malloc(sizeof(int*)*n);
	    for(int i = 0; i < n; i++){
	        mat[i] = (int*)malloc(sizeof(int)*m);
	    }
	    
	    for(int i = 0; i < n; i++){
	        for(int j = 0; j < m ; j++){
	            scanf("%d",&mat[i][j]);
	        }
	    }
	    

	    ris = shortest_path(mat,n,m);
	    printf("%d\n",ris);
	    
	    for(int i = 0; i < n; i++){
	        free(mat[i]);
	    }	    
	    free(mat);
	    
	    ntest--;
	}
	return 0;
}

CASI DI TEST:
3
7 10
1 1 1 1 1 1 1 1 0 1 
1 1 1 1 1 1 1 1 1 1 
1 1 1 1 1 1 1 1 1 1 
0 1 1 1 1 1 1 1 1 1 
1 1 1 1 1 1 1 1 1 1 
0 1 1 1 1 1 1 1 0 1 
0 1 1 1 1 1 1 1 1 1 
5 5
1 1 1 1 1 
1 1 1 1 1 
1 1 1 1 1 
1 1 1 1 1 
1 1 1 1 1 
9 6
1 1 1 1 1 0 
1 1 1 1 1 1 
0 1 1 1 1 1 
1 1 1 1 1 1 
1 1 1 1 1 0 
1 1 1 1 1 1 
1 1 0 1 1 1 
1 1 1 1 1 1 
1 1 1 1 1 0

