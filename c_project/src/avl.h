//! \file avl.h Header file que garante o data hiding da implementação das árvores binárias balanceadas
#ifndef __AVL_H__
#define __AVL_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "set.h"


typedef struct avl *AVL;

/*! 
  * \brief Inicializa a estrutura para uma árvore binária balanceada, alocando o espaço em memória necessário.
  * \param clone Função de clone da estrutura guardada no apontador de cada nodo.
  * \details A cabeça da árvore é inicializada a NULL e o seu tamanho a 0.
  */
AVL initAVL (clone_func clone);


/*! 
  * \brief Insere dados numa árvore binária balanceada organizando-a por data.
  * \param a Árvore binária balanceada onde se pretende inserir.
  * \param data Dados que se pretendem inserir.
  */
AVL insertAVL (AVL a, long data);


/*! 
  * \brief Testa se uma árvore binária balanceada se encontra vazia.
  * \param a Árvore binária balanceada que se pretende verificar se está vazia.
  * \details Para testar se a árvore se encontra vazia, verifica se o tamanho dela é 0.
  */
boolean isEmptyAVL(AVL a);


/*! 
  * \brief Testa se já existe um nodo com este data numa dada árvore binária balanceada.
  * \param a Árvore binária balanceada onde se pretende procurar.
  * \param data
  * \details Procura tanto no ramo da esquerda como no ramo da direita se existe algum nodo com este data na árvore, retornado TRUE em caso afirmativo.
  */
boolean lookUpAVL(AVL a, long data);


/*! 
  * \brief Retorna o tamanho de uma dada árvore binária balanceada.
  * \param a Árvore binária balanceada sobre a qual se pretende calcular o tamanho.
  */
long sizeAVL(AVL a);


/*! 
  * \brief Liberta todos os elementos de uma árvore binária balanceada.
  * \param a Árvore binária balanceada que se pretende libertar/eliminar.
  * \param f Apontador para a função responsável por fazer free do conteúdo dos nodos que se encontram na árvore.
  */
void freeAVL(AVL a,Funcao f);


/*! 
  * \brief Clona uma árvore binária balanceada.
  * \param a Árvore binária balanceada que se pretende clonar.
  */
AVL cloneAVL(AVL a);


/*! 
  * \brief Atualiza o conteúdo de uma árvore binária balanceada.
  * \param a Árvore binária balanceada na qual se pretende atualizar o conteúdo.
  * \param data Elemento do qual se pretende atualizar o conteúdo.
  * \param conteudo Conteúdo que se pretende atualizar na árvore binária balanceada.
  */
void updateContentAVL(AVL a,long data, void *conteudo);


/*! 
  * \brief Retorna o conteúdo de uma árvore binária balanceada.
  * \param a Árvore binária balanceada que se pretende extrair o conteúdo.
  * \param data Elemento do qual se pretende extrair o conteúdo.
  */
void * getContentAVL(AVL a, long data);

/*!
 * \brief Passagem dos dados da Árvore binária para a estrutura SET.
 * \param a Árvore binária balanceada que se pretende extrair o conteúdo.
 * \param s SET onde serão guardados os dados da Árvora binária.
 * \param comparator Função de comparação.
 */
SET insertSet(AVL a,SET s,comp_func comparator);

/*!
 * Passagem dos dados da Árvore binária para a estrutura SET
 * \param a Árvore binária balanceada que se pretende extrair o conteúdo.
 * \param s SET onde serão guardados os dados da Árvora binária.
 * \param comparator Função de comparação.
 * \param prefix Prefixo a ser comparado.
*/
SET insertSetPrefix(AVL a, SET s, comp_func comparator, char* prefix);

#endif 
