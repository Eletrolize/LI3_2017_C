#include "set.h"	


typedef struct elem{
	long id;
	void* pointer;
}*ELEM;

struct set{
	ELEM *list;
	int size;
	int capacity;
	boolean locked;
	Funcao f;
};

static void swapContent(SET st, long i, long j);
static long idPartition(SET st,long init, long end);
static ELEM newElem (long id, void* pointer);
static void freeELEM(ELEM elemento,Funcao f);
static void idQuickSort(SET st,long init, long end);
static long partition(SET set, long init, long end, comp_func comparator);
static void quicksort(SET st, long init, long end, comp_func comparator);

SET initSet(int cap, boolean lck, Funcao f){
	
	SET newSet = malloc(sizeof(*newSet));
	newSet->list = malloc(sizeof(ELEM)*cap);
	newSet->size = 0;
	newSet->capacity = cap;
	newSet->f = f;
	newSet->locked = lck;

	return newSet;	  
}


void freeSet(SET st){
	
	if(st!=NULL){
		for(int i = 0; i < st->size; i++){
	        freeELEM(st->list[i],st->f);
		}
		free(st->list);
		free(st);
	}
}

static void freeELEM(ELEM elemento,Funcao f){

    if(!f)
        return;
    f(elemento->pointer);
    free(elemento);

    return;
}



long getSetId(SET st, int position){

	long newId;
	if (position >=0 && position <= st->size){
		newId = st->list[position]->id;
		return (newId);
	}
	else return -1;

}


void* getSetContent(SET st, int position){

	if (position >=0 && position <= st->size){
		return (st->list[position]->pointer);
	}
	else return NULL;
}


int getSetSize(SET st){
	return (st->size);
}


static ELEM newElem (long id, void* pointer){

	ELEM newElem = malloc(sizeof(*newElem));
	newElem->id = id;
	newElem->pointer = pointer;

	return newElem;
}


SET insertElem(SET st, long id, void* pointer, comp_func comparator){

	ELEM tmp;
	// se estiver fechado
	if (st->locked) {
            //se tamanho==capacidade
        if (st->size == st->capacity) {
                // comparar pointer com o ultimo
                // se igual
            if (comparator(pointer,st->list[st->size-1]->pointer) == 0){
                    // verificar se o id do ultimo é menor.
                    // se o presente for maior
                if (id < st->list[st->size-1]->id) {
                        // troca
                    // free atual
                    freeELEM(st->list[st->size-1],st->f);
                    // meter no sitio do anterior o novo
                    tmp = newElem(id,pointer);
                    st->list[st->size-1] = tmp;
                    // ordenar
                    setSort(st, comparator);
                }
                else{
                    st->f(pointer);
                }
            }
                // se o presente for menor que o a inserir
            else if(comparator(pointer,st->list[st->size-1]->pointer) == 1){
                // trocar
                // free atual
                freeELEM(st->list[st->size-1],st->f);
                // meter no sitio do anterior o novo
                tmp = newElem(id,pointer);
                st->list[st->size-1] = tmp;
                // ordenar

                setSort(st,comparator);
            }
                // se o presente for maior que o a inserir
            else if(comparator(pointer,st->list[st->size-1]->pointer) == -1){
                st->f(pointer);
            }
        }
        else{

            ELEM newEleme = newElem(id, pointer);
            st->list[st->size] = newEleme;
            st->size++;

        }
    }
	else {
        if (st->size == st->capacity) {
            st->capacity = st->capacity * 2;
            st->list = realloc(st->list, st->capacity * sizeof(ELEM));
        }

        ELEM newEleme = newElem(id, pointer);
        st->list[st->size] = newEleme;
        st->size++;
        //ordenar
        idSort(st);
    }

	return st;
}


SET insertElemPrefix(SET s,long id, void* pointer, char* prefix, comp_func comparador){

    if(!s)
        return s;

    if(s->locked)
        return s;

    if(s->size == s->capacity){
        s->capacity = s->capacity * 2;
        s->list = realloc(s->list,s->capacity * sizeof(ELEM));
    }

    if(comparador(prefix,pointer)){
        ELEM new = newElem(id,pointer);
        s->list[s->size] = new;
        s->size++;
    }
    else{
        s->f(pointer);
    }

    return s;
}


static void swapContent(SET st, long i, long j){
	
	ELEM tmp = st->list[i];
	st->list[i] = st->list[j];
	st->list[j] = tmp;
}


static long idPartition(SET st,long init, long end){
	
	long pivot = st->list[end]->id;
	long i, limit = init-1;

	for (i = init; i < end; i++) {
        if ((st->list[i]->id) <= pivot) {
            limit++;
            swapContent(st, limit, i);
        }
    }

    swapContent(st, limit+1, end);
	return limit+1;
}


void idSort(SET st){


	long init = 0, end = st->size-1;
    idQuickSort(st,init,end);

}

static void idQuickSort(SET st,long init, long end){

    long limit;

    if(init < end){
        limit = idPartition(st,init,end);
        idQuickSort(st,init,limit-1);
        idQuickSort(st,limit+1,end);
    }

}


void setSort(SET st,comp_func comparator){

    quicksort(st,0,st->size-1,comparator);

}

static long partition(SET set, long init, long end, comp_func comparator){
    ELEM* list = set->list;
    void* pivot = set->list[end]->pointer;
    long i, limit = init-1;

    for (i = init; i < end; i++){
        if (comparator(list[i]->pointer, pivot) >= 0){
            limit++;
            swapContent(set,limit,i);
        }
    }

    swapContent(set, limit+1, end);
    return limit+1;
}


static void quicksort(SET st, long init, long end, comp_func comparator){
    long limit;

    if (init < end) {
        limit = partition(st, init, end, comparator);

        quicksort(st, init, limit-1, comparator);
        quicksort(st, limit+1, end, comparator);
    }
}
