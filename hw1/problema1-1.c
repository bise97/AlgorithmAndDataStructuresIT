/* INPUT:
Alberto Barbato Cicogna ENDL
Alfredo Benny Carlo Daniele ENDL
Antonio Biagio Casper Drusilla Francesco Ernesto ENDL
END

L'input è nel formato:
nome1 nome2 ... nome2n ENDL (per terminare la lista i-esima)
...
END (per terminare l'input) */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
    char name[20];
    struct Node *next;
} Node;

typedef struct List{
    Node *head;
    int len;
} List;

void list_insert(List *l, Node *n);
int create_list(List *l);
void print_list(List l);
Node* reverse_list(Node *head);
void reverse_half_list(List *l);

void list_insert(List *l, Node *n){
    n->next = l->head;
    l->head = n;
}

int create_list(List *l){
    char buff[20];
    int dim = 0;
    Node *n;
    
    scanf("%s",buff);
    
    if(strcmp(buff,"END") == 0){
        return 0;
        
    }else
    {
        while( strcmp(buff,"ENDL") ){
    	    dim++;
    	    n = (Node *) malloc (sizeof(Node));
    	    strcpy(n->name,buff);
    	    list_insert(l,n);
    	    scanf("%s",buff);
    	}
    	l->head = reverse_list(l->head);
    	l->len = dim;
    }
	return 1;
}

void print_list(List l){
    Node *x = l.head;
    while(x != NULL){
        printf("%s ",x->name);
        x = x->next;
    }
}

Node* reverse_list(Node *head){
    Node* new_head;
    if(head->next == NULL){
        new_head = head;
    }
    else{
        new_head = reverse_list(head->next);
        head->next->next = head;
        head->next = NULL;
    }
    return new_head;
}

void reverse_half_list(List *l){
    int n;
    Node *x, *h;
    
    x = l->head;
    n = l->len / 2;
    
    for(int i = 0 ; i < n-1 ; i++){
        x = x->next;
    }
    
    h = reverse_list(x->next);
    
    x->next = h;
}

void clean_list(List *l){
    Node *x, *y;
    x = l->head;
    while(x != NULL){
        y = x->next;
        free(x);
        x = y;
    }
    l->head = NULL;
    l->len = 0;
}

int main(void) {
	// your code goes here
	List l;
	l.head = NULL;
	l.len = 0;
	
	while(create_list(&l)==1){
	    reverse_half_list(&l);
	
	    print_list(l);
	    printf("\n");
	    clean_list(&l);
	};
	
	
    
	return 0;
}
