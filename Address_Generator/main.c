/*
To run this
g++ main.c
./a.out
*/
#include <stdio.h>
void display_datatypes_with_size() {
    printf("S.No  Data Type       Size\n");
    printf("1.    Short Int        2\n");
    printf("2.    Int              4\n");
    printf("3.    Long Int         4\n");
    printf("4.    Long Long Int    8\n");
    printf("5.    Char             1\n");
    printf("6.    Float            4\n");
    printf("7.    Double           8\n");
    printf("8.    Long Double      16\n");
}
void address_gen_1D(int n , int type_size ,unsigned long base_address){
    printf("Hi");
    for(int idx = 0;idx < n;idx++){
        printf("Address for index %d is 0x%lx\n",idx,base_address+(type_size * idx));
    }
}
void address_gen_2D(int row,int col,int type_size,unsigned long base_address){
    for(int r =0;r < row;r++){
        for(int c =0;c < col;c++){
            printf("Address for index [%d][%d] is 0x%lx\n",r,c,base_address + (r * col + c) * type_size);
        }
    }
}
void address_gen_3D(int row,int col,int depth,int type_size,unsigned long base_address){
    for(int r =0;r < row;r++){
        for(int c =0;c < col;c++){
            for(int d = 0;d < depth;d++){
                printf("Address for index [%d][%d][%d] is 0x%lx\n",r,c,d,base_address + type_size*(d+depth*(c+col*r)));
            }
        }
    }
}
int main(){
    unsigned long base_address = 0x7fffc7be80ec;
    int ch = 0,type_size = 0,n,row,col,depth;
    int types[8] = {2,4,4,8,1,4,8,16};
    while(ch <= 0 || ch > 8){
        display_datatypes_with_size();
        printf("Enter your Choice : ");
        scanf("%d",&ch);
        if(ch <= 0 || ch > 8) {
            printf("Enter a valid choice\n");
        }
    }
    type_size = types[ch-1];
    ch = 0;
    while(ch <= 0 || ch > 3){
        printf("Enter the Dimension (1/2/3) : ");
        scanf("%d",&ch);
        if(ch <= 0 || ch > 3) {
            printf("Enter a valid Dimension\n");
        }
    }
    if(ch == 1){
        printf("Enter Size : ");
        scanf("%d",&n);
        address_gen_1D(n,type_size,base_address);
    }
    else if(ch == 2){
        printf("Enter Row : ");
        scanf("%d",&row);
        printf("Enter Column : ");
        scanf("%d",&col);
        address_gen_2D(row,col,type_size,base_address);
    }
    else{
        printf("Enter Row : ");
        scanf("%d",&row);
        printf("Enter Column : ");
        scanf("%d",&col);
        printf("Enter Depth : ");
        scanf("%d",&depth);
        address_gen_3D(row,col,depth,type_size,base_address);
    }
    return 0;
}