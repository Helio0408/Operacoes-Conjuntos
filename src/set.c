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
static NO* no_busca(NO *raiz, int elemento);
static bool no_inserir(NO **raiz, int elemento, int prioridade);
static void no_remover(NO **raiz, int elemento);
static void no_uniao(NO *no, SET *C);

static NO *no_rotacionarEsquerda(NO *raiz);
static NO *no_rotacionarDireita(NO *raiz);
static void no_imprimir(NO* raiz);
static void no_apagar(NO *no);
static void no_apagarArvore(NO *no);
static void no_uniao(NO *no, SET *C);

static NO *no_criar(int elemento, int prioridade){
	NO *no = (NO*) malloc(sizeof(NO));
	no->elemento = elemento;
	no->prioridade = prioridade;
	no->esq = no->dir = NULL;

	return no;
}

static NO* no_busca(NO *raiz, int elemento){
	if(raiz->elemento == elemento)
		return raiz;

	if(raiz->elemento > elemento)
		return no_busca(raiz->esq, elemento);
	else
		return no_busca(raiz->dir, elemento);
}

static bool no_inserir(NO **raiz, int elemento, int prioridade){
	bool aux;
	NO **comp;

	if(*raiz == NULL){
		*raiz = no_criar(elemento, prioridade);
	}
	
	if(elemento < (*raiz)->elemento){
		comp = &((*raiz)->esq);
	}else if(elemento > (*raiz)->elemento){
		comp = &((*raiz)->dir);
	}else
		return false;
		
	aux = no_inserir(comp, elemento, prioridade);

	if(aux && (*comp)->prioridade > (*raiz)->prioridade){
		if((*comp) == (*raiz)->esq)
			*raiz = no_rotacionarDireita(*raiz);
		else
			*raiz = no_rotacionarEsquerda(*raiz);
	}

	return true;
}

static void no_remover(NO **raiz, int elemento){
	NO *tmp;

	if(*raiz == NULL) return;

	if(elemento < (*raiz)->elemento){
		no_remover(&((*raiz)->esq), elemento);
		return;
	}
	else if(elemento > (*raiz)->elemento){
		no_remover(&((*raiz)->dir), elemento);
		return;
	}

	if(elemento != (*raiz)->elemento) return;

	if((*raiz)->esq == NULL && (*raiz)->dir == NULL){
		no_apagar(*raiz);
		*raiz = NULL;
	}
	else if((*raiz)->esq == NULL){
		tmp = *raiz;
		*raiz = (*raiz)->dir;
		no_apagar(tmp);
	}
	else if((*raiz)->dir == NULL){
		tmp = *raiz;
		*raiz = (*raiz)->esq;
		no_apagar(tmp);
	}
	else{
		if((*raiz)->esq->prioridade < (*raiz)->dir->prioridade){
			*raiz = no_rotacionarEsquerda(*raiz);
		}
		else{
			*raiz = no_rotacionarDireita(*raiz);
		}

		no_remover(raiz, elemento);
	}
}

static void no_uniao(NO *no, SET *C){
	if(no == NULL)
		return;
	
	set_inserir(C, no->elemento);

	no_uniao(no->esq, C);
	no_uniao(no->dir, C);
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

static void no_imprimir(NO* raiz){
	if(raiz == NULL) return;

	no_imprimir(raiz->esq);
	printf("%d ", raiz->elemento);
	no_imprimir(raiz->dir);
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

static void no_uniao(NO *no, SET *C){
	if(no == NULL)
		return;
	
	set_inserir(C, no->elemento);

	no_uniao(no->esq, C);
	no_uniao(no->dir, C);
}

SET *set_criar(void){
	SET *s;

	s = (SET*)malloc(sizeof(SET));
	s->raiz = NULL;
	
	return s;
}

bool set_pertence(SET *A, int elemento){
	if(no_busca(A->raiz, elemento) != NULL)
		return true;
	else
		return false;
}

bool set_inserir(SET *s, int elemento){
	return no_inserir(&s->raiz, elemento, rand() % 1000);
}

bool set_remover(SET *s, int elemento){
	if(!no_busca(s->raiz, elemento)) return false;

	no_remover(&s->raiz, elemento);

	return true;
}

void set_apagar(SET **s){
	no_apagarArvore((*s)->raiz);
	free(*s);
	*s = NULL;
}

void set_imprimir(SET *s){
	no_imprimir(s->raiz);
	printf("\n");
}

SET *set_uniao(SET *A, SET *B){
	SET *C;
	
	C = set_criar();

	no_uniao(A->raiz, C);
	no_uniao(B->raiz, C);

	return C;
}

SET *set_interseccao(SET *A, SET *B){
	SET *C;
	return NULL;
}
