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
static void no_inter(NO *A, NO *B, SET *C);
static NO *no_rotacionarEsquerda(NO *raiz);
static NO *no_rotacionarDireita(NO *raiz);
static void no_imprimir(NO* raiz);
static void no_apagar(NO *no);
static void no_apagarArvore(NO *no);

static NO *no_criar(int elemento, int prioridade){
	NO *no = (NO*) malloc(sizeof(NO));
	no->elemento = elemento;
	no->prioridade = prioridade;
	no->esq = no->dir = NULL;

	return no;
}

static NO* no_busca(NO *raiz, int elemento){
	/* realiza uma busca binária de forma recursiva, caso o elemento
	 * não seja achado, retorna nulo */
	if(raiz == NULL) return NULL;

	if(raiz->elemento == elemento)
		return raiz;

	if(raiz->elemento > elemento)
		return no_busca(raiz->esq, elemento);
	else
		return no_busca(raiz->dir, elemento);
}

static bool no_inserir(NO **raiz, int elemento, int prioridade){
	/* realiza a inserção de um elemento e retorna verdadeiro caso 
	 * possível adicionar */
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

	/* após a inserção, verificar se é necessário a rotação para manter em ordem
	 * de prioridade do heap */
	if(aux && (*comp)->prioridade > (*raiz)->prioridade){
		if((*comp) == (*raiz)->esq)
			*raiz = no_rotacionarDireita(*raiz);
		else
			*raiz = no_rotacionarEsquerda(*raiz);
	}

	return true;
}

static void no_remover(NO **raiz, int elemento){
	/* essa função realiza a remoção de um elemento */
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
		/* se um elemento for uma folha, é necessário apenas removê-lo */ 
		no_apagar(*raiz);
		*raiz = NULL;
	}
	else if((*raiz)->esq == NULL){
		/* Nesse caso e no seguinte, o nó possui apenas um filho, então apenas
		 * substituímos o nó por esse filho */
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
		/* Nesse caso, o nó possui dois filhos. Para removê-lo, é necessário
		 * transformar o problema em um dos casos anteriores. Para isso, utilizamos
		 * a rotação.
		 * Para manter a ordem de prioridade do heap, rotacionamos à esquerda caso
		 * o elemento à esquerda tenha menor prioridade. Caso contrário, rotacionamos
		 * à direita */
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
	/* para realizar a união, basta percorrer o treap e adicionar
	 * cada elemento desejado no SET */
	if(no == NULL)
		return;
	
	set_inserir(C, no->elemento);

	no_uniao(no->esq, C);
	no_uniao(no->dir, C);
}

static void no_inter(NO *A, NO *B, SET *C){
	/* Para realizar a intersecção, basta percorrer o treap A e ver
	 * se cada elemento desse treap também está no treap B. */
	if(A == NULL) return;

	if(no_busca(B, A->elemento)){
		set_inserir(C, A->elemento);
	}

	no_inter(A->esq, B, C);
	no_inter(A->dir, B, C);
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
	/* A impressão realizada nesse caso é impressão em ordem */
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

/* Para as funções seguintes, basta chamar as funções estáticas
 * locais contidas nesse arquivo */

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
	return no_inserir(&s->raiz, elemento, rand() % 100000);
}

bool set_remover(SET *s, int elemento){
	/* Necessário realizar uma busca para ver se o elemento
	 * a ser removido está de fato lá */
	if(no_busca(s->raiz, elemento) == NULL) return false;

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

	C = set_criar();

	no_inter(A->raiz, B->raiz, C);

	return C;
}
