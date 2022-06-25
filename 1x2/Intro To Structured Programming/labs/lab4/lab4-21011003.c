#include <stdio.h>
#define MAX 7

int zamanKontrol(int bas, int bitis);
int faaliyetKontrol(int i,char harfler[MAX], char harf);

void GanttDraw(int gantt[MAX][2],char harfler[MAX], int boyut);



int main(){
    int i,boyut,gantt[MAX][2];
    char harfler[MAX];
    printf("Yapilacak is sayisini giriniz:");
    scanf("%d",&boyut);
    i=0;
    while(i<boyut){
        printf("%d. is kodu:",i+1);
        scanf(" %c",&harfler[i]);
        if(faaliyetKontrol(i,harfler,harfler[i])!=1){
            i++;
        }
    }
    
    i=0;
    while(i<boyut){
        printf("%c islemi baslangic zamani:",harfler[i]);
        scanf("%d",&gantt[i][0]);
        printf("%c islemi  bitis zamani:",harfler[i]);
        scanf("%d",&gantt[i][1]);
        if(zamanKontrol(gantt[i][0],gantt[i][1])!=1){
            i++;
        }
    }
    printf("\nGANT DIAGRAMI \n");
    GanttDraw(gantt,harfler,boyut);
    return 0;
}

int faaliyetKontrol(int i,char harfler[MAX], char harf){
    int j=0;
    while(j<i){
        if(harfler[j]==harf){
            return 1;
        }
        j++;
    }
    return 0;
}

int zamanKontrol(int bas, int bitis){
    if(bas>=1 && bitis>bas){
        return 0;
    }
    return 1;
}




void GanttDraw(int gantt[MAX][2],char harfler[MAX], int boyut){
    int i,j,k;
    for(i=0;i<boyut;i++){
        printf("\n"); 
        for(j=1;j<gantt[i][0];j++){
            printf("_");
        }
        for(k=gantt[i][0];k<gantt[i][1]+1;k++){
            printf("%c",harfler[i]);
        }
    }
}
