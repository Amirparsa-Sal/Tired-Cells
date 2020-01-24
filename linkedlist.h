struct point{
    int x;
    int y;
};
typedef struct point point;
struct node{
    point pos;
    int energy;
    char name[10];
    struct node *next;
    struct node *prev;
};
typedef struct node node;
node* create_node(node *new_node,int x,int y,int energy,char *name){
    int i;
    new_node=(node *)malloc(sizeof(node));
    (new_node->pos).x=x;
    (new_node->pos).y=y;
    new_node->energy=energy;
    new_node->next=NULL;
    new_node->prev=NULL;
    for(i=0;name[i]!='\0' && i<10;i++)
        (new_node->name)[i]=name[i];
    for(;i<10;i++)
        (new_node->name)[i]='\0';
    return new_node;
}
void add_end(node *head,node *new_node){
    printf("*");
    while(head->next!=NULL)
        head=head->next;

    head->next=new_node;
    new_node->prev=head;
}
void print_list(node *head){
    int i=1;
    for(;head->next!=NULL;head=head->next,i++)
        printf("%d)%s (%d,%d)\n",i,head->name,(head->pos).x,(head->pos).y);
    printf("%d)%s (%d,%d)",i,head->name,(head->pos).x,(head->pos).y);
    printf("\n-------------");
}
int list_size(node *head){
    int len=0;
    for(;head->next!=NULL;head=head->next)
        len++;
    len++;
    return len;
}
void delete_node(node **head,char *name,int len){
    int i;
    node *tmp1=(*head),*tmp2=(*head);
    char *nametmp=(char *)malloc(10*sizeof(char));
    for(i=0;i<len;i++)
        nametmp[i]=name[i];
    for(i=len;i<10;i++)
        nametmp[i]='\0';
    if((*head)->next==NULL){
        if(str_cmp((*head)->name,nametmp,10))
            free((*head));
        else
            return;
    }
    else{
        if(str_cmp((*head)->name,nametmp,10)){
            (*head)->next->prev=NULL;
            (*head)=(*head)->next;
            free((*head)->prev);
        }
        do{
            tmp2=tmp2->next;
            if(str_cmp(tmp2->name,nametmp,10)){
                tmp1->next=tmp2->next;
                if(tmp2->next!=NULL)
                    tmp2->next->prev=tmp1;
                free(tmp2);
            }
            tmp1=tmp1->next;
        }while(tmp2->next!=NULL);
    }
}
