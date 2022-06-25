#include <stdio.h>
#define boyut 100

int main() {
	
	int i, n, dizi[boyut], magicArray[boyut];
	
	printf("Dizinin boyutunu giriniz:");
	scanf("%d",&n);
	
	for(i=0;i<n;i++){
		magicArray[i]=0;		
	}
	
	
	for(i=0;i<n;i++){
		printf("dizinin %d . elemani:",i+1);
		scanf("%d",&dizi[i]);
		
		if(dizi[i]<=n){ // nden büyük olduðu taktirde sihirli sayi olamaz zaten ve cok buyuk bir sayiysa bellekte oraya erismeye calisirken sikinti cikacaktir
			magicArray[dizi[i]-1]+=1; //dizinin 0.indisini de kullanmak amaciyla yaptim. Aksi takdirde 0.indis gereksiz yere bosta kalmis olacak.
		}
	}
	
	
	for(i=0;i<n;i++){
		if(magicArray[i]==i+1){ //indis 0dan basladigi icin sihirli sayi olmasi icin deger indisin bir fazlasina esit olmalidir
			printf("%d\n",i+1);		
		
		}	
	}
	
	
	return 0;
}
