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
    for(i=0;i<10;i++)
        (new_node->name)[i]=name[i];
    return new_node;
}
void add_end(node *head,node *new_node){
    for(;head->next!=NULL;head=head->next);
    head->next=new_node;
    new_node->prev=head;
}
void print_nodes(node *head){
    int i=1;
    for(;head->next!=NULL;head=head->next,i++)
        printf("%d)%s (%d,%d)\n",i,head->name,(head->pos).x,(head->pos).y);
    printf("%d)%s (%d,%d)",i,head->name,(head->pos).x,(head->pos).y);
}
