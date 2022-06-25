#include <stdio.h>

int main(){
	char dizi[200];
	int i=1;
	printf("Girdi:");
	gets(dizi);
	
	if (dizi[0]<='z' &&dizi[0]>='a'){
		dizi[0]=dizi[0]+('A'-'a');
		}
	
	while (dizi[i]!='\0'){
		if (dizi[i-1]=='.' && dizi[i]!=' '&& dizi[i]>='a' && dizi[i]<='z'){
			dizi[i]=dizi[i]+('A'-'a');
		}
		
		else if (dizi[i-1]=='.' && dizi[i]==' '&&  dizi[i+1]>='a' &&dizi[i+1]<='z'){
			dizi[i+1]=dizi[i+1]+('A'-'a');
		}
		i+=1;
		
		
	}
	printf("\nCikti:%s",dizi);
	return 0;
}


