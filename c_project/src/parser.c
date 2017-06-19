#include "parser.h"

static void parseArticle(char **dados, xmlDocPtr doc, xmlNodePtr cur);
static void parseRevision(char **dados, xmlDocPtr doc, xmlNodePtr cur);
static void parseContributor(char **dados, xmlDocPtr doc, xmlNodePtr cur);
static void insertStructures(char **dados, CatArtigos catArtigos, CatContribuidores catContribuidores,boolean* revisoesUnicas,boolean * artigoRepetido);
static void countWordsAndBytes(xmlChar *text, long *word, long *bytes);

// retorna endereço do array com as cenas todas
// dados[0] = idArtigo
// dados[1] = title
// dados[2] = revisionId
// dados[3] = dataRevisao
// dados[4] = username/ip
// dados[5] = idContribuidor
// dados[6] = textSize
// dados[7] = wordNumber

void parseFile(CatArtigos catA, CatContribuidores catC,char *file){

	int tamanhoDados = 10;
	xmlDocPtr doc;
	xmlNodePtr cur;
	xmlNodePtr aux;
    boolean artigoRepetido = FALSE;
    boolean revisoesUnicas = FALSE;
	char **dados;
	dados = (char **) malloc(sizeof(char *)*tamanhoDados);
	int i;


	// alocar memória para o array dos dados a inserir
	for(i = 0 ; i < tamanhoDados ; i++){
		dados[i] = (char *) malloc(MAXBUFFER);
	}

	doc = xmlParseFile(file);

    if (!doc){
		fprintf(stderr,"Falha no parse do documento. \n");
		return;
	}


	cur = xmlDocGetRootElement(doc);

	if (!cur){
		fprintf(stderr,"Documento vazio!\n");
		return;
	}

	cur = cur->xmlChildrenNode;

	for(i = 0 ; cur ; cur = cur->next){
        aux = cur;
        if(!xmlStrcmp(cur->name,(const xmlChar *)"page")){
			parseArticle(dados,doc,cur);
			insertStructures(dados,catA,catC,&revisoesUnicas,&artigoRepetido);
            i++;
		}
		cur = aux;
	}



	// free do array para os dados
    for(i = 0 ; i < tamanhoDados ; i++){
		free(dados[i]);
	}

	free(dados);
	
	xmlFreeDoc(doc);


	return;
}

static void insertStructures(char **dados,CatArtigos catArtigos, CatContribuidores catContribuidores,boolean *revisoesUnicas,boolean *artigosRepetidos){

	Revisao review;
    Item contribuidor;

	if(!catArtigos){
		return;
	}
    if(!catContribuidores){
        return;
    }
    // id do artigo
    long ordenador = strtol(dados[0],NULL,10);
	catArtigos = insertCatArtigos(catArtigos,ordenador);
	review = getContentCatArtigos(catArtigos,ordenador);
	if (!review){
		review = initRevisao(1);
		review = addRevisao(review, &dados[1],revisoesUnicas);
		updateContentCatArtigos(catArtigos,ordenador,review);
	}
	else{
        (*artigosRepetidos)=TRUE;
        review = addRevisao(review, &dados[1],revisoesUnicas);
        updateContentCatArtigos(catArtigos, ordenador, review);
    }

    long idContribuinte = strtol(dados[5],NULL,10);
    
	// caso de o contribuidor ser -1 -> ip, nao se guarda infos
    if(idContribuinte != -1){
        catContribuidores = insertCatContribuidores(catContribuidores,idContribuinte);
        contribuidor = getContentCatContribuidores(catContribuidores,idContribuinte);
        if(!contribuidor){
            contribuidor = initItem();
            contribuidor = addItem(contribuidor,dados[4],1);
            updateContentCatContribuidores(catContribuidores,idContribuinte,contribuidor);
        }
        else{
            contribuidor = addContribuicao(contribuidor);
            contribuidor = setName(contribuidor,dados[4]);
            updateContentCatContribuidores(catContribuidores,idContribuinte,contribuidor);
        }
    }

    if(*artigosRepetidos){
        catArtigos = addArtigosRepetidos(catArtigos);
    }

    if(*revisoesUnicas){
        catArtigos = addRevisoesUnicas(catArtigos);
    }

    *artigosRepetidos = FALSE;
    *revisoesUnicas = FALSE;

	return;
}

