#include "catartigos.h"

struct catartigos{
	Catalogo artigo;
    long artigosRepetidos;
    long revisoesUnicas;
};

CatArtigos initCatArtigos(){

	CatArtigos cat = malloc(sizeof(struct catartigos));
    cat->artigosRepetidos = 0;
    cat->revisoesUnicas = 0;
	cat->artigo = initCat((clone_func) cloneRevisao);

	return cat;
}

CatArtigos insertCatArtigos(CatArtigos cat, long ord){

	cat->artigo = insertCat(cat->artigo, ord);

	return cat;
}

long sizeCatArtigos(CatArtigos cat){
	long i = 0;

	i = sizeCat(cat->artigo);

	return i;
}

void updateContentCatArtigos(CatArtigos cat, long ord, void *content){

	updateContentCat(cat->artigo, ord, content);
}

void *getContentCatArtigos(CatArtigos cat, long ord){

	void *resultado = getContentCat(cat->artigo, ord);

    return resultado;
}

boolean isEmptyCatArtigos(CatArtigos cat){
	boolean i;

	i = isEmptyCat(cat->artigo);

    return i;
}


void freeCatArtigos(CatArtigos cat){

	freeCat(cat->artigo,(Funcao) freeRevisao);
	free(cat);

	return;
}

SET moveCatArtigosToSet(CatArtigos cat,SET s,comp_func comparator){

    s = insertCatIntoSet(cat->artigo,s,comparator);

    return s;
}

SET moveCatArtigosForPrefix(CatArtigos cat,SET s,char *prefix){

    s = insertCatIntoSetPrefix(cat->artigo,s,(comp_func) isPrefix,prefix);

    return s;
}

CatArtigos addArtigosRepetidos(CatArtigos cat){
    cat->artigosRepetidos++;
    return cat;
}

CatArtigos addRevisoesUnicas(CatArtigos cat){
    cat->revisoesUnicas++;
    return cat;
}


long getArtigosRepetidos(CatArtigos cat){
    long r;
    r = cat->artigosRepetidos;
    return r;
}
long getRevisoesUnicas(CatArtigos cat){
    long r;
    r = cat->revisoesUnicas;
    return r;
}




