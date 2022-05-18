#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "first.h"
#include "record.h"
#include "recommend_and_heat_calculate.h"

#define DEBUG 1

int main(void){
	
	//判斷是否為第一次紀錄
	int first_record;
	printf("Are you recording for the first time?\n[1] Yes\t[2] No\n");
	while(1){
		scanf("%d", &first_record);
		if( (first_record == 1) || (first_record == 2))
                        break;
                else
                        printf("please input 1 or 2\n");

	}
	
	//假如為第一次紀錄先登記基本數值
	if( first_record == 1 ){
		int rd, rds;
		rd = first();
		if( rd == 1 ){
			printf("Would you recommended for a diet ?\n[1] Yes\t[2] No\n");
			scanf("%d", &rds);
			while( !((rds == 1) || (rds == 2)) ){
				printf("please input 1 or 2\n");
				scanf("%d", &rds);
			}
			if( rds == 1 ){
				recommend();
				return 0;
			}
			else
				return 0;
		}
	}	
	else{
		record_path();
	}

	return 0;
    
}