//! \file catcontribuidores.h Header file que garante o data hiding da implementação da estrutura catcontibuintes, que correponde a um array de árvores binárias balanceadas com informações dos contribuidores.
#ifndef __CATCONTRIBUIDORES_H__
#define __CATCONTRIBUIDORES_H__

#include "catalogo.h"
#include "contribuidor.h"

typedef struct catcontribuidores *CatContribuidores;


/*! 
  * \brief Inicializa um catálogo de contribuidores, ou seja, um array de árvores binárias balanceadas com a informação dos contribuidores.
  */
CatContribuidores initCatContribuidores();


/*! 
  * \brief Insere um catálogo de contribuidores.
  * \param cat Catálogo de contribuidores que se pretende inserir.
  * \param ord Elemento que se pretende inserir.
  */
CatContribuidores insertCatContribuidores(CatContribuidores cat, long ord);


/*! 
  * \brief Calcula o tamanho de um catálogo de contribuidores.
  * \param cat Catálogo de contribuidores que se pretende conhecer o tamanho.
  */
long sizeCatContribuidores(CatContribuidores cat);


/*! 
  * \brief Atualiza o conteúdo de um catálogo de contribuidores .
  * \param cat Catálogo de contribuidores no qual se pretende atualizar o seu conteúdo.
  * \param ord Elemento a dar update no catálogo de contribuidores
  * \param content Conteúdo que se pretende atualizar no catálogo de contribuidores.
  */
void updateContentCatContribuidores(CatContribuidores cat, long ord, void *content);


/*! 
  * \brief Retorna o conteúdo de um catálogo de contribuidores.
  * \param cat Catálogo de contribuidores no qual se pretende extrair o conteúdo. 
  * \param ord Elemento do qual se pretende extrair o conteúdo.
  */
void *getContentCatContribuidores(CatContribuidores cat, long ord);

/*! 
  * \brief Testa se um catálogo de contribuidores se encontra vazio.
  * \param cat Catálogo de contribuidores que se pretende verificar se encontra-se vazio.
  */
  boolean isEmptyContribuidores(CatContribuidores cat);


/*! 
  * \brief Limpa todos os elementos de um catálogo de contribuidores, eliminando-o.
  * \param Cat Catálogo de contribuidores que se pretende libertar/eliminar.
  */
  void freeCatContribuidores(CatContribuidores cat);

/*!
 * Inserção de um Catálogo de Contribuidores no SET.
 * \param cat Catalogo que se pretende inserir na estrutura (SET).
 * \param s SET que vai conter o Catálogo.
 * \param comparator função de comparação.
*/
SET moveCatContribuidoresToSet(CatContribuidores cat,SET s,comp_func comparator);


#endif
