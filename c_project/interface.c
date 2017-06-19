#include "interface.h"


struct TCD_istruct{
    CatArtigos artigos;
    CatContribuidores contributors;
};

static void sortAlphabetically(char** titulos,int size);
static void quickSortAlphabetically(char** titulos, int init, int end);
static int partitionAlphabetically(char** titulos, int init, int end);
static void swapString(char** titulos, int i1, int i2);

TAD_istruct init(){
	TAD_istruct estrutura = malloc(sizeof(struct TCD_istruct));
	estrutura->artigos = initCatArtigos();
	estrutura->contributors = initCatContribuidores();
	return estrutura;
}


//
TAD_istruct load(TAD_istruct qs, int nsnaps, char *snaps_paths[]){
	int i;
	for(i = 0 ; i < nsnaps ; i++){
        parseFile(qs->artigos,qs->contributors,snaps_paths[i]);
    }
	
	return qs;
}


// contar revisoes de todos os snapshots
long all_articles(TAD_istruct qs) {
    if(!qs) return -1;

    long r;
    r = getArtigosRepetidos(qs->artigos);
    r+=sizeCatArtigos(qs->artigos);
    return r;
}


// contar numero de artigos
long unique_articles(TAD_istruct qs){
	if (!qs)
		return -1;
	return sizeCatArtigos(qs->artigos);
}


// contar revisoes unicas
long all_revisions(TAD_istruct qs){

    long r;

    r = getRevisoesUnicas(qs->artigos);
    //r = sizeCatArtigos(qs->artigos);

    return r;

}

//contributors com mais revisoes, se tiverem nº igual, ordenar por identificador (crescente)
long *top_10_contributors(TAD_istruct qs){

    long * r;

    SET contributors;
    int i;

    r = malloc(sizeof(long)*10);

    contributors = initSet(10,TRUE,(Funcao) freeItem);

    moveCatContribuidoresToSet(qs->contributors,contributors,(comp_func)maxContribuicoes);

//    setSort(contributors, (comp_func) maxContribuicoes);
    for(i = 0 ; i < 10 ; i++) {
         r[i] = getSetId(contributors, i);
    }
    freeSet(contributors);

    return r;
}


// nome do contribuidor, com determinado identificador
char *contributor_name(long contributor_id, TAD_istruct qs){
    char *r;

    Item contributor;

    contributor = getContentCatContribuidores(qs->contributors,contributor_id);

    if(contributor){
        r = getNome(contributor);
        return  r;
    }

    freeItem(contributor);

    return NULL;
}

// artigos com maior texto (contar a revisao com mais texto)
long *top_20_largest_articles(TAD_istruct qs){
    long *r;


    SET artigos;
    int i;

    r = malloc(sizeof(long)*20);

    artigos = initSet(20,TRUE,(Funcao) freeRevisao);

    moveCatArtigosToSet(qs->artigos,artigos,(comp_func)compareTextSize);

    for(i = 0 ; i < 20 ; i++){
        r[i] = getSetId(artigos, i);
		Revisao r = getSetContent(artigos,i);
		printf("NR_BYTES:%ld  ", maxWordsRev(r));
	}

    freeSet(artigos);

    return r;
}


//
char *article_title(long article_id, TAD_istruct qs){
    char *r;

    Revisao review;

    review = getContentCatArtigos(qs->artigos,article_id);

    if(review){
        r = getArticleName(review);
        return r;
    }

    freeRevisao(review);

    return NULL;
}

//
long *top_N_articles_with_more_words(int n, TAD_istruct qs){
    long *r;


    SET artigos;
    int i;

    r = malloc(sizeof(long)*n);

    artigos = initSet(n,TRUE,(Funcao) freeRevisao);

    moveCatArtigosToSet(qs->artigos,artigos,(comp_func)compareWords);

    for(i = 0 ; i < n ; i++){
        r[i] = getSetId(artigos, i);
     }

    freeSet(artigos);

    return r;
}


//
char **titles_with_prefix(char *prefix, TAD_istruct qs){
    char ** r;

    SET artigos;

    artigos = initSet(1,FALSE,(Funcao) freeRevisao);

    moveCatArtigosForPrefix(qs->artigos,artigos,prefix);

    int size = getSetSize(artigos);
    r = malloc(sizeof(char*)*size+1);

    int i;

    for(i = 0 ; i < size ; i++ ){
        r[i] = malloc(MAXBUFFER);
        Revisao new = getSetContent(artigos,i);
        char* title = getArticleName(new);
        r[i] = title;
    }

    sortAlphabetically(r,size-1);
    r[size] = NULL;
    freeSet(artigos);
    return r;
}

static void sortAlphabetically(char** titulos,int size){
    quickSortAlphabetically(titulos,0,size);
}

static void quickSortAlphabetically(char** titulos, int init, int end){

    int limit;

    if(init < end){
        limit = partitionAlphabetically(titulos,init,end);

        quickSortAlphabetically(titulos,init,limit-1);
        quickSortAlphabetically(titulos,limit+1,end);
    }

}

static int partitionAlphabetically(char** titulos, int init, int end){
    char* pivot = titulos[end-1];
    int i, limit = init-1;

    for(i = init; i < end ; i++){
        if(strcmp(titulos[i],pivot) <= 0){
            limit++;
            swapString(titulos,limit,i);
        }
    }

   // swapString(titulos,limit+1,end);

    return limit+1;
}

static void swapString(char** titulos, int i1, int i2){
    char * tmp = titulos[i1];
    titulos[i1] = titulos[i2];
    titulos[i2] = tmp;
}

//
char *article_timestamp(long article_id, long revision_id, TAD_istruct qs){
    char *r;

    Revisao review;

    review = getContentCatArtigos(qs->artigos,article_id);

    if(review){
        r = getArticleTimeStamp(review,revision_id);
        return r;
    }

    return NULL;
}


//
TAD_istruct clean(TAD_istruct qs){
	if (!qs)
		return qs;
	freeCatArtigos(qs->artigos);
    freeCatContribuidores(qs->contributors);
	free(qs);
	return NULL;
}


