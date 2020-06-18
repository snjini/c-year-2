#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void Print_Row(int row, int height, int level);

int main(int argc, char *argv[]){
    int height, level, upHeight, recursion;
    
    level=atoi(argv[2]);
    height=atoi(argv[1]);
    upHeight=ceil(height/2.0);
    recursion=1;

    if(argc!=3){
        printf("ERROR: 2 arguments required.\n");
    }
    else if(upHeight<pow(2.0,level-1)){
        printf("ERROR: Height does not allow evenly dividing requested number of levels.\n");
    }
    else if(height<=0 || height%2==0){
        printf("ERROR: Incorrectargument. Height must be a positive odd integer.\n");
    }
    else{
        //the top half of the diamond
        for(int row=1; row<=height; row+=2){
            Print_Row(row, height,level);
            printf("\n");
        }
        //the bottom half of the diamond
        for(int row=height-2; row>0; row-=2){
            Print_Row(row,height,level);
            printf("\n");
        }
    }

}

void Print_Row(int row, int height, int level){
    
    //the base case
    if(level==1){
        int i,j,k;
        for(i=0; i<(height-row)/2; i++){
            printf(" ");
        }
        for(j=0; j<row; j++){
            printf("*");
        }
        for(k=0; k<(height-row)/2; k++){
            printf(" ");
        }
    }
    else{
        int i,j;
        if(row<(height+1)/2){
            for(i=0; i<(height+1)/4; i++){
                printf(" ");
            }
            Print_Row(row, height/2, level-1);
            for(j=0; j<(height+1)/4; j++){
                printf(" ");
            }
        }
        else{
        Print_Row(row-(height+1)/2, (height+1)/2, level-1);
        printf(" ");
        Print_Row(row-(height+1)/2, (height+1)/2, level-1);
        }
    }
}

