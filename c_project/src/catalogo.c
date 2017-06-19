 #include "catalogo.h"

#define NUMEROS 10

// Alterar tamanho do catalogo para guardar ids( neste caso convertemos o long a char e guardamos
struct catalogo{
	AVL numero[NUMEROS];
};

Catalogo initCat(clone_func clone){
	int i;

	Catalogo cat = malloc(sizeof(struct catalogo));
	
	for(i = 0 ; i < NUMEROS ; i++){
		cat->numero[i] = initAVL(clone);
	}		
	
	return cat;
}

// dados tem de conter o ordenador
Catalogo insertCat(Catalogo cat, long ordenador) {
   long i;
    // ir buscar o primeiro numero, verificar se é mais rapido a converter a string ou a ir fazendo divisoes

    i = getFirstNumber(ordenador);

    cat->numero[i] = insertAVL(cat->numero[i], ordenador);

    return cat;
}

boolean isEmptyCat(Catalogo cat){
	
	int i, j = 0;

	for (i=0 ; i<NUMEROS && j==0;i++){
		if (!isEmptyAVL(cat->numero[i])) j++;
	}

	return j==0;
}

long sizeCat (Catalogo cat){
    int i;
    long tamanho = 0;
    for(i = 0 ; i < NUMEROS ; i++){
        tamanho += sizeAVL(cat->numero[i]);
    }
    return tamanho;
}

void updateContentCat(Catalogo cat, long ordenador, void * content){

    long i;

    i = getFirstNumber(ordenador);

    updateContentAVL(cat->numero[i],ordenador,content);

}
void *getContentCat(Catalogo cat, long ordenador){

    void * result;
    long i;

    i = getFirstNumber(ordenador);

    result = getContentAVL(cat->numero[i],ordenador);

    return result;
}

void freeCat(Catalogo cat,Funcao f){
	int i;

	for(i=0 ; i<NUMEROS ; i++)
		freeAVL(cat->numero[i],f);

	free(cat);

	return;
}

SET insertCatIntoSet(Catalogo cat, SET s, comp_func comparator){
    int i;

    for(i = 0 ; i < NUMEROS ; i++){
       s = insertSet(cat->numero[i],s,comparator);
    }

    return s;
}


SET insertCatIntoSetPrefix(Catalogo cat, SET s, comp_func comparator, char* prefix){

    int i;

    for(i = 0 ; i < NUMEROS ; i++){
        s = insertSetPrefix(cat->numero[i],s,comparator,prefix);
    }

    return s;
}
