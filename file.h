int make_map(char *name,int map_size,char **arr){
    int i,j,x;
    char c;
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
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
           fread(&((*arr)[i][j]),sizeof(char),1,file);
    fclose(file);
    return n;
}
int save_game(node *head1,node *head2,int NumOfPlayers,int turn,char *map_address,char *save_address,int **energy,int NumofEnergy){
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
        fwrite(&(map_address[i]),sizeof(char),1,file);
    }
    l1=list_size(head1);
    if(NumOfPlayers==2)
        l2=list_size(head2);
    fwrite(&NumOfPlayers,sizeof(int),1,file);
    fwrite(&l1,sizeof(int),1,file);
    fwrite(&l2,sizeof(int),1,file);
    while(head1->next!=NULL){
        fwrite(head1,sizeof(node),1,file);
        head1=head1->next;
    }
    fwrite(head1,sizeof(node),1,file);
    if(NumOfPlayers==2){
        while(head2->next!=NULL){
            fwrite(head2,sizeof(node),1,file);
            head2=head2->next;
        }
        fwrite(head1,sizeof(node),1,file);
    }
    fwrite(&turn,sizeof(int),1,file);
    fwrite(&NumofEnergy,sizeof(int),1,file);
    for(i=0;i<NumofEnergy;i++){
        fwrite(&energy[i][0],sizeof(int),1,file);
        fwrite(&energy[i][1],sizeof(int),1,file);
        fwrite(&energy[i][2],sizeof(int),1,file);
    }
    fclose(file);
    return 0;
}
int load_game(node **head1,node **head2,int *NumOfPlayers,int *turn,char **map_address,char *save_address,int ***energy,int *NumofEnergy){
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
    (*head1)=create_node(*head1,0,0,0,"tmp");
    fread(*head1,sizeof(node),1,file);
    tmp=*head1;
    for(;l1-1>0;l1--){
        tmp->next=create_node(tmp->next,0,0,100,"tmp");
        fread(tmp->next,sizeof(node),1,file);
        tmp=tmp->next;
    }
    if(l2!=0){
        (*head2)=create_node(*head2,0,0,0,"tmp");
        fread(*head2,sizeof(node),1,file);
        tmp=*head2;
        for(;l2-1>0;l2--){
            tmp->next=create_node(tmp->next,0,0,100,"tmp");
            fread(tmp->next,sizeof(node),1,file);
            tmp=tmp->next;
        }
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
    fclose(file);
    return 0;
}
int read_dir(char ***address,char *suffix,int suffix_len,int *arrsize){
    int len,i;
    *arrsize=1;
    struct dirent *de;
    bool check;
    DIR *dr = opendir("C:\\Users\\Adak\\Desktop\\FinalProject");
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