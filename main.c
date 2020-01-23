#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dirent.h>
#include "linkedlist.h"
#include "file.h"
#include "cells.h"
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
int str_cmp(char *src,char *dst,int len){
    int i;
    for(i=0;i<len;i++)
        if(src[i]!=dst[i])
            return 0;
    return 1;
}
int find_min(int a,int b,int c){
    int mn=a;
    if(b<mn)
        mn=b;
    if(c<mn)
        mn=c;
    return mn;
}
int movecell(node *my_node,char *direction,node* head1,node *head2,int n,int arr[n][n]){
    int x,y;
    x=(my_node->pos).x;
    y=(my_node->pos).y;
    if(x%2==1){
        if(str_cmp(direction,"NorthWest",9))
            direction="West";
        else if(str_cmp(direction,"NorthEast",9))
            direction="East";
    }
    if(x%2==0){
        if(str_cmp(direction,"SouthWest",9))
            direction="West";
        else if(str_cmp(direction,"SouthEast",9))
            direction="East";
    }
    if(str_cmp(direction,"SouthWest",9)){
        if(CheckisAvailable(x-1,y-1,n,head1,head2,arr)){
            my_node->pos.x-=1;
            my_node->pos.y-=1;
        }
        else
            return 0;
    }
    else if(str_cmp(direction,"SouthEast",9)){
        if(CheckisAvailable(x+1,y-1,n,head1,head2,arr)){
            my_node->pos.x+=1;
            my_node->pos.y-=1;
        }
        else
            return 0;
    }
    else if(str_cmp(direction,"NorthEast",9)){
        if(CheckisAvailable(x+1,y+1,n,head1,head2,arr)){
            my_node->pos.x+=1;
            my_node->pos.y+=1;
        }
        else
            return 0;
    }
    else if(str_cmp(direction,"NorthWest",9)){
        if(CheckisAvailable(x-1,y+1,n,head1,head2,arr)){
            my_node->pos.x-=1;
            my_node->pos.y+=1;
        }
        else
            return 0;
    }
    else if(str_cmp(direction,"North",5)){
        if(CheckisAvailable(x,y+1,n,head1,head2,arr))
            my_node->pos.y+=1;
        else
            return 0;
    }
    else if(str_cmp(direction,"West",4)){
        if(CheckisAvailable(x-1,y,n,head1,head2,arr))
            my_node->pos.x-=1;
        else
            return 0;
    }
    else if(str_cmp(direction,"East",4)){
        if(CheckisAvailable(x+1,y,n,head1,head2,arr))
            (my_node->pos).x+=1;
        else
            return 0;
    }
    else if(str_cmp(direction,"South",5)){
        if(CheckisAvailable(x,y-1,n,head1,head2,arr))
            (my_node->pos).y-=1;
        else
            return 0;
    }
    return 1;
}
int main()
{
    node *head,*head2,*n1,*n2;
    head=create_node(head,1,0,100,"Amirparsa");
    int arr[2][2]={2,1,3,4};
    printf("%d\n",movecell(head,"North",head,head,2,arr));
    print_list(head);
    return 0;
}
