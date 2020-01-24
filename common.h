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
void getcellname(char name[10]){
    int index=0;
    char c;
    c=getchar();
    while(c!='\n' && index<10){
        name[index]=c;
        c=getchar();
        index++;
    }
}
int str_cmp(char *src,char *dst,int len){
    int i;
    for(i=0;i<len;i++)
        if(src[i]!=dst[i])
            return 0;
    return 1;
}
int find_min(int a,int b,int c){

    int mn=a;
    if(b<mn)
        mn=b;
    if(c<mn)
        mn=c;
    return mn;
}
int strlength(char *str){
    int len=1;
    for(;str[len-1]!='\0';len++);
    return len;
}
void printaddress(char **arr,int arrlen,int suffixlen){
    int i,j;
    printf("+------------------------+\n");
    for(i=0;i<arrlen;i++){
        printf("%d) ",i+1);
        for(j=0;j<strlength(arr[i])-suffixlen-1;j++)
            printf("%c",arr[i][j]);
        printf("\n");
    }
    printf("+------------------------+\n");
}
