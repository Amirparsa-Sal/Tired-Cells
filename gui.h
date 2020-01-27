void update_cells(node *HeadPlayer,int player,int ***pos,int n,int L){
    int x1,y1,x2,y2,x,y,arrx,arry;
    if(player==1){
        setcolor(WHITE);
        setbkcolor(BLACK);
        setfillstyle(1,BLACK);
    }
    else{
        setcolor(BLACK);
        setbkcolor(WHITE);
        setfillstyle(1,WHITE);
    }
    settextstyle(3,0,1);
    while(HeadPlayer!=NULL){
        x=HeadPlayer->pos.x;
        y=HeadPlayer->pos.y;
        arrx=x;
        arry=n-1-y;
        x1=pos[arry][arrx][0];
        y1=pos[arry][arrx][1];
        x2=pos[arry][arrx][2];
        y2=pos[arry][arrx][3];
        fillellipse((x1+x2)/2,(y1+y2)/2,L/4,L/4);
        if(n<10){
            char energy[5];
            char name[4];
            sprintf(energy,"%d",HeadPlayer->energy);
            name[0]=HeadPlayer->name[0];
            name[1]=HeadPlayer->name[1];
            name[2]=HeadPlayer->name[2];
            name[3]='\0';
            outtextxy(x1, y1,name);
            outtextxy((x1+x2)/2 - 15, (y1+y2)/2-15,energy);
            outtextxy((x1+x2)/2 - 15, (y1+y2)/2-15,energy);
        }

        HeadPlayer=HeadPlayer->next;
    }
}
void update_map(char **arr,int n,int **energy,int NumofEnergy,node *HeadPlayer1,node *HeadPlayer2,int NumofPlayers,int realplayer1){
    int i,j;
    int x1,y1,x2,y2,L;
    int ***pos;
    pos=(int ***)malloc(n*sizeof(int **));
    for(i=0;i<n;i++)
        pos[i]=(int **)malloc(n*sizeof(int *));
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            pos[i][j]=(int *)malloc(4*sizeof(int));
    setfillstyle(1,BLACK);
    bar(0,0,800,800);
    L=780/(n+1);
    setcolor(BLACK);
    setcolor(BLACK);
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(arr[i][j]=='1') setfillstyle(1,BLUE);
            else if(arr[i][j]=='2')setfillstyle(1,GREEN);
            else if(arr[i][j]=='3')setfillstyle(1,RED);
            else if(arr[i][j]=='4')setfillstyle(1,YELLOW);
            x1=10+j*L+L/2;
            x2=10+(j+1)*L+L/2;
            if(j%2==0){
                y1=10+(i*L)+L/4;
                y2=10+((i+1)*L)+L/4;
            }
            else{
                y1=10+(i*L)+3*L/4;
                y2=10+((i+1)*L)+3*L/4;
            }
            pos[i][j][0]=x1;
            pos[i][j][1]=y1;
            pos[i][j][2]=x2;
            pos[i][j][3]=y2;
            bar(x1,y1,x2,y2);
            rectangle(x1,y1,x2,y2);
        }
    }
    settextstyle(3,0,1);
    for(i=0;i<NumofEnergy;i++){
        setbkcolor(BLACK);
        int en=energy[i][2];
        x1=pos[energy[i][0]][energy[i][1]][0];
        y1=pos[energy[i][0]][energy[i][1]][1];
        x2=pos[energy[i][0]][energy[i][1]][2];
        y2=pos[energy[i][0]][energy[i][1]][3];
        setfillstyle(1,BLUE);
        bar(x1,y1,x2,y2);
        setfillstyle(4,BLUE);
        bar(x1,y1,x1+(en/100.0)*L,y2);
        rectangle(x1,y1,x2,y2);
        setbkcolor(BLUE);
        char energy[4];
        sprintf(energy,"%d",en);
        energy[3]='\0';

        outtextxy(x1,y2-25,energy);
    }
    if(HeadPlayer1!=NULL){
        if(realplayer1==1)
            update_cells(HeadPlayer1,1,pos,n,L);
        else
            update_cells(HeadPlayer2,1,pos,n,L);
    }
    if(HeadPlayer2!=NULL){
        if(NumofPlayers==2){
            if(realplayer1==1)
                update_cells(HeadPlayer2,2,pos,n,L);
            else
                update_cells(HeadPlayer1,2,pos,n,L);
        }
    }
}
void map_editor(){
    char *name;
    int mode=0;
    int **energy;
    int n=0,i,j;
    char **arr;
    int L;
    while(mode<=0 || mode>3){
        system("cls");
        printf("What do you like to do? \n1)Make your own map \n2)Make a random map \n3)Edit another map\n");
        scanf("%d",&mode);
    }
    if(mode==1 || mode==2){
        while(n<=0){
            system("cls");
            printf("Please enter the size of the map: ");
            fflush(stdin);
            scanf("%d",&n);
        }
        printf("Please enter the name of the map: ");
        fflush(stdin);
        getstring(&name);
        system("cls");
    }
    if(mode==1 || mode==3){
        if(mode==1){
            arr=(char **)malloc(n*sizeof(char *));
            for(i=0;i<n;i++)
                arr[i]=(char *)malloc(n*sizeof(char));
            for(i=0;i<n;i++)
                for(j=0;j<n;j++)
                    arr[i][j]='1';
        }
        else{
            char **SavedMaps;
            int MapsSize,MapNumber=0,len;
            read_dir(&SavedMaps,".bin",4,&MapsSize);
            system("cls");
            if(MapsSize==0){
                printf("There is no map to load!");
                Sleep(1000);
                return;
            }
            while(MapNumber<=0 || MapNumber>MapsSize){
                printf("Please choose one of the following maps:\n");
                read_dir(&SavedMaps,".bin",4,&MapsSize);
                printaddress(SavedMaps,MapsSize,4);
                fflush(stdin);
                scanf("%d",&MapNumber);
                system("cls");
            }
            MapNumber--;
            n=read_map(SavedMaps[MapNumber],&arr);
            name=SavedMaps[MapNumber];
            len=strlength(name);
            name=(char *)realloc(name,(len-4)*sizeof(char));
            name[len-5]='\0';
        }
        L=780/(n+1);
        printf("You can change the map by clicking on the map cells.\nYou can reset the map by right click \nAfter Finishing your work press any key to finish the map.\nBlue: Energy\nGreen: Mitosis\nRed: Forbidden\nYellow: Normal\n\n");
        initwindow(800,800);
        update_map(arr,n,energy,0,NULL,NULL,0,0);
        while(!kbhit()){
            if(ismouseclick(WM_LBUTTONDOWN)){
                int x,y,x1,y1,x2,y2;
                x=mousex();
                y=mousey();
                for(j=0;j<n;j++){
                    x1=10+j*L+L/2;
                    x2=10+(j+1)*L+L/2;
                    if(x>x1 && x<x2)
                        break;
                }
                if(j==n)
                    continue;
                if(j%2==0){
                    for(i=0;i<n;i++){
                        y1=10+(i*L)+L/4;
                        y2=10+((i+1)*L)+L/4;
                        if(y>y1 && y<y2)
                            break;
                    }
                }
                else{
                    for(i=0;i<n;i++){
                        y1=10+(i*L)+3*L/4;
                        y2=10+((i+1)*L)+3*L/4;
                        if(y>y1 && y<y2)
                            break;
                    }
                }
                if(i==n)
                    continue;
                arr[i][j]+=1;
                if(arr[i][j]=='5')
                    arr[i][j]='1';
                update_map(arr,n,energy,0,NULL,NULL,0,0);
                clearmouseclick(WM_LBUTTONDOWN);

            }
            else if(ismouseclick(WM_RBUTTONDOWN)){
                for(i=0;i<n;i++)
                    for(j=0;j<n;j++)
                        arr[i][j]='1';
                update_map(arr,n,energy,0,NULL,NULL,0,0);
                clearmouseclick(WM_RBUTTONDOWN);
            }
        }
    }


    if(mode==1 || mode ==3)
        make_map(name,n,arr);
    else if(mode==2)
        random_map(name,n);
    printf("Your map has been saved!");
    if(mode==1 || mode==3)
        closegraph();
    Sleep(1000);
    system("cls");
}
