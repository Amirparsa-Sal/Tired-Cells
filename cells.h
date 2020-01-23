int CheckisAvailable(int x,int y,int n,node *head1,node *head2,int arr[n][n]){
    int arrx,arry;
    arrx=x;
    arry=n-1-y;
    if(arr[y][x]==3)
        return 0;
    if(x<0 || x>=n || y<0 || y>=n)
        return 0;
    do{
        if((head1->pos).x==x && (head1->pos).y==y)
            return 0;
        head1=head1->next;
    }while(head1->next!=NULL);
    do{
        if((head2->pos).x==x && (head2->pos).y==y)
            return 0;
        head2=head2->next;
    }while(head2->next!=NULL);
    return 1;
}
int get_energy(node *my_node,int n,int arr[n][n]){
    int x,y;
    int tmp;
    y=n-1-(my_node->pos).y;
    x=(my_node->pos).x;
    if(arr[y][x]>=1 && arr[y][x]<=4)
        return 0;
    tmp=arr[y][x];
    arr[y][x]-=find_min(15,(arr[y][x]-1)/4,100-my_node->energy)*4;
    my_node->energy+=find_min(15,(tmp)/4,100-my_node->energy);
    return 1;
}
