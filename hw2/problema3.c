#include <stdio.h>
#include <stdlib.h>

typedef struct Stack{
    int *v;
    int dim;
    int sp;
}Stack;

int pop(Stack *s){
    if(s->sp > 0){
        s->sp = s->sp - 1;
        return s->v[s->sp];
    }
    return -1;
}

void push(int x, Stack *s){
    if(s->sp < s->dim){
        s->v[s->sp] = x;
        s->sp = s->sp + 1;
    }
}

void invert_matrix(int **mat, int n, int m){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(mat[i][j] == 0) mat[i][j] = 1;
            else mat[i][j] = 0;
        }
    }
}

int max_area(int *w, int m){
    Stack s;
    int area, max_area = 0;
    int i, j;
    
    s.dim = m+1;
    s.v = (int*)malloc(sizeof(int)*m+1);
    s.sp = 0;
    
    push(-1,&s);
    
    j = 0;
    
    while(j < m){
        if(s.sp == 1 || w[j] >= w[s.v[s.sp-1]]){
            push(j,&s);
            j++;
        }
            
        else{
            i = pop(&s);
            area = w[i] * (j - s.v[s.sp-1] - 1);
            if(area > max_area) max_area = area;
        }
    }
    
    while(s.sp > 1){
        i = pop(&s);
        area = w[i] * (m - s.v[s.sp-1] - 1);
        if(area > max_area) max_area = area;
    }
    
    free(s.v);
    
    return max_area;
    
}

int max_zero_sottomat(int **mat, int n, int m){
    int *sum;
    int max = 0;
    int s;
    
    invert_matrix(mat,n,m);
    
    sum = (int*)calloc(m,sizeof(int));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(mat[i][j] == 0) sum[j] = 0;
            else sum[j] = sum[j] + mat[i][j];
        }
        s = max_area(sum,m);
        if(s > max) max = s;
    }
    free(sum);
    
    return max;
}

int main(void) {
	// your code goes here
	int n, m, ris;
	int **mat;
	
	while(scanf("%d %d",&n,&m) != EOF){
	    
	    mat = (int**)malloc(sizeof(int*)*n);
	    for(int i = 0; i < n; i++) mat[i] = (int*)malloc(sizeof(int)*m);
	    
	    for(int i = 0; i < n; i++){
	        for(int j = 0; j < m; j++){
	            scanf("%d",&mat[i][j]);
	        }
	    }
	    
	    ris = max_zero_sottomat(mat,n,m);
	    
	    printf("%d\n",ris);
	    
	    for(int i = 0; i < n; i++) free(mat[i]);
	    free(mat);
	}
	return 0;
}

CASI DI TEST:
3 4
0 1 0 0 
0 1 0 0 
0 0 0 1 
9 8
0 1 0 0 1 0 1 0 
0 0 1 0 0 0 0 0 
0 0 0 0 0 0 1 1 
0 0 0 1 0 0 0 0 
1 1 1 1 0 1 0 0 
0 0 1 0 0 1 0 0 
0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 
1 0 0 1 0 0 0 0 
4 6
0 0 0 0 0 0 
1 0 0 0 1 0 
0 0 0 0 0 1 
0 0 0 1 0 0

