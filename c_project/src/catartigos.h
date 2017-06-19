//! \file catartigos.h Header file que garante o data hiding da implementação da estrutura catartigos, ou seja, um array de árvores binárias balanceadas com informação dos artigos.
#ifndef __CATARTIGOS_H__
#define __CATARTIGOS_H__

#include "catalogo.h"
#include "revisao.h"

typedef struct catartigos *CatArtigos;

/*! 
  * \brief Inicializa um catálogo de artigos, ou seja, um array de árvores binárias balanceadas com informação dos artigos.
  */
CatArtigos initCatArtigos();


/*! 
  * \brief Insere um catálogo de artigos.
  * \param cat Catálogo de artigos que se pretende inserir.
  * \param ord Elemento a inserir no catálogo de artigos.
  */
CatArtigos insertCatArtigos(CatArtigos cat, long ord);


/*! 
  * \brief Calcula o tamanho de um catálogo de artigos.
  * \param cat Catálogo de artigos que se pretende conhecer o tamanho.
  */
long sizeCatArtigos(CatArtigos cat);


/*! 
  * \brief Atualiza o conteúdo de um catálogo de artigos .
  * \param cat Catálogo de artigos no qual se pretende atualizar o seu conteúdo.
  * \param ord Elemento que se pretende atualizar o conteúdo.
  * \param content Conteúdo que se pretende atualizar no catálogo de artigos.
  */
void updateContentCatArtigos(CatArtigos cat, long ord, void *content);


/*! 
  * \brief Retorna o conteúdo de um catálogo de artigos.
  * \param cat Catálogo de artigos no qual se pretende extrair o conteúdo. 
  * \param ord Elemento do qual se pretende extrair o conteúdo.
  */
void *getContentCatArtigos(CatArtigos cat, long ord);


/*! 
  * \brief Testa se um catálogo de artigos se encontra vazio.
  * \param cat Catálogo de artigos que se pretende verificar se encontra-se vazio.
  */
boolean isEmptyArtigos(CatArtigos cat);


/*! 
  * \brief Limpa todos os elementos de um catálogo de artigos, eliminando-o.
  * \param cat Catálogo de artigos que se pretende libertar/eliminar.
  */
void freeCatArtigos(CatArtigos cat);

/*!
 * Inserção de um Catálogo de Artigos no SET.
 * \param cat Catalogo que se pretende inserir na estrutura (SET).
 * \param s SET que vai conter o Catálogo.
 * \param comparator Função de comparação.
*/
SET moveCatArtigosToSet(CatArtigos cat,SET s,comp_func comparator);

/*!
 * Inserção de um Catálogo de Contribuidores no SET.
 * \param cat Catalogo que se pretende inserir na estrutura (SET).
 * \param s SET que vai conter o Catálogo.
 * \param prefix Prefixo a ser comparado.
*/
SET moveCatArtigosForPrefix(CatArtigos cat,SET s,char *prefix);

/*!
 * Incrementa o número de artigos repetidos.
 * \param cat Catalogo que se pretende inserir na estrutura (SET).
*/
CatArtigos addArtigosRepetidos(CatArtigos cat);

/*!
 * Incrementa o número de revisões únicas.
 * \param cat Catalogo que se pretende inserir na estrutura (SET).
*/
CatArtigos addRevisoesUnicas(CatArtigos cat);

/*!
 * Retorna o número de artigos repetidos.
 * \param cat Catalogo que se pretende inserir na estrutura (SET).
*/
long getArtigosRepetidos(CatArtigos cat);

/*!
 * Retorna o número de revisões únicas.
 * \param cat Catalogo que se pretende inserir na estrutura (SET).
*/
long getRevisoesUnicas(CatArtigos cat);

#endif
