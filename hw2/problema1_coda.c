#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Node{
    int x;
    int y;
    struct Node* next;
    struct Node* prev;
}Node;

typedef struct Queue{
    Node *head;
    Node *tail;
}Queue;

void insert(Queue *q, Node *n){
    n->next = q->head;
    n->prev = NULL;
    q->head = n;
    if(n->next != NULL) n->next->prev = n;
    else q->tail = n;
}

Node* get (Queue *q){
    Node *n;
    n = q->tail;
    if(n != NULL){
		q->tail = n->prev;
		if(q->tail != NULL){
			q->tail->next = NULL;
		}
		else{
			q->head = NULL;
		}
	}
    return n;
}

void enqueue(int i, int j, Queue *q){
    Node *n;
    n = (Node*)malloc((sizeof(Node)));
    n->x = i;
    n->y = j;
    insert(q,n);
}

int dequeue(Queue *q, int *i, int *j){
    Node *n;
    n = get(q);
    if(n != NULL){
        *i = n->x;
        *j = n->y;
        free(n);
        return 0;
    }
    else return -1;
}

int check(int **mat, int n, int m, int i, int j){
    int flag = 1;
    if(i > 0 && mat[i-1][j] == 0) flag = 0;
    if(i < n-1 && mat[i+1][j] == 0) flag = 0;
    if(j > 0 && mat[i][j-1] == 0) flag = 0;
    if(j < m-1 && mat[i][j+1] == 0) flag = 0;
    
    return flag;
}

void trasf_mat(int **mat, int n, int m){        //sostituisce tutte le celle percorribili con INT_MAX
    for(int i = 0; i < n; i++){                 //e tutte quelle non percorribili con 0 o -1
        for(int j = 0; j < m; j++){
            if(mat[i][j] == 1){
                if(check(mat, n, m, i, j) == 1){
                    mat[i][j] = INT_MAX;
                }
                else{
                    mat[i][j] = -1;
                }
            }
        }
    }
}

void update_cells(int **mat, int n, int m, int i, int j, Queue *q){
    int sum = mat[i][j] + 1;
    
    //controllo se posso aggiornare il vicino di dx
    if(j < m-1 && mat[i][j+1] > sum){
        mat[i][j+1] = sum;
        enqueue(i,j+1,q);
    }
    
    //controllo se posso aggiornare il vicino di sotto
    if(i < n-1 && mat[i+1][j] > sum){
        mat[i+1][j] = sum;
        enqueue(i+1,j,q);
    }
    
    //controllo se posso aggiornare il vicino di sopra
    if(i > 0 && mat[i-1][j] > sum){
        mat[i-1][j] = sum;
        enqueue(i-1,j,q);
    }
    
    //controllo se posso aggiornare il vicino di sx
    if(j > 0 && mat[i][j-1] > sum){
        mat[i][j-1] = sum;
        enqueue(i,j-1,q);
    }
}

int shortest_path(int **mat, int n, int m){
    int min = INT_MAX;
    Queue q;
    int x,y;
    
    q.head = NULL;
    q.tail = NULL;
    
    trasf_mat(mat,n,m);
    
    for(int i = 0; i < n; i++){
        if(mat[i][m-1] > 0){
            mat[i][m-1] = 1;
            enqueue(i,m-1,&q);
        }
    }
    
    while(!dequeue(&q,&x,&y)) {
		update_cells(mat,n,m,x,y,&q);
	}
    
    for(int i = 0; i < n; i++){
        if(mat[i][0] > 0 && mat[i][0] < min) min = mat[i][0];
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

