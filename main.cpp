#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <dirent.h>
#include "common.h"
#include "linkedlist.h"
#include "file.h"
#include "cells.h"
int main(){
    char *MapAddress;
    node *HeadPlayer1,*HeadPlayer2;
    int NumofPlayers,turn,**arr,mode;
    printf("What do you like to do?\n 1)Load a game\n 2)Make new single player game\n 3)Make new multiplayer game\n 4)Exit\n");
    scanf("%d",&mode);
    if(mode==1){
        char **SavedAdresses;
        int AddressesSize,AddressNumber;
        printf("Please choose one of the following games:\n");
        read_dir(&SavedAdresses,".dat",4,&AddressesSize);
        printaddress(SavedAdresses,AddressesSize,4);
        scanf("%d",&AddressNumber);
        AddressNumber--;
        //Needs to be checked before loading
        load_game(&HeadPlayer1,&HeadPlayer2,&NumofPlayers,&turn,&MapAddress,SavedAdresses[AddressNumber]);
    }
    print_list(HeadPlayer1);
	return 0;
}
