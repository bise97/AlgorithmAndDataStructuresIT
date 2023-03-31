/* INPUT:
5
2 4 3 3 1
8
97 6 -3 -3 7 8 45 -30
4
9 4 6 1
0

L'input è nel formato:
n				//num. di elementi del vettore
a1 a2 ... an	//elementi del vettore
...
n=0 per terminare */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void merge(int *A, int p, int q, int r){
    int nL, nR;
    int *L, *R;
    int i, j;
    
    nL = q-p+1;
    nR = r-q;
    
    L = (int*)malloc(sizeof(int)*(nL+1));
    R = (int*)malloc(sizeof(int)*(nR+1));
    
    for(i = 0; i < nL ; i++) L[i] = A[p+i];
    for(j = 0; j < nR ; j++) R[j] = A[q+1+j];
    
    L[nL] = INT_MAX;
    R[nR] = INT_MAX;
    
    i = 0;
    j = 0;
    
    for(int k = p; k <= r ; k++){
        
        if (L[i] <= R[j]) {
            A[k] = L[i];
            i++;
        }
        else{
            A[k] = R[j];
            j++;
        }
    }
}

void merge_sort(int *A, int p, int r){
    int q;
    
    if(p < r){
        q = (p+r)/2;
        merge_sort(A,p,q);
        merge_sort(A,q+1,r);
        merge(A,p,q,r);
    }
}

int binary_search(int x, int *A, int p, int r){
    int i = -1;
    int q;
    
    while( p <= r ) {
        q = (p+r)/2;
        
        if(x < A[q]) r = q-1;
        else{
            p = q+1;
            if(x == A[q]) i = q;
        }
    }
    
    return i;
}

void num_elementi_min(int *A,int *B, int n){
    int *C;
    C = (int*)malloc(sizeof(int)*n);
    
    for(int i = 0 ; i < n ; i++){
        C[i] = A[i];
    }
    
    merge_sort(C,0,n-1);
    
    
    for(int i = 0; i < n ; i++){
        B[i] = binary_search(A[i],C,0,n-1) + 1;
    }
    
   free(C);
}

int main(void) {
	// your code goes here
	int n;
	int *A, *B;
	
	scanf("%d",&n);
	
	while(n != 0){
	    
	   A = (int*) malloc(sizeof(int)*n);
	   B = (int*) malloc(sizeof(int)*n);
	   
	   for(int i = 0 ; i < n ; i++){
	       scanf("%d ",&A[i]);
	   } 

	   num_elementi_min(A,B,n);
	   
	   for(int i = 0 ; i < n ; i++){
	       printf("%d ",B[i]);
	   }
	   printf("\n");
	   
	   free(A);
	   free(B);
	   
	   scanf("%d",&n);
	}
	
	return 0;
}
