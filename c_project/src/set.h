//! \file set.h Header file que garante o data hiding da implementação das estruturas de dados Sets.
#ifndef __SET_H__
#define  __SET_H__


#include <stdlib.h>
#include <string.h>
#include "utils.h"

typedef struct set *SET;


/*! 
  * \brief Inicializa um SET.
  * \param cap Tamanho máximo do SET.
  * \param lck Variável que determina se o SET será dinâmico ou estático.
  * \param f Função de comparação.
  */
SET initSet(int cap, boolean lck, Funcao f);

/*! 
  * \brief Liberta a memória ocupada por um SET.
  * \param st SET cuja memória vai ser libertada.
  */
void freeSet(SET st);

/*! 
  * \brief Retorna um ID de um dado SET.
  * \param st SET do qual se pretende extrair o id.
  * \param position Posição, no SET, do ID que se pretende retornar.
  */
long getSetId(SET st, int position);

/*!
  * \brief Retorna o conteúdo de um dado SET.
  * \param st SET do qual se pretende extrair o conteúdo.
  * \param position Posição, no SET, do conteúdo que se pretende retornar.
  */
void* getSetContent(SET st, int position);

/*!
  * \brief Retorna o tamanho de um dado SET.
  * \param st SET que se pretende conhecer o tamanho.
  */
int getSetSize(SET st);

/*!
  * \brief Insere um elemento num SET.
  * \param st SET onde se pretende inserir um elemento.
  * \param id ID do elemento a ser inserido.
  * \param pointer Apontador para a estrutura a ser inserida.
  * \param comparator Função de comparação.
  */
SET insertElem(SET st, long id, void* pointer, comp_func comparator);

/*!
 * \brief Insere um elemento num SET.
  * \param st SET onde se pretende inserir um elemento.
  * \param id ID do elemento a ser inserido.
  * \param pointer Apontador para a estrutura a ser inserida.
  * \param prefix Prefixo a ser comparado.
  * \param comparador Função de comparação.
  */
SET insertElemPrefix(SET s,long id, void* pointer, char* prefix, comp_func comparator);

/*!
  * \brief Ordena um dado SET por id.
  * \param st SET a ser ordenado.
  */
void idSort(SET st);

/*!
  * \brief Ordena um dado SET segundo a função de comparação passada.
  * \param st SET a ser ordenado.
  * \param comparator Função de coparação.
  */
void setSort(SET st,comp_func comparator);


#endif
