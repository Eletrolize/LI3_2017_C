//! \file interface.h Header file que garante o data hiding da implementação das interrogações.
#ifndef __INTERFACE_H__
#define  __INTERFACE_H__

#include "src/parser.h"


typedef struct TCD_istruct *TAD_istruct;

/*! 
  * \brief Inicializar a estrutura TAD_istruct.
  */
TAD_istruct init();

/*! 
  * \brief Carregar a estrutura TAD_istruct, com os snapshots apresentados.
  * \param qs Tipo abstrato de dados.
  * \param nsnaps Número de snapshots.
  * \param snaps_paths[] Conjunto dos snapshots.
  */
TAD_istruct load(TAD_istruct qs, int nsnaps, char *snaps_paths[]);

/*! 
  * \brief Conta os artigos presentes em todos os snapshots analisados.
  * \param qs Tipo abstrato de dados.
  * \details Os artigos duplicados em snapshots sucessivos e novas revisões de artigos são contabilizados.
  */
long all_articles(TAD_istruct qs);


/*! 
  * \brief Conta os artigos distintos presentes em todos os snapshots analisados.
  * \param qs Tipo abstrato de dados.
  * \details Apenas são contabilizados os artigos com identificadores distintos, sendo ignorados os artigos duplicados ou revisões dos mesmos.
  */
long unique_articles(TAD_istruct qs);


/*! 
  * \brief Conta as revisões presentes em todos os snapshots analisados.
  * \param qs Tipo abstrato de dados.
  * \details  Retorna o número de revisões unicas presentes nos snapshots analisados.
  */
long all_revisions(TAD_istruct qs);


/*! 
  * \brief Conta as revisões dos contribuidores, devolvendo os 10 identificadores daqueles que mais revisões fizeram.
  * \param qs Tipo abstrato de dados.
  * \details Caso hajam contribuidores com o mesmo número de revisões, ordena-os pelo seu identificador de forma crescente.
  */
long *top_10_contributors(TAD_istruct qs);


/*! 
  * \brief Retorna o nome de um contribuidor correspondente a um dado identificador. 
  * \param contributor_id Identificador de um contribuidor.
  * \param qs Tipo abstrato de dados. 
  * \details Caso não haja um contribuidor com o identificador explicitado, é retornado o valor NULL.
  */
  char *contributor_name(long contributor_id, TAD_istruct qs);


/*! 
  * \brief Identifica os artigos com maior texto (tamanho em bytes), devolvendo os 20 identificadores daqueles com mais tamanho.
  * \param qs Tipo abstrato de dados.
  * \details Caso hajam artigos com o mesmo tamanho, ordena-os pelo seu identificador de forma crescente.
  */
long *top_20_largest_articles(TAD_istruct qs);


/*! 
  * \brief Dado um determinado identificador de artigo, devolve o seu título.
  * \param article_id Identificador de artigo.
  * \param qs Tipo abstrato de dados.
  * \details Caso não haja um artigo com o identificador explicitado, é retornado o valor NULL.
  * \details Caso um artigo tenha várias revisões, é considerado o título da revisão mais recente do artigo.
  */
char *article_title(long article_id, TAD_istruct qs);


/*! 
  * \brief Identifica os artigos com maior número de palavras, devolvendo os 'n' identificadores daqueles que apresentam maior contagem de forma crescente.
  * \param n Número de artigos com mais palavras desejado.
  * \param qs Tipo abstrato de dados.
  * \details Caso hajam artigos com o mesmo número de palavras, ordena-os pelo seu identificador de forma crescente.
  */
long *top_N_articles_with_more_words(int n, TAD_istruct qs);


/*! 
  * \brief Devolve os titulos dos artigos que contêm o prefixo especificado, ordenados alfabéticamente.
  * \param *prefix Prefixo que vai ser procurado nos títulos.
  * \param qs Tipo abstrato de dados.
  * \details Caso os títulos tenham sido alterados em algumas revisões, é considerado o título da revisão mais recente do artigo.
  * \details O array de títulos termina com o elemento NULL.
  */
char **titles_with_prefix(char *prefix, TAD_istruct qs);


/*! 
  * \brief Devolve o timestamp para uma certa revisão/versão de um dado artigo.
  * \param article_id Identificador de artigo.
  * \param revision_id Identificador de revisão.
  * \param qs Tipo abstrato de dados.
  * \details Caso não haja a revisão para o artigo específico, é retornado o valor NULL.
  */
char *article_timestamp(long article_id, long revision_id, TAD_istruct qs);


/*! 
  * \brief Liberta todos os recursos associados à TAD_istruct.
  * \param qs Tipo abstrato de dados. 
  */
TAD_istruct clean(TAD_istruct qs);


#endif
