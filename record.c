#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "record.h"
#include "R1.h"
#include "R2.h"
#include "R3.h"
#include "R4.h"
#include "R5.h"

#define DEBUG 0

/*
讀取csv檔的record
根據record至函式執行
*/
void record_path(void){
	
	char file_name[MAXLENGTH];
	
	//讀取csv檔的名字
	printf("Please input your filename:\n");
	printf("(Add .csv at the end of filename)\n");
	scanf("%s", file_name);
	
	while(!file_name){
		printf("\nPlease input your filename again\n");
		scanf("%s", file_name);
	}
	
	//開啟csv檔
	FILE *fp;
    	fp = fopen(file_name, "r");
    	
    	while(!fp){
    		printf("Check whether your profile exists\n");
    		printf("If your profile is not exists\n");
    		printf("Please use (Ctrl + C) close this progress\n");
    		printf("And reopen this program input first use this program\n");
    		printf("Or Please input your filename again\n");
		scanf("%s", file_name);
		fp = fopen(file_name, "r");
    	}
    
    	char line[MAX_LINE_SIZE];
    	char *result = NULL;
    	int record, check_record = 0, recommended_diet, gender, age, height;
    	
    	//讀取第一次填的數值
    	while(fgets(line, MAX_LINE_SIZE, fp) != NULL) {
    		
        	result = strtok(line, ",");
        	
        	if(!isalpha(*result) && !check_record){
            			record = atoi(result);
            			check_record++;
            			
            			result = strtok(NULL, ",");
            			result = strtok(NULL, ",");
            			recommended_diet = atoi(result);
            			
            			if( (record == 4) || (record == 5)){
            				result = strtok(NULL, ",");
            				
            				result = strtok(NULL, ",");
            				gender = atoi(result);
            				
            				result = strtok(NULL, ",");
            				age = atoi(result);
            				
            				result = strtok(NULL, ",");
            				height = atoi(result);
            			}
            				
            			
            	}
   
        	if(check_record && isalpha(*result))
    			break;
    	}
    	fgets(line, MAX_LINE_SIZE, fp);
    	
    	#if DEBUG
    	printf("record %d\n", record);
    	#endif
    	
    	struct R1 *Head1 = NULL;
    	struct R2 *Head2 = NULL;
    	struct R3 *Head3 = NULL;
    	struct R4 *Head4 = NULL;
    	struct R5 *Head5 = NULL;
    	
    	//根據record不同
    	//將csv檔內的內容串成link list
    	switch (record){
    		case 1:
    			Head1 = R1_Read_File(fp);
    			break;
    		case 2:
    			Head2 = R2_Read_File(fp);
    			break;
    		case 3:
    			Head3 = R3_Read_File(fp);
    			break;
    		case 4:
    			Head4 = R4_Read_File(fp);
    			break;
    		case 5:
    			Head5 = R5_Read_File(fp);
    			break;
    	
    	}
    	
    	//選擇查看先前輸入內容或輸入新資料
    	while(1){
	    	int vi;
	    	printf("\nView current profile or input new data\n");
	    	printf("[1] view [2] input [3] quit:\n");
	    	
	    	while(1){
			scanf("%d", &vi);
			if( (vi == 1) || (vi == 2) || (vi == 3))
		                break;
		        else
		                printf("please input 1, 2 or 3\n");

		}
		
		if( vi == 1 ){
		
			switch (record){
	    		case 1:
	    			R1_View(Head1);
	    			break;
	    		case 2:
	    			R2_View(Head2);
	    			break;
	    		case 3:
	    			R3_View(Head3);
	    			break;
	    		case 4:
	    			R4_View(Head4);
	    			break;
	    		case 5:
	    			R5_View(Head5);
	    			break;
	    	
	    		}
	    		
		}
		
		else if( vi == 2 ){
			
			switch (record){
	    		case 1:
	    			R1_Insert(&Head1);
	    			break;
	    		case 2:
	    			R2_Insert(&Head2);
	    			break;
	    		case 3:
	    			R3_Insert(&Head3);
	    			break;
	    		case 4:
	    			R4_Insert(&Head4, gender, age, height);
	    			break;
	    		case 5:
	    			R5_Insert(&Head5, gender, age, height);
	    			break;
	    	
	    		}	
			
		}
		
		else if( vi == 3 )
			return;
		
    	}
    	fclose (fp);
    
    	return;
}
