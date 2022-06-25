#include <stdio.h>

int main(){

	int A[10][10],spaces[10],n,m,i,j,length,row,column;
	length=0;
	printf("N degeri: ");
	scanf("%d",&n);
	printf("M degeri: ");
	scanf("%d",&m);
	printf("Matrisi Girin\n");
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			printf("%d.satir %d. sutunun elemanini giriniz:",i+1,j+1);
			scanf("%d",&A[i][j]);
		}
	}
	
	for(row=0;row<m;row++){
		column=0;
		while(A[row][column]!=1 && column<n){
			column+=1;		
		}
		if(column==n){ //donguden cikma sebebi 1 elemani bulmasi degil de o satirin bitmesiyse bos satirdir
			spaces[length]=row;
			length+=1;
		}
	}
	
	printf("Girilen Matris:\n");
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			printf("%d ",A[i][j]);
		}
		printf("\n");
	}
	
	
	if(length!=0){	
		printf("Cikti:");
		for(i=0;i<length-1;i++){
			printf("%d,",spaces[i]+1);
		}
		printf("%d",spaces[length-1]+1); // En sonda virgul olmasi goruntuyu bozar dolayisiyla sondaki virgulu boyle yazdirdim.
	}
	else{
		printf("Bos satir bulanamadi");
	}
		
	
	
	
	
	return 0;
}
