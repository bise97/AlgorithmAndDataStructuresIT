/* INPUT:
a b c d e f 0

L'input è nel formato:
c1 c2 c3 c4 ... 0(per terminare) */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

typedef struct Node{
    char key;
    int priority;
    struct Node *parent;
    struct Node *left;
    struct Node *right;
}Node;

typedef struct Tree{
    Node *root;
}Tree;

void left_rotate(Tree *t, Node *x){
    Node *y;
    y = x->right;
    
    x->right = y->left;
    if(y->left != NULL){
        y->left->parent = x;
    }
    
    y->parent = x->parent;
    if(x->parent != NULL){
        if(x == x->parent->left){
            x->parent->left = y;
        }
        else{
            x->parent->right = y;
        }
    }
    else{
        t->root = y;
    }
    
    y->left = x;
    x->parent = y;
}

void right_rotate(Tree *t, Node *x){
    Node *y;
    y = x->left;
    
    x->left = y->right;
    if(y->right != NULL){
        y->right->parent = x;
    }
    
    y->parent = x->parent;
    if(x->parent != NULL){
        if(x == x->parent->left){
            x->parent->left = y;
        }
        else{
            x->parent->right = y;
        }
    }
    else{
        t->root = y;
    }
    
    y->right = x;
    x->parent = y;
}

void tree_insert(Tree *t, Node *x){
    Node *y, *z;
    
    y = NULL;
    z = t->root;
    
    while(z != NULL){
        y = z;
        
        if(x->key < z->key){
            z = z->left;
        }
        else{
            z = z->right;
        }
    }
    
    x->parent = y;
    
    if(y == NULL){
        t->root = x;
    }
    else{
        if(x->key < y->key){
            y->left = x;
        }
        else{
            y->right = x;
        }
    }
}

void treap_insert_fixup(Tree *t, Node *x){
    Node *y;
    
    y = x->parent;
    
    while(y != NULL && x->priority < y->priority){
        
        if(x == y->left){
            right_rotate(t,y);
        }
        else{
            left_rotate(t,y);
        }
        y = x->parent;
    }
}

void treap_insert(Tree *t, Node *x){
    tree_insert(t,x);
    treap_insert_fixup(t,x);
}

//codice per la stampa dell'output
bool array_null(Node **v, int dim){
    int i = 0;
    
    while(i<dim && v[i]==NULL) i++;
    if(i<dim) return false;
    else return true;
}

void print_level(Node **v,int liv){
    Node **w;
    char p[4];
    
    if(array_null(v,pow(2,liv))){
        return;
    }
    else{
       w = (Node**)malloc(sizeof(Node*)*pow(2,liv+1));
       for(int i = 0; i < pow(2,liv); i++){
           if(v[i] == NULL){
               printf("(NULL) ");
               w[2*i] = NULL;
               w[2*i + 1] = NULL;
           }
           else{
               if(v[i]->parent != NULL){
                   p[0] = v[i]->parent->key;
                   p[1] = '\0';
               }
               else{
                   p[0] = 'N';
                   p[1] = 'I';
                   p[2] = 'L';
                   p[3] = '\0';
               }
               printf("(%c:%d,%s) ",v[i]->key,v[i]->priority,p);
               w[2*i] = v[i]->left;
               w[2*i + 1] = v[i]->right;
           }
       }
       printf("\n");
       print_level(w,liv+1);
       free(w);
    }
}

void print_tree(Tree *t){
    
    Node *v[1];
    v[0] = t->root;
    
    print_level(v,0);

}
//fine codice stampa output

int main(void) {
	// your code goes here
	Tree t;
	Node *x;
	char k;
	
	t.root = NULL;
	
	srand(time(NULL));
	
	k = getchar();
	while(k != '0'){
	    x = (Node*)malloc(sizeof(Node));
	    x->key = k;
	    x->priority = rand()%100;
	    x->parent = NULL;
	    x->left = NULL;
	    x->right = NULL;
	    
	    treap_insert(&t,x);
	    
	    getchar();
	    k = getchar();
	}
	
	print_tree(&t);
	
	return 0;
}

