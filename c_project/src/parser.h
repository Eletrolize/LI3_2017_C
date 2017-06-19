//! \file parser.h Header file que garante o data hiding da implementação do parser, necessário para lidar com os snapshots input em formato xml.
#ifndef __PARSER_H__
#define  __PARSER_H__


#include <string.h>
#include <stdlib.h>
#include <libxml/parser.h>
#include <time.h>
#include "catartigos.h"
#include "catcontribuidores.h"
#include <libxml/xmlmemory.h>

/*! 
  * \brief Conta os artigos presentes em todos os snapshots analisados.
  * \param catA Catálogo de artigos.
  * \param catC Catálogo de contribuidores.
  * \param *filename Ficheiro input para parse.
  */
void parseFile(CatArtigos catA, CatContribuidores catC, char *fileName);

#endif