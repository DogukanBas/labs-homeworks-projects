#include <stdio.h>
#define MAX 20
int main(){
	int matris[MAX][MAX];
	int row,column;
	int rotaControl=0;
	int i,j,sayac=0,control=0;
	int rota[MAX];
	printf("Lutfen satir sayisini giriniz");
	scanf("%d",&row);
	printf("Lutfen sutu sayisini giriniz");
	scanf("%d",&column);
	for(i=0;i<row;i++){
		for(j=0;j<column;j++){
			printf("%d. satir %d. sutunu giriniz",i+1,j+1);
			scanf("%d",&matris[i][j]);
		}
	}

	if(matris[0][0]==1){
		rotaControl=1;
		i=0;
		j=0;
	
	}
	else if(matris[0][1]==1){
		rotaControl=1;
		i=0;
		j=1;
	}
	else if(matris[1][0]==1){
		rotaControl=1;
		i=1;
		j=1;
	}
	
	if(rotaControl==1){
		while(i<row && j<column && control==0){
			control=1;
			
			if(matris[i+1][j]==1){
				i=i+1;	
				control=0;
				rota[sayac]=2;
				sayac=sayac+1;
			}
			
			else if(matris[i][j+1]==1){
				j=j+1;	
				control=0;
				rota[sayac]=1;
				sayac=sayac+1;
			}
			}
	}

	
	else{
		printf("Rota Yok");
	}
	
	
	
	
	for(i=0;i<sayac;i++){
	printf("%d ",rota[i]);
	}
	

	
	
	
	
	
	return 0;
}
