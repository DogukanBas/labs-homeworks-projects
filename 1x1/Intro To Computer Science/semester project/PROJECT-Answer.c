#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(){
	int mode,rowNumber,columnNumber,memoryLength;
	printf("Type 1 for easy, 2 for medium ,3 for hard mode: ");
	scanf("%d",&mode);
	if(mode==1){
		game(4,4,2);	
	}
	else if(mode==2){
		game(6,6,6);
	}

	else if(mode==3){
		game(8,8,16);		
	}
	
	return 0;
}
 
int game(rowNumber,columnNumber,memoryLength){	
	srand(time(NULL));
	int shown[rowNumber][columnNumber],memory[memoryLength][3];
	int cardNumber=rowNumber*columnNumber;
	int hideRow,hideColumn,i,j,location1,location2,userRow1,userRow2,userColumn1,userColumn2,memory_index,computerRow1,computerRow2,computerColumn1,computerColumn2,foundInMemory,control;
	int userTry=0;
	int computerTry=0;	
	int computersTurn=0; //ilk hamleyi kullanici yapar
	int userScore=0;
	int computerScore=0;
	
	
	
	for(hideRow=0;hideRow<rowNumber;hideRow++){
		for(hideColumn=0;hideColumn<columnNumber;hideColumn++){
			shown[hideRow][hideColumn]=-1;
		}
	}
	
	
	for(i=0;i<memoryLength;i++){
		memory[i][0]=-2;
		memory[i][1]=-2;
		memory[i][2]=-2;
	}
	
	
	
	i=0;
	memory_index=0;
	location1=rand()%cardNumber;			
	location2=rand()%cardNumber;
	while(i<(cardNumber/2)){		 //8 tane es karti yani 16 karti rastgele rastgele sekilde yerlestiriyoruz			
		if(location1!=location2 && shown[location1/rowNumber][location1%columnNumber]==-1){			
			if(shown[location2/rowNumber][location2%columnNumber]==-1){
				shown[location1/rowNumber][location1%columnNumber]=i;
				shown[location2/rowNumber][location2%columnNumber]=i;
				i=i+1;
				
			}
			else{					
				location2=rand()%cardNumber;
			}			
		}
		else{				
			location1=rand()%cardNumber;
		}
		
	}
	
	//kartlari açik sekilde gosteriyoruz	
	for(i=0;i<columnNumber*4;i++){
		printf("-");
	}
	printf("\n");
	for(hideRow=0;hideRow<rowNumber;hideRow++){ 
		for(hideColumn=0;hideColumn<columnNumber;hideColumn++){
			printf("%d",shown[hideRow][hideColumn]);
			printf(" | ");
		}
		printf("\n");
		for(i=0;i<columnNumber*4;i++){
			printf("-");
		}	
		printf("\n");
		
	}
		
	
	while((userScore+computerScore)!=cardNumber/2 && userScore<=cardNumber/4 && computerScore<=cardNumber/4){
		if(computersTurn==0){
			
			printf("Your moves: %d\nComputer's moves: %d\n",userTry,computerTry);
					
			printf("\n\n\n");
			for(i=0;i<columnNumber*4;i++){
				printf("-");
			}
			printf("\n");
			for(hideRow=0;hideRow<rowNumber;hideRow++){ //kartlari kapali sekilde gösteriyoruz
				for(hideColumn=0;hideColumn<columnNumber;hideColumn++){
					if(shown[hideRow][hideColumn]!=-1){
						printf("*");
					}
					else{
						printf("-");
					}
					printf(" | ");						
				}
				printf("\n");
				for(i=0;i<columnNumber*4;i++){
					printf("-");
				}	
				printf("\n");
			}
			
			printf("Your score:%d\nComputer's score:%d\nRemaining pairs:%d\n",userScore,computerScore,(cardNumber/2-userScore-computerScore));
			printf("Please insert your first input with space in-between row and column");
			scanf("%d %d",&userRow1,&userColumn1);
			if(shown[userRow1-1][userColumn1-1]!=-1){
				userTry+=1;
				printf("\n");
				for(i=0;i<columnNumber*4;i++){
					printf("-");
				}
				printf("\n");
				for(hideRow=0;hideRow<rowNumber;hideRow++){
					for(hideColumn=0;hideColumn<columnNumber;hideColumn++){
						if(hideRow==userRow1-1 && hideColumn==userColumn1-1){
							printf("%d",shown[hideRow][hideColumn]);
						}
						else if(shown[hideRow][hideColumn]==-1){
							printf("-");
						}
						else{
							printf("*");
						}
						printf(" | ");
						
					}
					printf("\n");
					for(i=0;i<columnNumber*4;i++){
						printf("-");
					}
					printf("\n");
						
				}
			
				printf("Please insert your second input with space in-between row and column");
				scanf("%d %d",&userRow2,&userColumn2);	
				
				
				if((userRow1!=userRow2 || userColumn1!=userColumn2) && (shown[userRow1-1][userColumn1-1]!=-1 && shown[userRow2-1][userColumn2-1]!=-1 )){//Kullanici daha once eslestirilmemis 2 farkli kart actiysa
					
					printf("\n");
					for(i=0;i<columnNumber*4;i++){
						printf("-");
					}
					printf("\n");
					for(hideRow=0;hideRow<rowNumber;hideRow++){
						for(hideColumn=0;hideColumn<columnNumber;hideColumn++){
							if((hideRow==userRow1-1 && hideColumn==userColumn1-1)|| (hideRow==userRow2-1 && hideColumn==userColumn2-1)){
								printf("%d",shown[hideRow][hideColumn]);
								
							}
							else if(shown[hideRow][hideColumn]==-1){
								printf("-");
							}
							else{
								printf("*");
							}
							printf(" | ");
						
						}
						printf("\n");
						for(i=0;i<columnNumber*4;i++){
							printf("-");
						}
						printf("\n");
						
				
					}
	
				
					if(shown[userRow1-1][userColumn1-1]!=shown[userRow2-1][userColumn2-1]){ // acilan kartlar birbirinin esi degilse memorye eklenmeli
						control=0;
						i=0;
						while(control==0 && i<memoryLength){
							if(memory[i][1]==userRow1-1 && memory[i][2]==userColumn1-1){
								control=1;
							}
							i=i+1;
						}
						if(control==0){
							memory[memory_index][0]=shown[userRow1-1][userColumn1-1];
							memory[memory_index][1]=userRow1-1;
							memory[memory_index][2]=userColumn1-1;
							if(memory_index!=memoryLength-1){
								memory_index+=1;								
							}
							else{
								memory_index=0;
							}
						}
		   						
						control=0;
						i=0;
						while(control==0 && i<memoryLength){
							if(memory[i][1]==userRow2-1 && memory[i][2]==userColumn2-1){
								control=1;
							}
							i=i+1;
						}
						if(control==0){
							memory[memory_index][0]=shown[userRow2-1][userColumn2-1];
							memory[memory_index][1]=userRow2-1;
							memory[memory_index][2]=userColumn2-1;
							if(memory_index!=memoryLength-1){
								memory_index+=1;								
							}
							else{
								memory_index=0;
							}
						}
						computersTurn=1;				
						sleep(3);
						system("CLS");
						
							
					}
					else{//acilan kartlar birbirinin esiyse o kartlar varsa hafizadan cikarilmali, kullanicinin skoru 1 artirilmali, destede acildi olarak isaretlenmeli sira tekrar kullanicida olmali
						printf("CONGRATS YOU HAVE FOUND A PAIR!");
						shown[userRow1-1][userColumn1-1]=-1;				
						shown[userRow2-1][userColumn2-1]=-1;
						control=0;
						i=0;
						while(control==0 && i<memoryLength){
							if(memory[i][1]==userRow1-1 && memory[i][2]==userColumn1-1){
								control=1;
							}
							i+=1;
							
						}
						if(control==1){
							for(j=i-1;j<memoryLength-1;j++){
								memory[j][0]=memory[j+1][0];
								memory[j][1]=memory[j+1][1];
								memory[j][2]=memory[j+1][2];
							}
							memory[memoryLength-1][0]=-2;
							memory[memoryLength-1][1]=-2;
							memory[memoryLength-1][2]=-2;
							if(memory[memoryLength-2][0]==-2){
								memory_index=memory_index-1;
							}
							else{
								memory_index=memoryLength-1;
							}
						}
					
					
						control=0;
						i=0;
						while(control==0 && i<memoryLength){
							if(memory[i][1]==userRow2-1 && memory[i][2]==userColumn2-1){
								control=1;
							}
							i+=1;
						}
						if(control==1){
							for(j=i-1;j<memoryLength-1;j++){
								memory[j][0]=memory[j+1][0];
								memory[j][1]=memory[j+1][1];
								memory[j][2]=memory[j+1][2];
							}
							memory[memoryLength-1][0]=-2;
							memory[memoryLength-1][1]=-2;
							memory[memoryLength-1][2]=-2;
							if(memory[memoryLength-2][0]==-2){
								memory_index=memory_index-1;
							}
							else{
								memory_index=memoryLength-1;
							}
						}
						
						userScore+=1;
						sleep(2);
						system("CLS");
					}
					
				}
				else{
					printf("Please open two different valid cards...\n");
					sleep(2);
					system("CLS");
				}

	
				}
				else{
					printf("Please open two different valid cards...\n");
					sleep(2);
					system("CLS");
				}
						
			}			
		
		
		//Computer's guess 
		else if(computersTurn==1){
			printf("Your moves: %d\nComputer's moves: %d\n",userTry,computerTry);
			computerTry+=1;
	
			printf("COMPUTER'S TURN \n ");			
			printf("Your score:%d\nComputer's score:%d\nRemaining pairs:%d\n ",userScore,computerScore,(cardNumber/2-userScore-computerScore));
		
			foundInMemory=0;
			i=0;
			
			//Hafizada direkt ayni iki kart varsa
			while(foundInMemory==0 && i<memoryLength && memory[i][0]!=-2){ 
				j=0;
				while(foundInMemory==0 && j<memoryLength){					
					if(memory[i][0]==memory[j][0] && i!=j){
						computerRow1=memory[i][1];
						computerColumn1=memory[i][2];
						computerRow2=memory[j][1];
						computerColumn2=memory[j][2];
						foundInMemory=1;
					
					}
					j+=1;
				}
				i+=1;
				
			}
			
			if(foundInMemory==0){ 
				computerRow1=rand()%rowNumber;
				computerColumn1=rand()%columnNumber;
				while(shown[computerRow1][computerColumn1]==-1){ //-1 olmayan bir guess 1 seçilene kadar devam.
					computerRow1=rand()%rowNumber;
					computerColumn1=rand()%columnNumber;
					
				}
								
				i=0;	
				while(foundInMemory==0 && i<memoryLength){
					if(memory[i][0]==shown[computerRow1][computerColumn1] && (computerRow1!=memory[i][1] || computerColumn1!=memory[i][2])){ //Eger hafizada ilk actigimiz kartin esi varsa ikinci acacagimiz kart o olmalidir
						computerRow2=memory[i][1];
						computerColumn2=memory[i][2];
						foundInMemory=1;
					}
					i=i+1;
				}
				
				
				if(foundInMemory==0){ //eger hafizada es iki kart yoksa, ilk kart rastgele acilir. Eger rastgele acilan kartin esi hafizada yoksa ikinci kart da uygun sartlarda rastgele secilmelidir
					computerRow2=rand()%rowNumber;						
					computerColumn2=rand()%columnNumber;
					i=0;
					while(i<memoryLength){
						//ikinci acacagimiz karti rastgele secerken de hafizadan yardim almaliyiz. Eger rastgele sectigimiz 2. kart hafizada varsa ve ilk actigimiz kartla ayni olmadigini biliyorsak bos yere onu acmaya gerek yok. Onemli bir detay. 
						while((shown[computerRow2][computerColumn2]==-1) || (computerRow1==computerRow2 && computerColumn1==computerColumn2) ||(memory[i][1]==computerRow2 && memory[i][2]==computerColumn2 && memory[i][0]!=shown[computerRow1][computerColumn1])) { //-1 olmayan bir guess 2 seçilene kadar devam.
							computerRow2=rand()%rowNumber;
							computerColumn2=rand()%columnNumber;
							i=-1;					
						}
					i=i+1;
					
					}										
					
				}			
				
			}
		
			printf("COMPUTER OUTPUT:\n");
			printf("Guess 1: %d x % d\n",(computerRow1+1),(computerColumn1+1));
			printf("\n");
			for(hideRow=0;hideRow<rowNumber;hideRow++){
				for(hideColumn=0;hideColumn<columnNumber;hideColumn++){	
					if(hideRow==computerRow1 && hideColumn==computerColumn1){
						printf("%d",shown[hideRow][hideColumn]);
					
							
					}
					else if(shown[hideRow][hideColumn]==-1){
						printf("-");
					}
					

					else{
						printf("*");
					}
					printf(" | ");
					
				}
				printf("\n");
				for(i=0;i<columnNumber*4;i++){
					printf("-");
				}
				printf("\n");		

			
			}
			sleep(3);
			
			printf("Guess 1: %d x % d\n",(computerRow1+1),(computerColumn1+1));
			printf("Guess 2: %d x % d\n",(computerRow2+1),(computerColumn2+1));
			
			printf("\n");
			for(i=0;i<columnNumber*4;i++){
				printf("-");
			}
			printf("\n");
			for(hideRow=0;hideRow<rowNumber;hideRow++){
				for(hideColumn=0;hideColumn<columnNumber;hideColumn++){	
					if((hideRow==computerRow1 && hideColumn==computerColumn1 || (hideRow==computerRow2 && hideColumn==computerColumn2))){
						printf("%d",shown[hideRow][hideColumn]);					
							
					}
				
					else if(shown[hideRow][hideColumn]==-1){
						printf("-");
					}					

					else{
						printf("*");
					}
					printf(" | ");
					
				}
				printf("\n");
				for(i=0;i<columnNumber*4;i++){
					printf("-");
				}
				printf("\n");		

			
			}
		
			if(shown[computerRow1][computerColumn1]!=shown[computerRow2][computerColumn2]){//eger acilan iki kart es degilse							
				control=0;
				i=0;
				while(control==0 && i<memoryLength){
					if(memory[i][1]==computerRow1 && memory[i][2]==computerColumn1){
						control=1;
					}
					i=i+1;
				}
				if(control==0){
					memory[memory_index][0]=shown[computerRow1][computerColumn1];
					memory[memory_index][1]=computerRow1;
					memory[memory_index][2]=computerColumn1;
					if(memory_index!=memoryLength-1){
						memory_index+=1;								
					}
					else{
						memory_index=0;
					}
				}

				control=0;
				i=0;
				while(control==0 && i<memoryLength){
					if(memory[i][1]==computerRow2 && memory[i][2]==computerColumn2){
						control=1;
					}
					i=i+1;
				}
				if(control==0){
					memory[memory_index][0]=shown[computerRow2][computerColumn2];
					memory[memory_index][1]=computerRow2;
					memory[memory_index][2]=computerColumn2;
					if(memory_index!=memoryLength-1){
						memory_index+=1;								
					}
					else{
						memory_index=0;
					}
				}
			   
				computersTurn=0;
				sleep(3);
				system("CLS");
						
			}
			else{//acilan kartlar birbirinin esiyse o kartlar varsa hafizadan cikarilmali, kullanicinin skoru 1 artirilmali, destede acildi olarak isaretlenmeli sira tekrar kullanicida olmali
			   
				printf("Oops, computer found a pair..");
				computersTurn=1;//commputer gets another choice
				sleep(2);
				shown[computerRow1][computerColumn1]=-1;				
				shown[computerRow2][computerColumn2]=-1;
				control=0;
				i=0;
				while(control==0 && i<memoryLength){
					if(memory[i][1]==computerRow1 && memory[i][2]==computerColumn1){
						control=1;
					}
					i=i+1;
				}
				if(control==1){
					for(j=i-1;j<memoryLength-1;j++){
						memory[j][0]=memory[j+1][0];
						memory[j][1]=memory[j+1][1];
						memory[j][2]=memory[j+1][2];
					}
					memory[memoryLength-1][0]=-2;
					memory[memoryLength-1][1]=-2;
					memory[memoryLength-1][2]=-2;
					if(memory[memoryLength-2][0]==-2){
						memory_index=memory_index-1;
					}
					else{
						memory_index=memoryLength-1;
					}
				}
			
				
				control=0;
				i=0;
				while(control==0 && i<memoryLength){
					if(memory[i][1]==computerRow2 && memory[i][2]==computerColumn2){
						control=1;
					}
					i=i+1;
				}
				if(control==1){
				
					for(j=i-1;j<memoryLength-1;j++){
						memory[j][0]=memory[j+1][0];
						memory[j][1]=memory[j+1][1];
						memory[j][2]=memory[j+1][2];
					}
					memory[memoryLength-1][0]=-2;
					memory[memoryLength-1][1]=-2;
					memory[memoryLength-1][2]=-2;
					if(memory[memoryLength-2][0]==-2){
						memory_index=memory_index-1;
					}
					else{
						memory_index=memoryLength-1;
					}
				}  
							
				computerScore+=1;
				system("CLS");
			}
			
		}
	}
	
	sleep(1);
	
	if(computerScore>userScore){
		printf("\nOOOPS YOU LOST...\nYou have done %d moves computer has done %d moves\n",userTry,computerTry);
		printf("Your score:%d\nComputer's score:%d\n",userScore,computerScore);
	}
	else if(computerScore==userScore){
		printf("\nNo one won!\nYou have done %d moves computer has done %d moves\n",userTry,computerTry);
		printf("Your score:%d\nComputer's score:%d ",userScore,computerScore);
	}
	else{ 
		printf("\nYOU WON!\nYou have done %d moves computer has done %d moves\n",userTry,computerTry);
		printf("Your score:%d\nComputer's score:%d ",userScore,computerScore);
	}
		
}

	
	
	
