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
    printf("What do you like to do? \n1)Load a game \n2)Make a new single player game \n3)Make a new multiplayer game \n4)Exit\n");
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
    system("cls");
    int flag=1;
    initwindow(800,800);
    update_map(arr,n,energy,NumofEnergy,HeadPlayer1,HeadPlayer2,NumofPlayers);
    //fflush(stdin);
    while(flag){
        if(turn%2==1){
            int i,mode;
            node *my_node=HeadPlayer1;
            int cellnumber=list_size(HeadPlayer1)+1;
            print_list(HeadPlayer1);
            while(cellnumber>list_size(HeadPlayer1) || cellnumber<=0){
                printf("%s, Please choose one of your cells\nCell number: ",player1);
                scanf("%d",&cellnumber);
                if(cellnumber>list_size(HeadPlayer1) || cellnumber<=0)
                    printf("Invalid Number Please Try Again\n");
            }
            for(i=0;i<cellnumber-1;i++)
                my_node=my_node->next;
            system("cls");
            printf("%s, What do you like to do with your cell? (Cell Name= %s)\n",player1,my_node->name);
            printf("1)Move \n2)Split Cell \n3)Boost Energy \n4)Save \n5)Exit\n");
            scanf("%d",&mode);
            system("cls");
            if(mode==1){
                char *direction;
                int dir,flag=0;
                printf("Please enter the direction you want:\n");
                printf("1)North \n2)South \n3)NorthEast \n4)NorthWest \n5)SouthEast \n6)SouthWest\n");
                scanf("%d",&dir);
                if(dir==1) direction="North";
                else if(dir==2) direction="South";
                else if(dir==3) direction="NorthEast";
                else if(dir==4) direction="NorthWest";
                else if(dir==5) direction="SouthEast";
                else if(dir==6) direction="SouthWest";
                flag=movecell(my_node,direction,HeadPlayer1,HeadPlayer2,n,arr);
                if(flag==1){
                    printf("Your cell moved successfuly!");
                    update_map(arr,n,energy,NumofEnergy,HeadPlayer1,HeadPlayer2,NumofPlayers);
                    if(NumofPlayers==2)turn++;
                }
                else{
                    printf("Cannot move to that place!");
                }
                Sleep(500);
                system("cls");
            }
            else if(mode==2){
                int dx,dy;
                int flag;
                flag=check_for_split(&my_node,&HeadPlayer1,&HeadPlayer2,n,arr,&dx,&dy);
                if(flag==-1)printf("You cant split the cell because the cell's energy is less than 80!\n\n");
                else if(flag==-2)printf("You cant split the cell because the cell is not on splitting place\n\n");
                else if(flag==-3)printf("You cant split the cell because there is no place for new cell\n\n");
                else{
                    node *new_cell1,*new_cell2;
                    char *name1,*name2;
                    printf("Please enter the new name of the cell: ");
                    fflush(stdin);
                    getstring(&name1);
                    printf("Please enter the name of the new cell: ");
                    fflush(stdin);
                    getstring(&name2);
                    mitosis(&my_node,&HeadPlayer1,&HeadPlayer2,&new_cell1,name1,&new_cell2,name2,n,arr);
                    printf("Your cell splitted successfuly!\n");
                    update_map(arr,n,energy,NumofEnergy,HeadPlayer1,HeadPlayer2,NumofPlayers);
                    if(NumofPlayers==2)turn++;
                    Sleep(500);
                    system("cls");
                }

            }
            else if(mode==3){
                int flag;
                flag=get_energy(my_node,n,arr,energy,NumofEnergy);
                if(flag==-1)printf("Getting energy failed because the cell is not on the energy resource place\n\n");
                else if(flag==-2)printf("Getting energy failed because the cell is full of energy\n\n");
                else if(flag==-3)printf("Getting energy failed because the energy resource is empty\n\n");
                else{
                    printf("Your cell got energy successfuly!\n");
                    update_map(arr,n,energy,NumofEnergy,HeadPlayer1,HeadPlayer2,NumofPlayers);
                    if(NumofPlayers==2)turn++;
                    Sleep(500);
                    system("cls");
                }
            }
        }

    }
    return 0;
};
