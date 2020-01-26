void update_cells(node *HeadPlayer,int player,int ***pos,int n,int L){
    int x1,y1,x2,y2,x,y,arrx,arry;
    if(player==1){


        setfillstyle(1,BLACK);
    }
    else{


        setfillstyle(1,WHITE);
    }
    printf(".");
    settextstyle(8,0,1);
    char energy[5];
    while(HeadPlayer->next!=NULL){

        itoa(HeadPlayer->energy,energy,10);
        x=HeadPlayer->pos.x;
        y=HeadPlayer->pos.y;
        arrx=x;
        arry=n-1-y;
        x1=pos[arry][arrx][0];
        y1=pos[arry][arrx][1];
        x2=pos[arry][arrx][2];
        y2=pos[arry][arrx][3];
        fillellipse((x1+x2)/2,(y1+y2)/2,L/4,L/4);
        outtextxy(x1+10, y1+10,HeadPlayer->name);

        outtextxy((x1+x2)/2 - 15, (y1+y2)/2-15,energy);
        HeadPlayer=HeadPlayer->next;
    }
    char tmp[7];
    itoa(HeadPlayer->energy,tmp,10);
    x=HeadPlayer->pos.x;
    y=HeadPlayer->pos.y;
    arrx=x;
    arry=n-1-y;
    x1=pos[arry][arrx][0];
    y1=pos[arry][arrx][1];
    x2=pos[arry][arrx][2];
    y2=pos[arry][arrx][3];
    fillellipse((x1+x2)/2,(y1+y2)/2,L/4,L/4);
    outtextxy(x1+10, y1+10,HeadPlayer->name);

    outtextxy((x1+x2)/2 - 15, (y1+y2)/2 -15,tmp);
}
void update_map(char **arr,int n,int **energy,int NumofEnergy,node *HeadPlayer1,node *HeadPlayer2,int NumofPlayers,int realplayer1){
    int i,j;
    int x,y,x1,y1,x2,y2,L;
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
    setcolor(WHITE);
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
    }
    if(realplayer1==1)
        update_cells(HeadPlayer1,1,pos,n,L);
    else
        update_cells(HeadPlayer2,1,pos,n,L);
    if(NumofPlayers==2){
        if(realplayer1==1)
            update_cells(HeadPlayer2,2,pos,n,L);
        else
            update_cells(HeadPlayer1,2,pos,n,L);
    }
}