static void parseArticle(char **dados, xmlDocPtr doc, xmlNodePtr cur){
	
	xmlChar *text;

	for(cur = cur->xmlChildrenNode ; cur ; cur = cur->next){
		if(!xmlStrcmp(cur->name,(const xmlChar *)"title")){
			text = xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
			strcpy(dados[1], (char *)text);
			xmlFree(text);
		}	
		else if(!xmlStrcmp(cur->name,(const xmlChar *)"id")){
			text = xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
			strcpy(dados[0], (char *)text);
			xmlFree(text);
		}
		else if(!xmlStrcmp(cur->name,(const xmlChar *)"revision")){
			parseRevision(dados,doc,cur);
		}
	}

}

static void parseRevision(char **dados, xmlDocPtr doc, xmlNodePtr cur){

	xmlChar *text;
    long words = 0,bytes;

	for(cur = cur->xmlChildrenNode ; cur ; cur = cur->next){
		if(!xmlStrcmp(cur->name,(const xmlChar *)"id")){
			text = xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
			strcpy(dados[2], (char *)text);
			xmlFree(text);	
		}
		if(!xmlStrcmp(cur->name,(const xmlChar *)"timestamp")){
			text = xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
			strcpy(dados[3], (char *)text);
			xmlFree(text);
		}
		if(!xmlStrcmp(cur->name,(const xmlChar *)"contributor")){
			parseContributor(dados,doc,cur);
		}
        if(!xmlStrcmp(cur->name,(const xmlChar *)"text") && cur->properties != NULL && !(xmlStrcmp(cur->properties->name,(const xmlChar *)"space"))){
			text = xmlNodeListGetString(doc,cur->xmlChildrenNode,1);

            countWordsAndBytes(text,&words,&bytes);

            char * tamanhoString = malloc(MAXBUFFER);
            char * tamanhoPalavras = malloc(MAXBUFFER);

            sprintf(tamanhoString,"%ld",bytes);
            sprintf(tamanhoPalavras,"%ld",words);

            strcpy(dados[6],tamanhoString);
            strcpy(dados[7],tamanhoPalavras);

            free(tamanhoString);
            free(tamanhoPalavras);
			xmlFree(text);
		}
	}
}

static void parseContributor(char **dados, xmlDocPtr doc, xmlNodePtr cur){

	xmlChar *text;

	for(cur = cur->xmlChildrenNode ; cur != NULL ; cur = cur->next){
		if(!xmlStrcmp(cur->name,(const xmlChar *)"username")){
			text = xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
			strcpy(dados[4], (char *)text);
			xmlFree(text);
		}
		if(!xmlStrcmp(cur->name,(const xmlChar *)"id")){
			text = xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
			strcpy(dados[5], (char *)text);
			xmlFree(text);
		}
		if(!xmlStrcmp(cur->name,(const xmlChar *)"ip")){
			text = xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
			strcpy(dados[4], (char *)text);
			strcpy(dados[5],"-1"); // meter o "Id" a -1 no caso de ips
			xmlFree(text);	
		}
	}
}

static void countWordsAndBytes(xmlChar *text, long *word, long *bytes){
    int i;

    for(i = 0 ; text[i] != '\0' ; i++){
        if(text[i] == ' ' || text[i] == '\n' || text[i] == '\t'){
            if(text[i+1] != ' ' && text[i+1] != '\n' && text[i+1] != '\t') {
                (*word)++;
            }
        }
    }

    *bytes = i;
}
