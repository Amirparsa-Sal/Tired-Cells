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

void getstring(char **name){
    int len=0;
    char c;
    (*name)=(char *)malloc(sizeof(char));
    c=getchar();
    while(c!='\n'){
        (*name)[len]=c;
        len++;
        (*name)=(char *)realloc((*name),(len+1)*sizeof(char));
        c=getchar();
    }
    (*name)[len]='\0';
}
