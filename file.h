int make_map(char *name,int map_size,char **arr){
    int i,j,len;
    FILE *file;
    len=strlength(name);
    name=(char *)realloc(name,(len+4)*sizeof(char));
    name[len-1]='.';
    name[len]='b';
    name[len+1]='i';
    name[len+2]='n';
    name[len+3]='\0';
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
    int i,j,x,len;
    char c;
    FILE *file;
    len=strlength(name);
    name=(char *)realloc(name,(len+4)*sizeof(char));
    name[len-1]='.';
    name[len]='b';
    name[len+1]='i';
    name[len+2]='n';
    name[len+3]='\0';
    file=fopen(name,"wb");
    if(file==NULL){
        printf("ERROR");
        return -1;
    }
    fwrite(&map_size,sizeof(int),1,file);
    for(i=0;i<map_size;i++){
        for(j=0;j<map_size;j++){
            x=rand()%4 +1;
            c='0'+x;
            fwrite(&c,sizeof(char),1,file);
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
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
           fread(&((*arr)[i][j]),sizeof(char),1,file);
    fclose(file);
    return n;
}
int save_game(node *head1,node *head2,int NumOfPlayers,char *Player1Name,char *Player2Name,int turn,char *map_address,char *save_address,int **energy,int NumofEnergy){
    int len,i;
    int l1,l2=0;
    FILE *file;
    file=fopen(save_address,"wb");
    if(file==NULL){
        printf("ERROR");
        return -1;
    }
    len=strlength(map_address);
    for(i=0;i<len;i++)
        fwrite(&(map_address[i]),sizeof(char),1,file);
    fwrite(&NumOfPlayers,sizeof(int),1,file);
    len=strlength(Player1Name);
    for(i=0;i<len;i++)
        fwrite(&(Player1Name[i]),sizeof(char),1,file);
    l1=list_size(head1);
    fwrite(&l1,sizeof(int),1,file);
    while(head1!=NULL){
        fwrite(head1,sizeof(node),1,file);
        head1=head1->next;
    }
    fwrite(&turn,sizeof(int),1,file);
    fwrite(&NumofEnergy,sizeof(int),1,file);
    for(i=0;i<NumofEnergy;i++){
        fwrite(&energy[i][0],sizeof(int),1,file);
        fwrite(&energy[i][1],sizeof(int),1,file);
        fwrite(&energy[i][2],sizeof(int),1,file);
    }
    if(NumOfPlayers==2){
        len=strlength(Player2Name);
        for(i=0;i<len;i++)
            fwrite(&(Player2Name[i]),sizeof(char),1,file);
        l2=list_size(head2);
        fwrite(&l2,sizeof(int),1,file);
        while(head2!=NULL){
            fwrite(head2,sizeof(node),1,file);
            head2=head2->next;
        }
    }
    fclose(file);
    return 0;
}
int load_game(node **head1,node **head2,int *NumOfPlayers,char **Player1Name,char ** Player2Name,int *turn,char **map_address,char *save_address,int ***energy,int *NumofEnergy){
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
    cnt=0;
    fread(NumOfPlayers,sizeof(int),1,file);
    (*Player1Name)=(char *)malloc(sizeof(char));
    fread(&c,sizeof(char),1,file);
    while(c!='\0'){
        (*Player1Name)[cnt]=c;
        cnt++;
        (*Player1Name)=(char *)realloc((*Player1Name),(cnt+1)*sizeof(char));
        fread(&c,sizeof(char),1,file);
    }
    (*Player1Name)[cnt]='\0';

    fread(&l1,sizeof(int),1,file);

    (*head1)=create_node(*head1,0,0,0,"tmp");
    fread(*head1,sizeof(node),1,file);
    tmp=*head1;
    for(;l1-1>0;l1--){
        tmp->next=create_node(tmp->next,0,0,100,"tmp");
        fread(tmp->next,sizeof(node),1,file);
        tmp=tmp->next;
    }
    fread(turn,sizeof(int),1,file);
    fread(NumofEnergy,sizeof(int),1,file);
    int i;
    (*energy)=(int **)malloc(*NumofEnergy*sizeof(int *));
    for(i=0;i<*NumofEnergy;i++){
        (*energy)[i]=(int *)malloc(3*sizeof(int));
        fread(&((*energy)[i][0]),sizeof(int),1,file);
        fread(&((*energy)[i][1]),sizeof(int),1,file);
        fread(&((*energy)[i][2]),sizeof(int),1,file);
    }


    if(*NumOfPlayers==2){
        cnt=0;
        (*Player2Name)=(char *)malloc(sizeof(char));
        fread(&c,sizeof(char),1,file);
        while(c!='\0'){
            (*Player2Name)[cnt]=c;
            cnt++;
            (*Player2Name)=(char *)realloc((*Player2Name),(cnt+1)*sizeof(char));
            fread(&c,sizeof(char),1,file);
        }
        (*Player2Name)[cnt]='\0';

        fread(&l2,sizeof(int),1,file);

        (*head2)=create_node(*head2,0,0,0,"tmp");
        fread(*head2,sizeof(node),1,file);
        tmp=*head2;
        for(;l2-1>0;l2--){
            tmp->next=create_node(tmp->next,0,0,100,"tmp");
            fread(tmp->next,sizeof(node),1,file);
            tmp=tmp->next;
        }
    }

    fclose(file);
    return 0;
}
int read_dir(char ***address,char *suffix,int suffix_len,int *arrsize){
    int len,i;
    *arrsize=1;
    struct dirent *de;
    bool check;
    DIR *dr = opendir(".");
    if (dr == NULL){
        printf("Error");
        return -1;
    }
    (*address)=(char **)malloc(sizeof(char *));
    while ((de = readdir(dr)) != NULL){
        len=de->d_namlen;
        check=true;
        for(i=0;i<suffix_len;i++)
            if((de->d_name)[len-(suffix_len-i)]!=suffix[i])
                check=false;
        if(check){
            ((*address)[(*arrsize)-1])=(char *)malloc((len+1)*sizeof(char));
            for(i=0;i<len;i++)
                (*address)[(*arrsize)-1][i]=de->d_name[i];
            (*address)[(*arrsize)-1][len]='\0';
            (*arrsize)++;
            (*address)=(char **)realloc(*address,(*arrsize)*sizeof(char *));
        }
    }
    (*arrsize)--;
    closedir(dr);
    return 0;
}
