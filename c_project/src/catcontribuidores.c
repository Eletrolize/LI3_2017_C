#include "catcontribuidores.h"

struct catcontribuidores{
	Catalogo contribuidores;
};

CatContribuidores initCatContribuidores(){
	CatContribuidores cat = malloc(sizeof(struct catcontribuidores));
	cat->contribuidores = initCat((clone_func) cloneItem);

	return cat;
}

CatContribuidores insertCatContribuidores(CatContribuidores cat, long ord){
	cat->contribuidores = insertCat(cat->contribuidores, ord);

	return cat;
}

long sizeCatContribuidores(CatContribuidores cat){
	long i;

	i = sizeCat(cat->contribuidores);

	return i;
}

void updateContentCatContribuidores(CatContribuidores cat, long ord, void *content){

	updateContentCat(cat->contribuidores, ord, content);
}

void *getContentCatContribuidores(CatContribuidores cat, long ord){
	void *resultado = getContentCat(cat->contribuidores, ord);
    return resultado;
}

boolean isEmptyContribuidores(CatContribuidores cat){
	boolean i;

	i = isEmptyCat(cat->contribuidores);

	return i;
}

void freeCatContribuidores(CatContribuidores cat){

	freeCat(cat->contribuidores,(Funcao) freeItem);
	free(cat);

	return;
}

SET moveCatContribuidoresToSet(CatContribuidores cat,SET s,comp_func comparator){

    s = insertCatIntoSet(cat->contribuidores,s,comparator);

    return s;
}


