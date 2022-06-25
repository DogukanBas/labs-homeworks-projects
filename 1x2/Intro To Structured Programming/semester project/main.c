#include <stdio.h>
#define MAX 50
int floodFill(int matrix[MAX][MAX],int fillRow,int fillColumn, int row,int column,int color,int fillColor);
int main(){
    
    int matrix[MAX][MAX],i,j,row,column,fillColumn,fillRow,fillColor;
    printf("amount of rows");
    scanf("%d",&row);
        
    printf("amount of columns");
    scanf("%d",&column);

    for(i=0;i<row;i++){
        for(j=0;j<column;j++){
            printf("insert %dth row %dth column",i,j);
            scanf("%d",&matrix[i][j]);
        }
    }

    printf("THE MATRIX\n");
    for(i=0;i<row;i++){
        for(j=0;j<column;j++){
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }

    printf("enter the row of the element you want to start filling from:(first row is 0th row):");
    scanf("%d",&fillRow);
    printf("enter the column of the element you want to start filling frmo (first column is 0th column):");
    scanf("%d",&fillColumn);
    printf("Which color would you like to fill");
    scanf("%d",&fillColor);
    floodFill(matrix,fillRow,fillColumn,row,column,matrix[fillRow][fillColumn],fillColor);
    printf("\n");
    printf("FINAL MATRIX\n");
    for(i=0;i<row;i++){
        for(j=0;j<column;j++){
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }
    

    return 0;
}

int floodFill(int matrix[MAX][MAX],int fillRow,int fillColumn, int row,int column,int color,int fillColor){

    //base case if out of range or new pixel's color is not as same as the first pixel's colur 

    if(fillRow<0 || fillRow>=row ||fillColumn<0 || fillColumn>=column|| matrix[fillRow][fillColumn]!=color){

        return 0;   
    }
    else{
        matrix[fillRow][fillColumn]=fillColor;


        floodFill(matrix,fillRow-1,fillColumn,row,column,color,fillColor);
        floodFill(matrix,fillRow+1,fillColumn,row,column,color,fillColor);
        floodFill(matrix,fillRow,fillColumn+1,row,column,color,fillColor);
        floodFill(matrix,fillRow,fillColumn-1,row,column,color,fillColor);
    }

}
