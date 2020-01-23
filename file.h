int make_map(char *name,int map_size,char arr[map_size][map_size]){
    int i,j;
    FILE *file;
    file=fopen(name,"wb");
    if(file==NULL){
        printf("ERROR");
        return -1;
    }
    fwrite(&map_size,sizeof(int),1,file);
    for(i=0;i<map_size;i++)
        for(j=0;j<map_size;j++)
            fwrite(&arr[i][j],sizeof(char),1,file);
    fclose(file);
    return 0;
}

int random_map(char *name,int map_size){
    srand(time(NULL));
    int i,j,x;
    FILE *file;
    file=fopen(name,"wb");
    if(file==NULL){
        printf("ERROR");
        return -1;
    }
    fwrite(&map_size,sizeof(int),1,file);
    for(i=0;i<map_size;i++){
        for(j=0;j<map_size;j++){
            x=rand()%4 +1;
            fwrite(&x,sizeof(char),1,file);
        }
    }
    fclose(file);
    return 0;
}

int read_map(char *name,char ***arr){
    int i,j;
    int n;
    FILE *file;
    file=fopen(name,"rb");
    if(file==NULL){
        printf("ERROR");
        return -1;
    }
    fread(&n,sizeof(int),1,file);
    (*arr)=(char **)malloc(n*sizeof(char *));
    for(i=0;i<n;i++)
        (*arr)[i]=(char *)malloc(n*sizeof(char));
    for(i=0;i<n;i++){
        for(j=0;j<n;j++)
           fread(&((*arr)[i][j]),sizeof(char),1,file);
    }
    fclose(file);
    return n;
}
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
    l1=list_size(head1);
    if(NumOfPlayers==2)
        l2=list_size(head2);
    fwrite(&NumOfPlayers,sizeof(int),1,file);
    fwrite(&l1,sizeof(int),1,file);
    fwrite(&l2,sizeof(int),1,file);
    fwrite(head1,sizeof(node),1,file);
    if(NumOfPlayers==2)
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

    fread(NumOfPlayers,sizeof(int),1,file);
    fread(&l1,sizeof(int),1,file);
    fread(&l2,sizeof(int),1,file);

    tmp=create_node(tmp,0,0,0,"tmp");
    (*head1)=create_node(*head1,0,0,0,"tmp");
    fread(*head1,sizeof(node),1,file);
    if(l2!=0){
        (*head2)=create_node(*head2,0,0,0,"tmp");
        fread(*head2,sizeof(node),1,file);
    }
    fread(turn,sizeof(int),1,file);
    fclose(file);
    return 0;
}
