#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "set.h"

int main(){
	srand(time(NULL));
	SET *A, *B;
  	int n_a, n_b, x;
  	int op, num;
	int quit = 0;

	A = set_criar();
	B = set_criar();

	scanf("%d %d", &n_a, &n_b);

	for(int i=0; i<n_a; i++){
		scanf("%d",&x);
		set_inserir(A, x);
	}
	
	for(int i=0; i<n_b; i++){
    	scanf("%d",&x);
    	set_inserir(B, x);
  	}

	while(!quit){
  		scanf("%d", &op);

		switch(op){
			case 0: {
				quit = 1;
				break;
			}
			case 1: {
				scanf("%d", &num);
				if(set_pertence(A,num)) 
					printf("Pertence.\n");
				else
					printf("Nao Pertence.\n");
				break;
    		}
    		case 2: {
				SET *C = set_uniao(A,B);
				printf("Uniao: ");
				set_imprimir(C);
				set_apagar(&C);
				break;
    		}
    		case 3: {
				SET *C = set_interseccao(A, B);
				printf("Interseccao: ");
				set_imprimir(C);
				set_apagar(&C);
				break;
    		}
    		case 4: {
				int num;
				scanf("%d", &num);
				set_remover(A,num);
				set_imprimir(A); 
				break;
    		}
    		case 5: {
				printf("A: ");
				set_imprimir(A); 
				printf("B: ");
				set_imprimir(B); 
				break;
    		}
		}
	}

	set_imprimir(A);
	set_imprimir(B);

	set_apagar(&A);
	set_apagar(&B);
    
	return 0;
}
