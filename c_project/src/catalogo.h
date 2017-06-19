//! \file catalogo.h Header file que garante o data hiding da implementação da estrutura catalogo, que corresponde a um array de árvores binárias balanceadas.
#ifndef __CATALOGO_H__
#define __CATALOGO_H__

#include <stdlib.h>
#include "utils.h"
#include "avl.h"

typedef struct catalogo *Catalogo;


/*!
  * \brief Inicializa um catálogo que corresponde a um array de árvores binárias balanceadas.
  * \param clone Função que realiza o clone da estrutura de dados guardada no catalogo.
  */
Catalogo initCat(clone_func clone);


/*! 
  * \brief Insere um catálogo de acordo com um ordenador passado como argumento.
  * \param cat Catálogo que se pretende inserir no array.  
  * \param ordenador Parâmetro segundo o qual o Catálogo será ordenado.
  * \details A inserção no catalogo é dependente do primeiro número de cada ordenador.
  */
Catalogo insertCat(Catalogo cat, long ordenador);


/*! 
  * \brief Atualiza o conteúdo de um catálogo.
  * \param cat Catálogo no qual se pretende atualizar o seu conteúdo.
  * \param ordenador Elemento a inserir no catálogo
  * \param content Conteúdo que se pretende atualizar no catálogo.
  */
void updateContentCat(Catalogo cat, long ordenador, void *content);


/*! 
  * \brief Retorna o conteúdo de um catálogo.
  * \param cat Catálogo no qual se pretende retirar o conteúdo.
  * \param ordenador Elemento do qual será retirado o conteúdo.
  * \details Retorna NULL caso nao encontro o elemento.
  */
void *getContentCat(Catalogo cat, long ordenador);


/*! 
  * \brief Testa se um catálogo se encontra vazio.
  * \param cat Catálogo que se pretende verificar se encontra-se vazio.
  */
boolean isEmptyCat(Catalogo cat);


/*! 
  * \brief Calcula o tamanho de um catálogo.
  * \param cat Catálogo que se pretende conhecer o tamanho.
  */
long sizeCat(Catalogo cat);


/*! 
  * \brief Liberta todos os elementos de um catálogo.
  * \param cat Catálogo que se pretende libertar/eliminar.
  * \param f Apontador para a função responsável por fazer free dos elementos que se encontram no catálogo.
  */
void freeCat(Catalogo cat,Funcao f);

/*!
 * Inserção de um Catálogo no SET.
 * \param cat Catalogo que se pretende inserir na estrutura (SET).
 * \param s SET que vai conter o Catálogo.
 * \param comparator Função de comparação.
*/
SET insertCatIntoSet(Catalogo cat, SET s, comp_func comparator);

/*!
 * Inserção de um Catálogo no SET.
 * \param cat Catalogo que se pretende inserir na estrutura (SET).
 * \param s SET que vai conter o Catálogo.
 * \param comparator Função de comparação.
 * \param prefix Prefixo a ser comparado.
*/
SET insertCatIntoSetPrefix(Catalogo cat, SET s, comp_func comparator, char* prefix);

#endif
