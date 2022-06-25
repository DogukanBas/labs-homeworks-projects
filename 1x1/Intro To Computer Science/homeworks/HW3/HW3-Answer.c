#include <stdio.h>
#define N 5000
int main(void)
{
 FILE *fp;
 char text[N];
 /********* degisken tanimlari ************/
 int i=0,wordCounter=0,k=0,j;
 /********* degisken tanimlari sonu ************/

 // Dosyayi açma
 if ((fp = fopen ("soru.txt", "r")) == NULL) {
 printf("Dosya açma hatasi!");
 return 1;
 }
 // Dosyadan okuma
 fgets(text, N-1, fp);
 // printf("%s\n", text);

 /*
 * text karakter dizisi degiskeninde dosyadan okunan metin yer almaktadir.
 * toplam kelime sayisinin hesabi ve bosluk temizleme islemleri -TERCIHEN-
 * bu dizi üzerinde yapilmalidir. Harici dizi kullanimi önerilmemektedir.
 */
 /********* kod blogu ************/
 while(text[i]!='\0'){
 	if(text[i]==' '){
 		if(text[i+1]==' '){
 			j=i;
 			while(text[j]!='\0'){
 				text[j]=text[j+1];
 				j+=1;
			 }
		 }
		else{
			i+=1;
			wordCounter+=1;
		}		
	}
	else{
		i+=1;
	}
	
 }
 
 if(text[0]==' '){ //son durumda ilk karakter bosluk ise bu bosluktan kurtulmak icin tum dizi bir birim saga kaydirilir ve yanlis sayilan kelime geri alinir
 	wordCounter-=1;
 	while(text[k]!='\0'){
 		text[k]=text[k+1];
 		k+=1;
	 }
 }
 
 if(text[i-1]==' '){ //en sonda bosluk varsa bu bosluk silinir
 	text[i-1]='\0';
 }
 printf("Toplam kelime sayisi:%d\n",wordCounter);
 printf("%s",text);
 



 /********* kod blogu sonu ************/
 // Dosyayi kapama
 fclose(fp);
 return 0;
}
