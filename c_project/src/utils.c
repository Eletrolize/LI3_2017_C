//
// Created by menino bruno on 11-04-2017.
//

#include "utils.h"


long getFirstNumber(long number){

    long aux = number;

    while(aux >= 10){
        aux = aux / 10;
    }

    return aux;
}

int maiorPrefix(char* str1, char* str2){
	int i, c=0;

	for(i=0; str1[i] == str2[i] && str2[i]!='\0' && str1[i]!='\0'; i++){
		c++;
	}

	return c;
}