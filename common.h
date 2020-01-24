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
