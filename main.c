#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "linkedlist.h"
int save_game(node *head1,node *head2,int NumOfPlayers,int turn,char *map_address,char *save_address){
    int len,i;
    int l1,l2=0;
    FILE *file;
    file=fopen(save_address,"wb");
    if(file==NULL){
        printf("ERROR");
        return -1;
    }
    for(len=1;;len++)
        if(map_address[len-1]=='\0')
            break;
    for(i=0;i<len;i++){
        printf("%c",map_address[i]);
        fwrite(&(map_address[i]),sizeof(char),1,file);
    }
    printf("\n");
    printf("%s\n",map_address);
    l1=list_size(head1);
    if(NumOfPlayers==2)
        l2=list_size(head2);
    fwrite(&NumOfPlayers,sizeof(int),1,file);
    fwrite(&l1,sizeof(int),1,file);
    fwrite(&l2,sizeof(int),1,file);

    for(;head1->next!=NULL;head1=head1->next)
        fwrite(head1,sizeof(node),1,file);
    if(NumOfPlayers==2)
        for(;head2->next!=NULL;head2=head2->next)
            fwrite(head2,sizeof(node),1,file);

    fwrite(&turn,sizeof(int),1,file);
    fclose(file);
    return 0;
}
int load_game(node **head1,node **head2,int *NumOfPlayers,int *turn,char **map_address,char *save_address){
    FILE *file;
    int cnt=0,l1,l2;
    char c;
    node *tmp;
    file=fopen(save_address,"rb");
    if(file==NULL){
        printf("ERROR");
        return -1;
    }
    (*map_address)=(char *)malloc(sizeof(char));
    fread(&c,sizeof(char),1,file);

    while(c!='\0'){
        (*map_address)[cnt]=c;
        cnt++;
        (*map_address)=(char *)realloc((*map_address),(cnt+1)*sizeof(char));
        fread(&c,sizeof(char),1,file);
    }
    (*map_address)[cnt]='\0';

    fread(&NumOfPlayers,sizeof(int),1,file);
    fread(&l1,sizeof(int),1,file);
    fread(&l2,sizeof(int),1,file);

    tmp=create_node(tmp,0,0,0,"tmp");
    (*head1)=create_node(*head1,0,0,0,"tmp");
    fread(*head1,sizeof(node),1,file);

    for(;l1-1>0;l1--){
        fread(tmp,sizeof(node),1,file);
        add_end(*head1,tmp);
    }
    if(l2!=0){
        (*head2)=create_node(*head2,0,0,0,"tmp");
        fread(*head2,sizeof(node),1,file);
        for(;l2-1>0;l2--){
            fread(tmp,sizeof(node),1,file);
            add_end(*head2,tmp);
        }
    }
    fread(turn,sizeof(int),1,file);
    fclose(file);
    return 0;
}

int main()
{
    node *head1,*head2,*n1,*n2;
    head1=create_node(head1,0,0,100,"amir");
    n1=create_node(n1,1,1,90,"parsa");
    n2=create_node(n2,2,2,80,"gaboor");
    add_end(head1,n1);
    add_end(head1,n2);
    save_game(head1,head2,1,1,"map.bin","01.dat");
    node *head3,*head4;
    int NumOfPlayers,turn;
    char *map_address;
    load_game(&head3,&head4,&NumOfPlayers,&turn,&map_address,"01.dat");
    print_list(head3);
    return 0;
}
