
#include "revisao.h"

// Uma revisao (nao existe repetição de revisoes)
typedef struct elemento{
	long idRevisao;
	char *data;
	char *nomeContribuinte;
	long reviewTextSize;
	long idContribuinte;
    long wordNumber;
}* Elemento;

// associado a um id de um artigo, guardar o titulo
struct revisao{
    long tamanho;
    long capacidade;
	char *articleName;
	Elemento *list;
};

static Elemento newElemento(char **dados);
static void freeElemento(Elemento first);
// static long maxWordsRev(Revisao r1);
static long maxTextSize(Revisao r1);
static Elemento cloneElemento(Elemento elemento);

Revisao initRevisao(long capacidade){
    Revisao review = malloc(sizeof(struct revisao));

    review->capacidade = capacidade;
    review->tamanho = 0;
    review->articleName = malloc(MAXBUFFER);
    review->list = malloc(sizeof(Elemento) * capacidade);

    return review;
}

Revisao addRevisao(Revisao review,char **dados, boolean* unico){

    Elemento elem;

    long size = review->tamanho;

    if (size == review->capacidade){
        review->capacidade *= 2;
        review->list = realloc(review->list,review->capacidade * sizeof(Elemento));
    }

    long id = strtol(dados[1],NULL,10);
    if (!searchRevisaoIdArtigo(review,id)){
        elem = newElemento(&dados[1]);
        review->list[size] = elem;
        review->tamanho++;
        (*unico) = TRUE;
    }
    else{

    }

    //Copia do titulo, para o caso de este ser mudado.
    strcpy(review->articleName,dados[0]);

    return review;
}


boolean searchRevisaoIdArtigo(Revisao review, long id) {
    int i;

    if(!review)
        return FALSE;

    for(i = 0 ; i < review->tamanho ; i++){
        if(review->list[i]->idRevisao == id){
            return TRUE;
        }
    }

    return FALSE;
}

char *getArticleName(Revisao review){
    char *name;
	if (!review)
		return NULL;
    name = malloc(MAXBUFFER);
	strcpy(name, review->articleName);
    return name;
}

char *getArticleTimeStamp(Revisao review,long idRevisao){

    char *result = NULL;
    int i;

    if(!review)
        return NULL;

    for( i = 0 ; i < review->tamanho ; i++){
        if(review->list[i]->idRevisao == idRevisao){
            result = malloc(MAXBUFFER);
            strcpy(result,review->list[i]->data);
        }
    }

    return result;
}

long getNumeroRevisoes(Revisao review){

    long r = 0;
    if(review){
        r = review->tamanho;
    }
    return r;
}


void freeRevisao(Revisao review){
	int i;

    if(!review)
        return;

    free(review->articleName);
    for(i = 0 ; i < review->tamanho ; i++){
        freeElemento(review->list[i]);
    }
    free(review->list);
    free(review);

    return;
}

static Elemento newElemento(char **dados){
	int i;
	Elemento first = malloc(sizeof(struct elemento));
    first->data = malloc(MAXBUFFER);
    first->nomeContribuinte = malloc(MAXBUFFER);
	for(i = 0 ; i < 6 ; i++){
		switch (i){
			case 0: first->idRevisao = strtol(dados[i],NULL,10);
					break;
			case 1: strcpy(first->data,dados[i]);
					break;
			case 2: strcpy(first->nomeContribuinte,dados[i]);
					break;
			case 3: first->idContribuinte = strtol(dados[i],NULL,10);
					break;
			case 4: first->reviewTextSize = strtol(dados[i],NULL,10);
					break;
            case 5: first->wordNumber = strtol(dados[i],NULL,10);
                    break;
            default: break;
        }
	}
	return first;
}

boolean compareWords(Revisao r1,Revisao r2){

    long text1 = maxWordsRev((Revisao) r1);
    long text2 = maxWordsRev((Revisao) r2);

    if(text1 > text2) return 1;
    if(text1 < text2) return -1;
    return 0;

}

//verifica, numa revisão, o Elemento com mais palavras
long maxWordsRev(Revisao r1){
    int i;
    long maior;

    if(!r1) return 0;
    maior = r1->list[0]->wordNumber;

    for(i=1; i < r1->tamanho; i++){
        if(maior < r1->list[i]->wordNumber) maior = r1->list[i]->wordNumber;
    }

    return maior;
}

int compareTextSize(Revisao r1, Revisao r2){

    long text1 = maxTextSize((Revisao)r1);
    long text2 = maxTextSize((Revisao)r2);

    if(text1 > text2) return 1;
    if(text1 < text2) return -1;
    return 0;

}

//verifica, numa revisao, qual o elemento com o maior texto( maior numero de bytes)
static long maxTextSize(Revisao r1){
    int i;
    long maior;

    if(!r1) return 0;
    maior = r1->list[0]->reviewTextSize;

    for(i=1; i < r1->tamanho; i++){
        if(maior < r1->list[i]->reviewTextSize) maior = r1->list[i]->reviewTextSize;
    }

    return maior;
}

boolean isPrefix(char* str, Revisao r1){
    int length = strlen(str);
    if(maiorPrefix(str, r1->articleName) == length) return TRUE;

    return FALSE;
}

static void freeElemento(Elemento elem){

    if(!elem)
        return;

    free(elem->data);
    free(elem->nomeContribuinte);

    free(elem);

    return;
}


Revisao cloneRevisao (Revisao review){
    if(!review)
        return NULL;
    int i;
    Revisao new = initRevisao(review->capacidade);
    for(i = 0 ; i < review->tamanho ; i++){
        new->list[i] = cloneElemento((Elemento) review->list[i]);
    }
    strcpy(new->articleName,review->articleName);
    new->tamanho = review->tamanho;
    new->capacidade = review->capacidade;

    return new;
}

static Elemento cloneElemento(Elemento elemento){
    if(!elemento)
        return NULL;

    Elemento new;

    new = malloc(sizeof(struct elemento));

    new->data = malloc(MAXBUFFER);
    strcpy(new->data,elemento->data);
    new->wordNumber = elemento->wordNumber;
    new->idContribuinte = elemento->idContribuinte;
    new->reviewTextSize = elemento->reviewTextSize;
    new->nomeContribuinte = malloc(MAXBUFFER);
    strcpy(new->nomeContribuinte,elemento->nomeContribuinte);
    new->idRevisao = elemento->idRevisao;


    return new;
}
