//! \file revisao.h Header file que garante o data hiding da implementação da estrutura revisao, que guarda informação acerca de cada revisão. 
#ifndef __REVISAO_H__
#define  __REVISAO_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"

#define MAXBUFFER 128


typedef struct revisao *Revisao;

/*! 
  * \brief Cria uma nova revisão.
  * \param capacidade Tamanho que se pretende para a revisão criada.
  */
Revisao initRevisao(long capacidade);

/*! 
  * \brief Adiciona uma revisão.
  * \param review Revisão que se pretende adicionar.
  * \param dados Array com os dados a inserir dentro da revisão
  * \param unico Endereço de boolean para indicar se a revisão inserida é única ou não.
  */
Revisao addRevisao(Revisao review,char **dados, boolean* unico);


/*! 
  * \brief Testa se um dado artigo possui determinada revisão.
  * \param review Revisão que se pretende procurar.
  * \param id Identificador de artigo.
  */
boolean searchRevisaoIdArtigo(Revisao review,long id);


/*! 
  * \brief Retorna o título dada uma revisão.
  * \param review Revisão da qual se pretende retirar o título.
  */
char *getArticleName(Revisao review);


 /*! 
  * \brief Retorna o número total de revisões (repetidas e não repetidas). 
  * \param review Revisão da qual se pretende saber o número total de revisões.
  */
long getNumeroTotal(Revisao review);


/*! 
  * \brief Retorna o número de revisões não repetidas.
  * \param review Revisão da qual se pretende saber o número de revisões.
  */
long getNumeroRevisoes(Revisao review);


/*! 
  * \brief Limpa todos os parâmetros de uma revisão, eliminando-a.
  * \param review Revisão que se pretende libertar/eliminar.
  */
void freeRevisao(Revisao review);


/*! 
  * \brief Retorna o timestamp da revisão de um dado artigo.
  * \param review Revisão da qual se pretende o timestamp.
  * \param id Identificar de artigo.
  */
char *getArticleTimeStamp(Revisao review, long id);


/*! 
  * \brief Clone de uma revisão.
  * \param review Revisão que se pretende clonar.
  */
Revisao cloneRevisao(Revisao review);


/*! 
  * \brief Testa se a palavra dada é prefixo do título de uma dada revisão.
  * \param str Palavra que se pretende verificar se é um prefixo do título da revisão.
  * \param r1 Revisão cujo título se pretende comparar.
  */
boolean isPrefix(char* str, Revisao r1);


/*!
  * \brief Compara o máximo de palavras presente em cada uma das revisões passadas
  * \param review1 Primeira revisão a comparar
  * \param review2 Segunda revisão a comparar
  * \details Retorna 0 se o número máximo de palavras é igual entre as duas revisões, 1 se a primeira revisão tiver um número superior e -1 se a segunda tiver um valor superior.
  */
int compareWords(Revisao review1, Revisao review2);

/*!
  * \brief Compara o tamanho máximo do texto (em bytes) que existe entre duas revisões
  * \param review1 Primeira revisão a comparar
  * \param review2 Segunda revisão a comparar
  * \details Retorna 0 se o tamanho maximo do texto de ambas as revisões for igual, 1 se a primeira revisão tiver um número superior e -1 se a segunda tiver um valor superior.
  */
int compareTextSize(Revisao review1, Revisao review2);

long maxWordsRev(Revisao r1);

#endif
