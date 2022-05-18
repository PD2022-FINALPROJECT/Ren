#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "recommend_and_heat_calculate.h"
#include "myDB.h"

#define DEBUG 0
#define MAX(a,b) ((a-b) >= 0 ? a : b)

void serving_print(float fruit, float vegetable, float grains, float protein, float milk){
	printf("\nThe recommended menu as follow:\n");
	printf("%.1f sersving(s) %s\n", fruit, FTN[0]);
	printf("%.1f fist(s) %s\n", vegetable, FTN[1]);
	printf("%.1f fist(s) %s\n", grains, FTN[2]);
	printf("%.1f palm(s) %s\n", protein, FTN[3]);
	printf("%.1f cup(s) %s\n", milk, FTN[4]);

}

void recommend(void){
	int meal;
	printf("\nWhich meal would you like to be recommended ?\n");
	printf("[1] Breakfast [2] Lunch [3] Dinner\n");
	scanf("%d", &meal);
	while( (meal > 3) || (meal < 1)){
		printf("please input 1, 2 or 3\n");
		scanf("%d", &meal);
	}
    
    	//cat[5] = fruit, vegetable, grains, protein, milk
    	//breakfast[5] = cat[5] (用來裝早餐)
    	float cat[5], temp;
	switch (meal){
		case 1:
			serving_print(FTS[0]/3, FTS[1]/3, FTS[2]/3, FTS[3]/3, FTS[4]/3);
			break;
		case 2:
			
			
			printf("\nPlease input your breakfast serving(s)\n");
			printf("Input example:\n");
			printf("fruit[unit:sersving] vegetable[unit:fist] grains[unit:fist] protein[unit:palm] milk[unit:cup]\n");
			printf("2 1 1 3 2\n");
				
		    	for(int i = 0 ; i < 5 ; i++){
		        	scanf("%f", &cat[i]);
		        	if(MAX(cat[i], FTS[i]/3) != cat[i])
					cat[i] = FTS[i]/3;
				else
					cat[i] = (cat[i] - FTS[0]/3) / 2;
		    	}
		    
			serving_print(cat[0], cat[1], cat[2], cat[3], cat[4]);
				
			break;
		case 3:
		
			printf("\nPlease input your breakfast and lunch serving(s)\n");
			printf("Input example:\n");
			printf("fruit[unit:sersving] vegetable[unit:fist] grains[unit:fist] protein[unit:palm] milk[unit:cup]\n");
			printf("2 1 1 3 2\n");
			
			for(int i = 0 ; i < 10 ; i++){
				if( i < 5 )
				    	scanf("%f", &cat[i]);
				else
				    	scanf("%f", &temp);
				cat[i%5] += temp;
				#if DEBUG
				printf("cat[%d] %f\n", i, cat[i%5]);
				#endif
			}
			    
			for(int i = 0 ; i < 5 ; i++){
				#if DEBUG
				printf("cat[%d] %f\n", i, cat[i]);
				#endif
				if(MAX(cat[i], FTS[i]) != cat[i])
					cat[i] = FTS[i] - cat[i];
				else
					cat[i] = 0;
			
			}
			serving_print(cat[0], cat[1], cat[2], cat[3], cat[4]);
            
			break;
	}
}
