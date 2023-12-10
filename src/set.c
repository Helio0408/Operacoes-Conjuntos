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
static void no_apagarArvore(NO *no);

static NO *no_criar(int elemento, int prioridade){
	NO *no = (NO*) malloc(sizeof(NO));
	no->elemento = elemento;
	no->prioridade = prioridade;
	no->esq = no->dir = NULL;

	return no;
}

static bool no_busca(NO *raiz, int elemento){
	return false;
}

static void no_inserir(NO *raiz, int elemento, int prioridade){
}

static void no_remover(NO *raiz, int elemento){
	if(!no_busca(raiz, elemento)) return;
	NO* pai = raiz;
	NO* filho = raiz;

	while(1){
		if(elemento == filho->elemento){
			break;
		}
		else if(elemento < filho->elemento){
			pai = filho;
			filho = filho->esq;
		}
		else{
			pai = filho;
			filho = filho->dir;
		}
	}

	if(filho->esq == NULL && filho->dir == NULL){
		if(filho == pai->esq) pai->esq = NULL;
		if(filho == pai->dir) pai->dir = NULL;

		free(filho);
	}
	else if(filho->esq == NULL){
		if(filho == pai->esq) pai->esq = NULL;
		if(filho == pai->dir) pai->dir = NULL;

		filho->elemento = filho->dir->elemento;
		filho->prioridade = filho->dir->prioridade;
		free(filho->dir);
	}
	else if(filho->dir == NULL){
		if(filho == pai->esq) pai->esq = NULL;
		if(filho == pai->dir) pai->dir = NULL;

		filho->elemento = filho->esq->elemento;
		filho->prioridade = filho->esq->prioridade;
		free(filho->esq);
	}
	else{
		NO* tmp;
		/* rotaciona para esquerda para manter a ordem de heap */
		if(filho->dir->prioridade > filho->esq->prioridade){
			tmp = no_rotacionarEsquerda(filho);
		}
		else tmp = no_rotacionarDireita(filho);

		if(filho == pai->esq) pai->esq = tmp;
		if(filho == pai->dir) pai->dir = tmp;

		no_remover(tmp, elemento);
	}
}

static NO* no_rotacionarEsquerda(NO *raiz){
	NO *aux;

	aux = raiz->dir;
	raiz->dir = aux->esq;
	aux->esq = raiz;

	return aux;
}

static NO* no_rotacionarDireita(NO *raiz){
	NO *aux;

	aux = raiz->esq;
	raiz->esq = aux->dir;
	aux->dir = raiz;

	return aux;
}

static void no_apagar(NO *no){
	free(no);
}

static void no_apagarArvore(NO *no){
	if(no == NULL) return;

	no_apagarArvore(no->esq);
	no_apagarArvore(no->dir);

	no_apagar(no);
}

SET *set_criar(void){
	return NULL;
}

bool set_pertence(SET *A, int elemento){
	return no_busca(A->raiz, elemento);
}

bool set_inserir(SET *s, int elemento){
	no_inserir(s->raiz, elemento, rand());

	return true;
}

bool set_remover(SET *s, int elemento){
	if(!no_busca(s->raiz, elemento)) return false;

	no_remover(s->raiz, elemento);

	return true;
}

void set_apagar(SET **s){

}

void set_imprimir(SET *s){

}

SET *set_uniao(SET *A, SET *B){
	return NULL;
}

SET *set_interseccao(SET *A, SET *B){
	return NULL;
}
