#include "avl.h"

#define MAXBUFFER 87

typedef enum balance {LH, EH, RH} BalanceFactor;

typedef struct node{
    long data;
    void *conteudo;
    struct node *esquerda, *direita;
    BalanceFactor bal;
}* NODE;

struct avl{
	NODE head;
	long size;
    clone_func clone;
};



static NODE cloneNode(NODE nodo);
static void freeNode(NODE nodo,Funcao f);
static NODE balanceLeft(NODE nodo);
static NODE balanceRight(NODE nodo);
static NODE insertLeft(NODE nodo, NODE novo, int *up);
static NODE insertRight(NODE nodo, NODE novo, int *up);
static NODE rotateLeft(NODE nodo);
static NODE rotateRight(NODE nodo);
static NODE initNode(long data, void *conteudo, NODE esq, NODE dir);
static NODE insertNode(NODE nodo, NODE novo, int *up);
static SET insertNodeinSet(NODE a, SET s, comp_func comparator,clone_func clone);
static SET insertNodeinSetPrefix(NODE a, SET s, comp_func comparator, clone_func clone,char* prefix);


AVL initAVL(clone_func clone){

	AVL a = malloc(sizeof(struct avl));

    a->head = NULL;
	a->size = 0;
    a->clone = clone;

	return a;
}

long sizeAVL(AVL a){

    long r = 0;

    if (!a)
        return -1;

    r = a->size;
    return r;
}

AVL insertAVL(AVL a,long data){
	 
	 int up = 0;
	 if (!lookUpAVL(a, data)){
	 	NODE novo = initNode(data, NULL, NULL, NULL);
	 	a->head = insertNode(a->head, novo, &up);
	 	a->size++;
	 }

	 return a;
}

AVL cloneAVL(AVL a){
	AVL new;

	new = malloc(sizeof(struct avl));
	new->head = cloneNode(a->head);
	new->size = a->size;

	return new;
}

boolean isEmptyAVL(AVL a){
	return (a->size==0);
}

boolean lookUpAVL(AVL a, long data){
    if(!a){
        return FALSE;
    }
	NODE novo = a->head;
	long r;
	while(novo){
		r = novo->data - data;
		if(r<0) novo = novo->direita;
		else if(r>0) novo = novo->esquerda;
		else return TRUE;
	}
	return FALSE;
}

void freeAVL(AVL a,Funcao f){

	if(!a) return;
	freeNode(a->head,f);
	free(a);

	return;
}

static NODE cloneNode(NODE nodo){
	NODE novo = NULL;

	if(!nodo) return nodo;

	novo = malloc(sizeof(struct node));

	novo->data = nodo->data;
	novo->conteudo = nodo->conteudo;
	novo->bal = nodo->bal;
	novo->esquerda = cloneNode(nodo->esquerda);
	novo->direita = cloneNode(nodo->direita); 

	return novo;
}

static void freeNode(NODE nodo,Funcao f){

    if(nodo){
        freeNode(nodo->direita,f);
        freeNode(nodo->esquerda,f);

        if(nodo->conteudo){
            f(nodo->conteudo);
        }
        free(nodo);
    }
    return;
}

static NODE balanceLeft(NODE nodo){
  if (nodo -> esquerda -> bal == LH){
    nodo = rotateRight (nodo);
    nodo -> bal = EH;
    nodo -> direita -> bal = EH;
  } 
  else {
    nodo -> esquerda = rotateLeft (nodo->esquerda);
    nodo = rotateRight(nodo);

    switch (nodo -> bal){
      case EH:
        nodo -> esquerda -> bal = EH;
        nodo -> direita -> bal = EH;
        break;
      case LH:
        nodo -> esquerda -> bal = EH;
        nodo -> direita -> bal = RH;
        break;
      case RH:
        nodo -> esquerda -> bal = LH;
        nodo -> direita -> bal = EH;
    }
    nodo -> bal = EH;
  }
  return nodo;
}

static NODE balanceRight(NODE nodo){
  if (nodo->direita->bal == RH){
    nodo = rotateLeft (nodo);
    nodo -> bal = EH;
    nodo -> esquerda -> bal = EH;
  } else {
    nodo -> direita = rotateRight (nodo -> direita);
    nodo = rotateLeft(nodo);

    switch (nodo->bal){
      case EH:
        nodo -> esquerda -> bal = EH;
        nodo -> direita -> bal = EH;
        break;
      case LH:
        nodo -> esquerda -> bal = EH;
        nodo -> direita -> bal = RH;
        break;
      case RH:
        nodo -> esquerda -> bal = LH;
        nodo -> direita -> bal = EH;
    }
    nodo -> bal = EH;
  }
  return nodo;
}


