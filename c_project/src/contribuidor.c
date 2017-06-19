#include "contribuidor.h"

struct item{
	char* nome;
	long nrContribuicoes;
};

Item initItem(){
	Item i = malloc(sizeof(struct item));
	i->nome = malloc(MAXBUFFER);
	i->nrContribuicoes = 0;

	return i;
}

Item addItem(Item i, char* str, long nr){

	strcpy(i->nome, str);
	i->nrContribuicoes = nr;

	return i;
}

Item cloneItem(Item i){
    Item new;

    if(!i)
        return NULL;

    new = initItem();
    strcpy(new->nome,i->nome);
    new->nrContribuicoes = i->nrContribuicoes;

    return new;
}


char* getNome(Item i){
    char *r;
    r = malloc(MAXBUFFER);
	if(!i) return NULL;
    strcpy(r,i->nome);
	return r;
}

Item setName(Item i, char *nome){
    if(i) strcpy(i->nome,nome);
    return i;
}

long getNrContribuicoes(Item i){
	if(!i) return -1;
	return i->nrContribuicoes;
}

void setNrContribuicoes(Item i, long contribuicao){

	if(i) i->nrContribuicoes = contribuicao;
}

Item addContribuicao(Item i){

	if(i) i->nrContribuicoes++;
    return i;
}

int maxContribuicoes(Item i1, Item i2){
	
	if(i1->nrContribuicoes > i2->nrContribuicoes) return 1;
	if(i1->nrContribuicoes < i2->nrContribuicoes) return -1;

    return 0;
}

void freeItem(Item i){

	if(!i) return;

	free(i->nome);
	free(i);

	return;
}
