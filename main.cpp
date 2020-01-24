#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <dirent.h>
#include "common.h"
#include "linkedlist.h"
#include "file.h"
#include "cells.h"
int main(){
    int i,n,j;
    char *MapAddress,**arr;
    node *HeadPlayer1,*HeadPlayer2;
    int NumofPlayers,turn,mode,NumofEnergy=0;
    int **energy;
    printf("What do you like to do?\n 1)Load a game\n 2)Make new single player game\n 3)Make new multiplayer game\n 4)Exit\n");
    scanf("%d",&mode);
    //initialize
    if(mode==1){
        char **SavedAdresses;
        int AddressesSize,AddressNumber;
        printf("Please choose one of the following games:\n");
        read_dir(&SavedAdresses,".dat",4,&AddressesSize);
        printaddress(SavedAdresses,AddressesSize,4);
        scanf("%d",&AddressNumber);
        AddressNumber--;
        //Needs to be checked before loading
        load_game(&HeadPlayer1,&HeadPlayer2,&NumofPlayers,&turn,&MapAddress,SavedAdresses[AddressNumber],&energy,&NumofEnergy);
        n=read_map(MapAddress,&arr);
    }
    /*if(mode==2){
        //some inits head1,head2,nop=1,turn=1,mapaddress,n,arr
    }
    if(mode==3){
        //some inits head1,head2,nop=1,turn=1,mapaddress,n,arr
    }*/
    if(mode==2 || mode==3){
        //init energy
        int i,j;
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
    for(i=0;i<NumofEnergy;i++){
        printf("%d %d %d\n",energy[i][0],energy[i][1],energy[i][2]);
    }
}
