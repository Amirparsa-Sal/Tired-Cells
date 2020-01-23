#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include "file.h"
#include "linkedlist.h"
void getstring(char **name){
    int len=0;
    char c;
    (*name)=(char *)malloc(sizeof(char));
    c=getchar();
    while(c!='\n'){
        (*name)[len]=c;
        len++;
        (*name)=(char *)realloc((*name),(len+1)*sizeof(char));
        c=getchar();
    }
    (*name)[len]='\0';
}
int main()
{
    return 0;
}
