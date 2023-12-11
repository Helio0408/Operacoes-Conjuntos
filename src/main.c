#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "set.h"

/* Trabalho SET de algoritmos e estrutura de dados
 * Alunos:
 * Gabriel Martins Monteiro (N°USP: 14572099)
 * Hélio Márcio Cabral Santos (N°USP: 14577862) */

int main(){
	srand(time(NULL));
	SET *A, *B;
  	int n_a, n_b, x;
  	int num;
	int quit = 0;
	char op[20];
	char conjunto_atual;

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
  		scanf("%s", op); /* scanear operador */

		if(!strcmp(op, "quit")){
			quit = 1;
		}
		else if(!strcmp(op, "pertence")){
			scanf(" %c %d", &conjunto_atual, &num);

			if(conjunto_atual == 'a'){
				if(set_pertence(A, num)) printf("%d pertence ao conjunto a\n", num);
				else printf("%d nao pertence oa conjunto a\n", num);
			}
			else{
				if(set_pertence(B, num)) printf("%d pertence ao conjunto b\n", num);
				else printf("%d nao pertence oa conjunto b\n", num);
			}
		}
		else if(!strcmp(op, "uniao")){
			SET *C = set_uniao(A,B);
			printf("uniao: ");
			set_imprimir(C);
			set_apagar(&C);
		}
		else if(!strcmp(op, "interseccao")){
			SET *C = set_interseccao(A, B);
			printf("interseccao: ");
			set_imprimir(C);
			set_apagar(&C);
		}
		else if(!strcmp(op, "inserir")){
			scanf(" %c %d", &conjunto_atual, &num);

			if(conjunto_atual == 'a'){
				set_inserir(A,num);
			}
			else{
				set_inserir(B,num);
			}
		}
		else if(!strcmp(op, "remover")){
			scanf(" %c %d", &conjunto_atual, &num);

			if(conjunto_atual == 'a'){
				set_remover(A,num);
			}
			else{
				set_remover(B,num);
			}
		}
		else if(!strcmp(op, "imprimir")){
			printf("a: ");
			set_imprimir(A);
			printf("b: ");
			set_imprimir(B);
		}
	}

	set_apagar(&A);
	set_apagar(&B);
    
	return 0;
}
