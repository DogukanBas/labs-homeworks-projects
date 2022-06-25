#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 3

int determinant(int submatrix[2][2]);
void randomMatrixFunc(int randomMatrix[MAX][MAX]);
int minorMatrixFunc(int randomMatrix[MAX][MAX],int minorMatrix[MAX][MAX],int row,int column);
void printMatrix(int matrix[MAX][MAX]);
int main(){
    srand(time(NULL));
    int randomMatrix[MAX][MAX],minorMatrix[MAX][MAX];
    randomMatrixFunc(randomMatrix);
    printf("The random matrix:\n");
    printMatrix(randomMatrix);
    printf("\n\n");
    minorMatrixFunc(randomMatrix,minorMatrix,0,0);
    
    printf("\n\n");
    printMatrix(minorMatrix);

}

void randomMatrixFunc(int randomMatrix[MAX][MAX]){
    int i;
    int j;
    for(i=0;i<MAX;i++){
        for(j=0;j<MAX;j++){
            randomMatrix[i][j]= rand() % 10;
        }
    }

}

int determinant(int submatrix[2][2]){
    return submatrix[0][0]*submatrix[1][1]-submatrix[1][0]*submatrix[0][1];
}


int minorMatrixFunc(int randomMatrix[MAX][MAX],int minorMatrix[MAX][MAX],int row,int column){
    int i,j,minorRow=0,minorColumn=0, submatrix[2][2],frow,fcolumn;
    frow=row;
    fcolumn=column;
    submatrix[0][0]=0;
    submatrix[0][1]=0;
    submatrix[1][0]=0;
    submatrix[1][1]=0;
    if(row==MAX-1 && column==MAX-1){
        submatrix[0][0]=randomMatrix[0][0];
        submatrix[0][1]=randomMatrix[0][1];
        submatrix[1][0]=randomMatrix[1][0];
        submatrix[1][1]=randomMatrix[1][1];
        minorMatrix[row][column]=determinant(submatrix);
        return 0;
    }
    for(i=0;i<MAX;i++){
        if(i!=row){
            for(j=0;j<MAX;j++){
                if(j!=column){
                    submatrix[minorRow][minorColumn]=randomMatrix[i][j];
                    if(minorColumn==1){
                        minorColumn=-1;
                        minorRow++;
                    }
                    minorColumn++;
                    

                }
            }
        }
    }
    
    minorMatrix[row][column]=determinant(submatrix);
    if(column==MAX-1){
        fcolumn=-1;
        frow++;
    }
    fcolumn++;
    minorMatrixFunc(randomMatrix,minorMatrix,frow,fcolumn);
  

    

}

void printMatrix(int matrix[MAX][MAX]){
    int i,j;
    for(i=0;i<MAX;i++){
        for(j=0;j<MAX;j++){
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }
}
