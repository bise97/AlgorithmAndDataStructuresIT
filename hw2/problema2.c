#include <stdio.h>
#include <stdlib.h>

unsigned long dp (int n, unsigned long *mem){
    if(mem[n] == 0){
        mem[n] = dp(n-1,mem) + (n-1)*dp(n-2,mem);
    }

    return mem[n];
}

int main(void) {
	// your code goes here
	int n;
	unsigned long ris;
	unsigned long *mem;
	
	while( scanf("%d",&n) != EOF){
	   mem = (unsigned long*)malloc(sizeof(unsigned long)*n+1);
	   for(int i = 0; i < n+1; i++) mem[i] = 0;
	   mem[1] = 1;
	   mem[2] = 2;
	   
	   ris = dp(n,mem);
	   
	   printf("%lu\n",ris);
	   free(mem);
	}
	return 0;
}

CASI DI TEST:
3
5
15

