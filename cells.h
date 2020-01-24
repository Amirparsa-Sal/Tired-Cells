int CheckisAvailable(int x,int y,int n,node *head1,node *head2,char **arr){
    int arrx,arry;
    arrx=x;
    arry=n-1-y;
    if(arrx<0 || arrx>=n || arry<0 || arry>=n)
        return 0;
    if(arr[arry][arrx]=='3')
        return 0;
    do{
        if((head1->pos).x==x && (head1->pos).y==y)
            return 0;
        if(head1->next!=NULL)
            head1=head1->next;
    }while(head1->next!=NULL);
    do{
        if((head2->pos).x==x && (head2->pos).y==y)
            return 0;
        if(head2->next!=NULL)
            head2=head2->next;
    }while(head2->next!=NULL);
    return 1;
}
int find_energy(int x,int y,int **energy,int NumofEnergy){
    int i;
    for(i=0;i<NumofEnergy;i++){

        if(energy[i][0]==x && energy[i][1]==y)
            return i;
    }
    printf(",");
    return -1;
}
int get_energy(node *my_node,int n,char **arr,int **energy,int NumofEnergy){
    int x,y;
    int tmp;
    y=n-1-(my_node->pos).y;
    x=(my_node->pos).x;
    if(arr[y][x]!='1')
        return 0;

    tmp=energy[find_energy(y,x,energy,NumofEnergy)][2];
    printf("tmp:%d\n",tmp);
    energy[find_energy(y,x,energy,NumofEnergy)][2]-=find_min(15,energy[find_energy(y,x,energy,NumofEnergy)][2],100-my_node->energy);
    printf("final:%d\n",energy[find_energy(y,x,energy,NumofEnergy)][2]);
    my_node->energy+=find_min(15,tmp,100-my_node->energy);
    return 1;
}

int check_random_move(node *my_node,int arrx[6],int arry[6],int n,node *head1,node *head2,char **arr,int *dx,int *dy){
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
    (*dx)=arrx[valids[rnd]];
    (*dy)=arry[valids[rnd]];
    return 1;
}
int mitosis(node **my_node,node **head1,node **head2,node **newcell1,char *newcellname1,node **newcell2,char *newcellname2,int n,char **arr){
    int x,y,arrx,arry,dx,dy;
    int zojdirectionx[6]={-1,-1,0,0,1,1},zojdirectiony[6]={0,1,-1,1,0,1},farddirectionx[6]={-1,-1,0,0,1,1},farddirectiony[6]={0,-1,-1,1,0,-1};
    x=((*my_node)->pos).x;
    y=((*my_node)->pos).y;
    arrx=x;
    arry=n-1-y;
    if((*my_node)->energy<80 || arr[arry][arrx]!='2')
        return 0;
    if(x%2==0){
        if (!check_random_move(*my_node,zojdirectionx,zojdirectiony,n,*head1,*head2,arr,&dx,&dy))
            return 0;
    }
    else if(x%2==1){
        if (!check_random_move(*my_node,farddirectionx,farddirectiony,n,*head1,*head2,arr,&dx,&dy))
            return 0;
    }
    (*newcell1)=create_node((*newcell1),x,y,40,newcellname1);
    (*newcell2)=create_node((*newcell2),x+dx,y+dy,40,newcellname2);
    add_end(*head1,*newcell1);
    add_end(*head1,*newcell2);
    printf(".");
    delete_node(head1,(*my_node)->name,10);
    return 1;
}
int movecell(node *my_node,char *direction,node* head1,node *head2,int n,char **arr){
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
