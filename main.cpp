#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <dirent.h>
#include "common.h"
#include "linkedlist.h"
#include "file.h"
#include "cells.h"
#include "gui.h"
int main(){
    srand(time(NULL));
    node *HeadPlayer1=NULL,*HeadPlayer2=NULL;
    int **energy;
    char **arr;
    int NumofPlayers=1,turn=1,mode,NumofEnergy=0,l1,l2;
    int i,n,j;
    char *MapAddress,*player1,*player2;
    printf("What do you like to do?\n 1)Load a game\n 2)Make a new single player game\n 3)Make a new multiplayer game\n 4)Exit\n");
    scanf("%d",&mode);
    system("cls");
    //initialize
    if(mode==4)
        return 0;
    if(mode==1){
        char **SavedAdresses;
        int AddressesSize,AddressNumber;
        printf("Please choose one of the following games:\n");
        read_dir(&SavedAdresses,".dat",4,&AddressesSize);
        printaddress(SavedAdresses,AddressesSize,4);
        scanf("%d",&AddressNumber);
        AddressNumber--;
        //Needs to be checked before loading
        load_game(&HeadPlayer1,&HeadPlayer2,&NumofPlayers,&player1,&player2,&turn,&MapAddress,SavedAdresses[AddressNumber],&energy,&NumofEnergy);
        n=read_map(MapAddress,&arr);
        system("cls");
    }
    else{
        //init map
        char **SavedMaps;
        char *cellname;
        node *tmp;
        int MapsSize,MapNumber,x,y;
        printf("Please choose on of the following maps:\n");
        read_dir(&SavedMaps,".bin",4,&MapsSize);
        printaddress(SavedMaps,MapsSize,4);
        scanf("%d",&MapNumber);
        system("cls");
        MapNumber--;
        n=read_map(SavedMaps[MapNumber],&arr);
        MapAddress=SavedMaps[MapNumber];
        //init heads
        printf("Please enter the name of Player1: ");
        fflush(stdin);
        getstring(&player1);
        //must check for available
        printf("%s, Please enter the number of cells you want: ",player1);
        scanf("%d",&l1);
        get_cells(n,&HeadPlayer1,&HeadPlayer2,player1,l1,arr);
        system("cls");
        if(mode==3){
            NumofPlayers=2;
            printf("Please enter the name of Player2: ");
            fflush(stdin);
            getstring(&player2);
            printf("%s, Please enter the number of cells you want: ",player2);
            scanf("%d",&l2);
            get_cells(n,&HeadPlayer2,&HeadPlayer1,player2,l2,arr);
            system("cls");
        }
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){
                if(arr[i][j]=='1'){
                    if(NumofEnergy==0)
                        energy=(int **)malloc(sizeof(int *));
                    else
                        energy=(int **)realloc(energy,(NumofEnergy+1)*sizeof(int *));
                    energy[NumofEnergy]=(int *)malloc(3*sizeof(int));
                    energy[NumofEnergy][0]=i;
                    energy[NumofEnergy][1]=j;
                    energy[NumofEnergy][2]=100;
                    NumofEnergy++;
                }
            }
        }
    }
    print_list(HeadPlayer1);
    print_list(HeadPlayer2);
    initwindow(800,800);
    update_map(arr,n,energy,NumofEnergy,HeadPlayer1,HeadPlayer2,NumofPlayers);
    fflush(stdin);
    getchar();
    return 0;
}
