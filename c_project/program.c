
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "interface.h"



int main (int argc, char **argv) {
    clock_t ti;
    clock_t tl;
    clock_t tf;
    int i, q5, q7, q8, q10a, q10r;
    int op = -1;
    int flow = 0;
    char q9[128];
    long* aux;
    long* aux1;
    long* aux2;
    char* r;
    char* s;
    char* u;
    char** titles;

    ti = clock();

	TAD_istruct estrutura = init();

    ti = clock() - ti;
    printf("\n\n");
    printf("Demorou %f segundos a iniciar a estrutura. \n",((float) ti)/CLOCKS_PER_SEC);

    tl = clock();

    estrutura = load(estrutura,argc-1,&argv[1]);

    tl = clock() - tl;
    printf("\n");
    printf("Demorou %f segundos a dar load dos ficheiros para a estrutura. \n",((float) tl)/CLOCKS_PER_SEC);



    while(flow == 0){
        printf("\n");
        printf("Escolha a sua opção: ");
        printf("\n");
        printf("   0 -> Ver o resultado de todas as queries\n");
        printf("   1 -> Ver o resultado de  uma querie específica\n");
        scanf("%d",&op);
        printf("\n");
        if(op == 0 || op == 1) flow = 1;
        else printf("Opção Inválida");
    }

    if (op == 1){

    printf("\n\n\n");
    printf("   1 -> Contar os artigos presentes em todos os snapshots analisados\n");
    printf("   2 -> Contar os artigos distintos presentes em todos os snapshots analisados\n");
    printf("   3 -> Contar as revisões presentes em todos os snapshots analisados\n");
    printf("   4 -> Contar as revisões dos contribuidores, devolvendo os 10 identificadores daqueles que mais revisões fizeram\n");
    printf("   5 -> Retornar o nome de um contribuidor correspondente a um dado identificador de contribuidor\n");
    printf("   6 -> Devolver os 20 identificadores de artigo com maior texto(tamanho em bytes)\n");
    printf("   7 -> Retornar o título de um artigo, correspondente a um dado identificador de artigo\n");
    printf("   8 -> Devolver os 'n' identificadores dos artigos com o maior número de palavras de forma crescente\n");
    printf("   9 -> Devolver os títulos dos artigos que contêm o prefixo especificado, ordenados alfabéticamente\n");
    printf("   10 -> Devolver o timestamp para uma certa revisão/versão de um dado artigo\n");

    flow = 0;
    while(flow == 0){
        printf("\n");
        printf("Escolha a sua opção: ");
        scanf("%d",&op);
        if(op > 0 && op < 11) flow = 1;
        else printf("Opção Inválida");
    }


    switch(op){

        case 1:
            printf("\n\n");
            printf("   Foram contabilizados %ld artigos em todos os snapshots analisados\n",all_articles(estrutura));
            break;

        case 2:
            printf("\n\n");
            printf("   Foram contabilizados %ld artigos únicos em todos os snapshots analisados\n",unique_articles(estrutura));
            break;


        case 3:
            printf("\n\n");
            printf("   Foram contabilizadas %ld revisões em todos os snapshots analisados\n",all_revisions(estrutura));
            break;


        case 4:
            printf("\n\n");
            printf(" Pretende saber os identificadores dos 10 contribuidores que mais revisões fizeram\n");
            printf("\n");
            aux = top_10_contributors(estrutura);
            printf(" Top 10 contribuidores com mais revisões:\n");
            for(i = 0 ; i < 10 ; i++){
                printf(" %ld\n",aux[i]);
            }
            free(aux);
            break;

        case 5:
            printf("\n\n");
            printf(" Pretende saber qual o nome de um contribuidor dado o seu identificador de contribuidor\n");
            printf("\n");
            printf("   Introduza o identificador para o qual pretende saber o nome de contribuidor\n");
            scanf("%d",&q5);
            r = contributor_name(q5,estrutura);
            printf(" Nome do contribuinte com o id %d: %s\n",q5,r);
            free(r);
            break;

        case 6:
            printf("\n\n");
            printf(" Pretende saber os identificadores dos 20 artigos com mais texto (tamanho em bytes)\n");
            printf("\n");
            aux1 = top_20_largest_articles(estrutura);
            printf(" Top 20 maior tamanho em bytes:\n");
            for(i = 0 ; i < 20 ; i ++){
                printf("Artigo nº%d, id:%ld\n",i+1,aux1[i]);
            }
            free(aux1);
            break;

        case 7:
            printf("\n\n");
            printf(" Pretende saber qual o título de um artigo dado o seu identificador de artigo\n");
            printf("\n");
            printf("   Introduza o identificador para o qual pretende saber o título de artigo\n");
            scanf("%d",&q7);
            s = article_title(q7,estrutura);
            printf(" Titulo do artigo com o id %d : %s\n",q7,s);
            free(s);
            break;

        case 8:
            printf("\n\n");
            printf(" Pretende saber de forma crecente quais os identificadores dos 'n' artigos que contêm o maior número de palavras\n");
            printf("\n");
            printf("   Introduza quantos artigos pretende saber\n");
            scanf("%d",&q8);
            aux2 = top_N_articles_with_more_words(q8,estrutura);
            printf(" Top '%d' artigos com mais palavras:\n",q8);
            printf(" Identificadores de artigo: ");
            for(i = 0 ; i < q8 ; i ++){
                printf(" id:%ld ,",aux2[i]);
            }
            free(aux2);
            break;

        case 9:
            printf("\n\n");
            printf(" Pretende saber os títulos dos artigos que contêm um determinado prefixo\n");
            printf("\n");
            printf("   Introduza o prefixo que deseja procurar\n");
            scanf("%s",q9);
            titles = titles_with_prefix(q9,estrutura);
            for(i=0; titles[i] != NULL;i++){
                printf(" Artigo %d: %s. \n", i+1, titles[i]);
            }
            break;

        case 10:
            printf("\n\n");
            printf(" Pretende saber qual o timestamp de uma dada revisão de um dado artigo\n");
            printf("\n");
            printf("   Introduza o identificador do artigo\n");
            scanf("%d",&q10a);
            printf("\n");
            printf("   Introduza o identificador da revisão\n");
            scanf("%d",&q10r);
            u = article_timestamp(q10a,q10r,estrutura);
            printf("\n");
            printf(" Data da revisão %d do artigo com o id %d : %s\n",q10r,q10a,u);
            free(u);
            break;
        default:break;
    }

    tf = clock();

    clean(estrutura);

    tf = clock() - tf;
    printf("\n\n");
    printf("Demorou %f segundos a dar free da estrutura. \n",((float) tf)/CLOCKS_PER_SEC);
}
else{
    printf("\n\n");
    printf("Foram contabilizados %ld artigos em todos os snapshots analisados\n",all_articles(estrutura));
    printf("\n\n");
    printf("Foram contabilizados %ld artigos únicos em todos os snapshots analisados\n",unique_articles(estrutura));
    printf("\n\n");
    printf("Foram contabilizadas %ld revisões em todos os snapshots analisados\n",all_revisions(estrutura));
    printf("\n\n");

    aux = top_10_contributors(estrutura);
            printf(" Top 10 contribuidores com mais revisões:\n");
            for(i = 0 ; i < 10 ; i++){
                printf(" %ld ,",aux[i]);
            }
            free(aux);


    printf("\n\n");
    r = contributor_name(102030,estrutura);
            printf(" Nome do contribuinte com o id 102030: %s\n",r);
            free(r);

    printf("\n\n");
    aux1 = top_20_largest_articles(estrutura);
            printf(" Top 20 maior tamanho em bytes:\n");
            for(i = 0 ; i < 20 ; i ++){
                printf(" id:%ld ,",aux1[i]);
            }
            free(aux1);


    printf("\n\n");
    s = article_title(102030,estrutura);
            printf(" Titulo do artigo com o id 102030 : %s\n",s);
            free(s);



    printf("\n\n");
    aux2 = top_N_articles_with_more_words(8,estrutura);
    printf(" Top '8' artigos com mais palavras:\n");
    printf(" Identificadores de artigo: \n");
    for(i = 0 ; i < 8 ; i ++){
        printf(" id:%ld, ",aux2[i]);
    }
    free(aux2);



    printf("\n\n");
    titles = titles_with_prefix("Anax",estrutura);
    printf("Títulos com um dado prefixo: \n");
    for(i = 0 ; titles[i] != NULL ; i++){
        printf("%s, ", titles[i]);
    }

    printf("\n\n");


    printf("\n\n");
     u = article_timestamp(102030,8888,estrutura);
            printf(" Data da revisão 8888 do artigo com o id 102030 : %s\n",u);
            free(u);


    tf = clock();

    clean(estrutura);

    tf = clock() - tf;
    printf("\n\n");
    printf("Demorou %f segundos a dar free da estrutura. \n",((float) tf)/CLOCKS_PER_SEC);

    }

     return 0;
}
