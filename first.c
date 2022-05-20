#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "first.h"

#define DEBUG 0
#define MAX_NAME_LENGTH 100

void create_marks_csv( int sim_or_det, int recommend_diet, int record_type, float weight, int gender, int age, float height ){
	FILE *fp;

	char filename[MAX_NAME_LENGTH];
	printf("\nPlease remind your filename\n");
	printf("Filename must not exceed %d characters!!!\n", MAX_NAME_LENGTH);
	scanf("%s", filename);
	
	printf("\nCreating %s.csv file\n\n",filename);
	strcmp(filename, strcat(filename,".csv"));
	
	fp=fopen(filename,"w+");
	
	//簡易紀錄及不想紀錄基礎代謝熱量開新csv 
    
	if( (sim_or_det == 2)){
		fprintf(fp,"Record,Simple_or_Detail,Recommend_Diet");
		fprintf(fp,"\n%d,%d,%d\n\n", 1,sim_or_det, recommend_diet);
		fprintf(fp,"Year,Month,Day,Weight\n");
		fclose(fp);
		printf("\n %sfile created\n\n",filename);
		return;
	}
    
    	//細節紀錄但不希望計算基礎代謝
    	if(gender == 3){
        		fprintf(fp,"Record,Simple_or_Detail,Recommend_Diet,Record_Type\n");
        	if(record_type == 1)
			fprintf(fp,"%d,", 2);
	    	else
		    	fprintf(fp,"%d,", 3);
		fprintf(fp,"%d,%d,%d\n\n",sim_or_det, recommend_diet, record_type);
		fprintf(fp,"Year,Month,Day,Weight");
        
        	if(record_type == 1)
		    	fprintf(fp,",Heat\n");
	    	else
		    	fprintf(fp,",Heat,BLD\n");
		
		fclose(fp);
		printf("\n%sfile created\n\n",filename);
		return;
    	}
	
	//詳細紀錄且想紀錄基礎代謝熱量
	fprintf(fp,"Record,Simple_or_Detail,Recommend_Diet,Record_Type,Gender,Age,Height\n");
	if(record_type == 1)
		fprintf(fp,"%d,", 4);
	else
		fprintf(fp,"%d,", 5);
	fprintf(fp,"%d,%d,%d,%d,%d,%.1f\n\n", sim_or_det, recommend_diet, record_type, gender, age, height);
	
	fprintf(fp,"Year,Month,Day,Weight,Metabolism");
    
	if(record_type == 1)
		fprintf(fp,",Heat\n");
	else
		fprintf(fp,",Heat,BLD\n");
	
	fclose(fp);
	printf("\n%s file created\n\n",filename);
	return;
	
}

int first(void){
	/*
	當使用者第一次開啟此程式,則須先填寫一些基本設定
	詳細紀錄使用者往後的紀錄方式,同時此模式基本只會
	進入一次,因此提醒使用者必須想好再進行填寫
	*/
	printf("\nOnce the program filled in, it can't be modified\n");
	printf("Please fill in carefully\n");
	
	//確認使用者希望詳細紀錄抑或是簡單紀錄
	int sim_or_det;
	printf("\nhow do you want to record：\n");
	printf("[1] Detailed Record (Contain weight and calories)\n[2] Simple Record (Only contain weight)\n");
	while(1){
		scanf("%d", &sim_or_det);
		if( (sim_or_det == 1) || (sim_or_det == 2))
			break;
		else
			printf("please input 1 or 2\n");
	}
	
	//確認使用者是否有需推薦餐點的服務
	int recommend_diet;
	printf("\nWhether to be recommended for a diet\n");
	printf("[1] Yes (You need to input the content of today's ingestion)\n[2] No\n");
	while(1){
                scanf("%d", &recommend_diet);
                if( (recommend_diet == 1) || (recommend_diet == 2))
                       	break;
                else
                        printf("please input 1 or 2\n");
        }
	
	//若詳細紀錄則詢問使用者依各餐熱量登記或整日熱量登記
	int record_type = 0;
	if( sim_or_det == 1 ){
		
		printf("\nwhat kind of record do you want\n");
		printf("[1] Daily (Record total daily calorie intake)\n[2] Diet (Record calories per meal)\n");
		while(1){
                	scanf("%d", &record_type);
                	if( (record_type == 1) || (record_type == 2))
                        	break;
                	else
                        	printf("please input 1 or 2\n");
        	}

	}

	#if DEBUG
	printf("sim_or_det %d\n", sim_or_det);
	printf("recommended_diet %d\n", recommend_diet);
	printf("record_type %d\n", record_type);
	#endif
		
	//首先紀錄使用者當前的體重
	float weight = -1;
	
	printf("\nRecord your current basics values\n");
	
	int gender = -1, age = -1;
	float metabolism = -1, height = -1;
	
	//將使用者前面填寫之內容歸類為往後執行程序篩選
	if( sim_or_det == 2 ){
		create_marks_csv(sim_or_det, recommend_diet, record_type, weight, gender, age, height);
		return recommend_diet;
		
	}
	else{
	
		//讓使用者選擇性別與是否需紀錄基礎熱量消耗
		printf("\nWhat is your gender\n");
		printf("[1] Male [2] Female \n[3] Unwilling to tell(don't want to calculate basal metabolism)\n");
		scanf("%d", &gender);
		while( gender != 1 && gender != 2 && gender != 3){
			printf("gender must be 1, 2 or 3\n");
			scanf("%d", &gender);
		}
		
		//不紀錄基礎消耗
		if(gender == 3){
			create_marks_csv(sim_or_det, recommend_diet, record_type, weight, gender, age, height);
			return recommend_diet;
		}
		
		//若不提供身高與體重則無法進行基礎熱量消耗的計算	
		int c = -1;
		
		printf("\nWould you like to reveal your height and age?\n");
		printf("we will use your height and weight to calculate metabolism\n");
		printf("[1] yes [2] very willing [3] no!!!\n");
		scanf("%d", &c);
		while( c != 1 && c != 2 && c != 3){
			printf("input must be 1, 2 or 3\n");
			scanf("%d", &c);
		}
	
		if(c == 3){
			printf("you don't have this option\n");
			printf("or you can exit and reopen this program !!!\n");
			exit(1);
		}
			
		printf("\ninput your height (unit:cm) \n");
		while(height < 0){
			scanf("%f", &height);
			if(height < 0)
				printf("height must > 0\n");
		}
			
		printf("\ninput your age \n");
		while(age < 0){
			scanf("%d", &age);
			if(age < 0)
				printf("age must > 0\n");
		}
		
		create_marks_csv(sim_or_det, recommend_diet, record_type, weight, gender, age, height);
		
		
	}
	
	return recommend_diet;
	
	#if DEBUG
	printf("gender %d\n", gender);
	printf("metabolism %f\n", metabolism);
	#endif

		

}