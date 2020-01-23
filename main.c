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
    x=my_node->pos.x;
    y=my_node->pos.y;
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
    else if(str_cmp(direction,"East",9)){
        if(CheckisAvailable(x+1,y,n,head1,head2,arr))
            my_node->pos.x+=1;
        else
            return 0;
    }
    else if(str_cmp(direction,"South",9)){
        if(CheckisAvailable(x,y-1,n,head1,head2,arr))
            my_node->pos.y-=1;
        else
            return 0;
    }
    return 1;
}
int check_random_move(node *my_node,int arrx[6],int arry[6],int n,node *head1,node *head2,int arr[n][n],int *dx,int *dy){
    int valid=0,i,valids[6]={0},rnd;
    for(i=0;i<6;i++){
        if(CheckisAvailable((my_node->pos).x+arrx[i],(my_node->pos).y+arry[i],n,head1,head2,arr)){
            valid++;
            valids[valid-1]=i;
        }
    }
    if(valid==0)
        return 0;
    rnd=rand()%valid;
    (*dx)=arrx[rnd];
    (*dy)=arry[rnd];
    return 1;
}
int mitosis(node **my_node,node *head1,node *head2,node **newcell1,char *newcellname1,node **newcell2,char *newcellname2,int n,int arr[n][n]){
    int dx,dy;
    if((*my_node)->energy<80)
        return 0;
    int zojdirectionx[6]={-1,-1,0,0,1,1};
    int zojdirectiony[6]={0,1,-1,1,0,1};
    int farddirectionx[6]={-1,-1,0,0,1,1};
    int farddirectiony[6]={0,-1,-1,1,0,-1};
    int x,y,arrx,arry;
    if(x%2==0){
        if (!check_random_move(*my_node,zojdirectionx,zojdirectiony,n,head1,head2,arr,&dx,&dy))
            return 0;
    }
    else if(x%2==1){
        if (!check_random_move(*my_node,farddirectionx,farddirectiony,n,head1,head2,arr,&dx,&dy))
            return 0;
    }
    x=((*my_node)->pos).x;
    y=((*my_node)->pos).y;
    (*newcell1)=create_node((*newcell1),x,y,40,newcellname1);
    (*newcell2)=create_node((*newcell2),x+dx,y+dy,40,newcellname2);
    delete_node(head1,(*my_node)->name,10);
}
int main()
{
    return 0;
}
