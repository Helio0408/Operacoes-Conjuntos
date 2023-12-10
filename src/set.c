#include "set.h"

typedef struct no_s{
	int prioridade;
	int elemento;

	struct no_s *esq;
	struct no_s *dir;
} NO;

struct set{
	NO *raiz;
};

/* funções locais */
static NO* no_criar(int elemento, int prioridade);
static bool no_busca(NO *raiz, int elemento);
static void no_inserir(NO *raiz, int elemento, int prioridade);
static void no_remover(NO *raiz, int elemento);
static NO *no_rotacionarEsquerda(NO *raiz);
static NO *no_rotacionarDireita(NO *raiz);
static void no_apagar(NO *no);

static NO *no_criar(int elemento, int prioridade){
}

static bool no_busca(NO *raiz, int elemento){
}

static void no_inserir(NO *raiz, int elemento, int prioridade){
}

static void no_remover(NO *raiz, int elemento){
}

static NO* no_rotacionarEsquerda(NO *raiz){
}

static NO* no_rotacionarDireita(NO *raiz){
}

static void no_apagar(NO *no){
}

SET *set_criar(void){

}

bool set_pertence(SET *A, int elemento){

}

bool set_inserir (SET *s, int elemento){

}

bool set_remover(SET *s, int elemento){

}

void set_apagar(SET **s){

}

void set_imprimir(SET *s){

}

SET *set_uniao(SET *A, SET *B){

}

SET *set_interseccao(SET *A, SET *B){

}
