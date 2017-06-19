//! \file contribuidor.h Header file que garante o data hiding da implementação da estrutura item, que guarda informação acerca de cada contribuidor.
#ifndef __CONTRIBUIDOR_H__
#define  __CONTRIBUIDOR_H__

#include <stdlib.h>
#include <string.h>

#define MAXBUFFER 128

typedef struct item *Item;


/*! 
  * \brief Inicializa uma estrutura que guarda informação acerca de um contribuidor.
  */
Item initItem();


/*! 
  * \brief Atualiza o nome e número de contribuições de um dado contribuidor.
  * \param i Contribuidor que se pretende atualizar.
  * \param str Nome do contribuidor que se pretende atualizar no item.
  * \param nr Número de contribuições que se pretende atualizar no item.
  */
Item addItem(Item i, char* str, long nr);


/*! 
  * \brief Retorna o nome de um dado contribuidor.
  * \param i Contribuidor do qual se pretende conhecer o nome. 
  */
char* getNome(Item i);

/*! 
  * \brief Retorna um clone da estrutura passada como argumento.
  * \param i Item que se pretende clonar. 
  */
Item cloneItem(Item i);


/*! 
  * \brief Atualiza o nome de um dado contribuidor.
  * \param i Contribuidor para o qual se pretende atualizar o nome. 
  * \param nome Nome que se pretende atualizar no contribuidor.
  */
Item setName(Item i,char *nome);


/*! 
  * \brief Retorna o número de contribuições de um contribuidor.
  * \param i Contribuidor para o qual se pretende conhecer o número de contribuições.
  */
long getNrContribuicoes(Item i);


/*! 
  * \brief Atualiza o número de contribuições de um dado contribuidor.
  * \param i Contribuidor para o qual se pretende atualizar o número de contribuições. 
  * \param contribuicao Número de contribuições que se pretende atualizar no contribuidor.
  */
void setNrContribuicoes(Item i, long contribuicao);


/*! 
  * \brief Atualiza mais uma contribuição no número de contribuições de um dado contribuidor.
  * \param i Contribuidor para o qual se pretende atualizar o número de contribuições. 
  */
Item addContribuicao(Item i);


/*! 
  * \brief Limpa todos os elementos da estrutura que representa um contribuidor, eliminando-a.
  * \param i Contribuidor que se pretende libertar/eliminar.
  */
void freeItem(Item i);


/*! 
  * \brief Dados dois contribuidores, testa qual deles tem o maior número de contribuições .
  * \param i1 Um dos contribuidores que se pretende comparar quanto ao número de contribuições.
  * \param i2 Um dos contribuidores que se pretende comparar quanto ao número de contribuições.
  * \details Esta função retorna: -1 caso o primeiro contribuidor tenha menos contribuições que o segundo; 0 caso os dois contribuidores tenham o mesmo número de contribuições; 1 caso o primeiro contribuidor tenha mais contribuições que o segundo;   
  */
int maxContribuicoes(Item i1, Item i2);

#endif