static NODE insertLeft(NODE nodo, NODE novo, int *up){
 nodo -> esquerda = insertNode(nodo -> esquerda, novo, up);

  if (*up){
    switch (nodo -> bal){
      case RH:
        nodo -> bal = EH;
        *up = 0;
        break;
      case EH:
        nodo -> bal = LH;
        *up = 1;
        break;
      case LH:
        nodo = balanceLeft(nodo);
        *up = 0;
    }
  }
  return nodo;
}

static NODE insertRight(NODE nodo, NODE novo, int *up){
	nodo -> direita = insertNode(nodo -> direita, novo, up);

  if (*up){
    switch (nodo -> bal) {
      case LH:
        nodo -> bal = EH;
        *up = 0;
        break;
      case EH:
        nodo -> bal = RH;
        *up = 1;
        break;
      case RH:
        nodo = balanceRight(nodo);
        *up = 0;
    }
  }
  return nodo;
}



static NODE rotateLeft(NODE nodo){
	NODE aux = NULL;
  	if (!nodo || !(nodo->direita))
    	return 0;
  	aux = nodo -> direita;
  	nodo -> direita = aux -> esquerda;
  	aux -> esquerda = nodo;
  	nodo = aux;
  return nodo;
}

static NODE rotateRight(NODE nodo){
	 NODE aux = NULL;

  if (!nodo || !(nodo->esquerda))
    return 0;
  aux = nodo->esquerda;
  nodo -> esquerda = aux -> direita;
  aux -> direita = nodo;
  nodo = aux;

  return nodo;
}

static NODE initNode(long data, void *conteudo, NODE esq, NODE dir){
	NODE novo = NULL;

	novo = (NODE) malloc(sizeof(struct node));
    novo->data = data;
    novo->conteudo = conteudo;
	novo->esquerda = esq;
	novo->direita = dir;
    novo->bal = EH;
	return novo;
}

static NODE insertNode(NODE nodo, NODE novo, int *up){

    long r;

    if (!nodo){
    *up = 1;
    return novo;
    }
    r =  novo->data - nodo->data;

    if (r > 0)
        nodo = insertRight(nodo,novo,up);
    else if (r < 0)
        nodo = insertLeft(nodo,novo,up);

    return nodo;
}

void updateContentAVL(AVL a,long data, void *conteudo){
	long comp;
	NODE novo = a->head;


	while(novo){
		comp = novo->data - data;

		if(comp == 0){
			novo->conteudo = conteudo;
		}
		if(comp < 0 ) novo = novo->direita;
		else novo = novo->esquerda;
	}
}

void * getContentAVL(AVL a, long data){
	NODE novo = a->head;
	long comp;

	while(novo){

		comp = novo->data - data;
		if(comp == 0) return novo->conteudo;
		if(comp < 0) novo = novo->direita;
		else novo = novo->esquerda;
	}

	return NULL;
}

SET insertSet(AVL a, SET s, comp_func comparator){

    if (a){
       if(a->clone)
           s = insertNodeinSet(a->head,s,comparator,a->clone);
       else
           s = insertNodeinSet(a->head,s,comparator,NULL);
    }

    return s;
}

SET insertSetPrefix(AVL a, SET s, comp_func comparator, char* prefix){

    if(a){
        if(a->clone)
            s = insertNodeinSetPrefix(a->head,s,comparator,a->clone,prefix);
        else
            s = insertNodeinSetPrefix(a->head,s,comparator,NULL,prefix);
    }

    return s;
}

static SET insertNodeinSet(NODE a, SET s, comp_func comparator, clone_func clone){
    long id;
    if(a) {
        s = insertNodeinSet(a->esquerda, s, comparator,clone);

        id = a->data;
        if(clone) {
            s = insertElem(s,id, clone(a->conteudo), comparator);
        }
        else
            s = insertElem(s,id,a->conteudo,comparator);

        s = insertNodeinSet(a->direita, s, comparator,clone);
    }
    return s;
}

static SET insertNodeinSetPrefix(NODE a, SET s, comp_func comparador, clone_func clone, char* prefix){
    if(a){
        s = insertNodeinSetPrefix(a->esquerda,s,comparador,clone,prefix);

        if(clone)
            s = insertElemPrefix(s,a->data,clone(a->conteudo),prefix,comparador);
        else
            s = insertElemPrefix(s,a->data,a->conteudo,prefix,comparador);


        s = insertNodeinSetPrefix(a->direita,s,comparador,clone,prefix);
    }
    return s;
}
