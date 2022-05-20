#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "path.h"
#include "Record.h"

#define DEBUG 1

/*
讀取csv檔的record
根據path至函式執行
*/
void path(void){
	
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
    	int record, check_record = 0, recommended_diet, gender = 0, age = 0, height = 0;
    	
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
    	
    	struct Record *Head = NULL;
	
	Head = Read_File(fp, record);
	
	int vi;
	    	
	while(1){
		
		printf("\nView current profile or input new data\n");
		printf("[1] view [2] input [3] delete [4] modify [5] quit:\n");
		
		scanf("%d", &vi);
		while( !((vi == 1) || (vi == 2) || (vi == 3) || (vi == 4) || (vi == 5)) ){
			printf("please input 1, 2, 3, 4 or 5\n");
			scanf("%d", &vi);
		}
		
		switch (vi){
	    		case 1:
	    			View(Head, record);
	    			break;
	    		case 2:
	    			Insert(&Head, record, gender, age, height);
	    			break;
	    		case 3:
	    			Delete(&Head, record);
	    			break;
	    		case 4:
	    			Modify(Head, record, gender, age, height);
	    			break;
	    		case 5:
	    			return;
	    	
		}
	}
	
    	fclose (fp);
    
    	return;
}
