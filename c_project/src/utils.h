//! \file utils.h Header file que garante o data hiding da implementação de algumas funções úteis.
#ifndef PROGRAM_UTILS_H
#define PROGRAM_UTILS_H

typedef int boolean;

#define FALSE (0)
#define TRUE (!FALSE)


typedef boolean (*comp_func) (void*, void*);
typedef void(*Funcao)(void*);
typedef void*(*clone_func) (void*);

/*!
  * \brief Retorna o primeiro dígito de um dado número.
  * \param number Número sobre o qual se pretende identificar o primeiro dígito
  */
long getFirstNumber(long number);


/*! 
  * \brief Retorna o número máximo de caracteres do prefixo entre duas palavras.
  * \param str1 Palavra que poderá ser um prefixo da segunda.
  * \param str2 Segunda palavra sobre a qual se verifica se a primeira é um sufixo.
  */
int maiorPrefix(char* str1, char* str2);

#endif //PROGRAM_UTILS_H
