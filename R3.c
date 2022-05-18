#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "record.h"
#include "R3.h"

//將csv檔內資料串成link list
struct R3 *R3_Read_File(FILE *fp){

	char line[MAX_LINE_SIZE];
    	char *result = NULL;
    	int cnt = 0;
    	
    	struct R3 *head, *current;
	
	while(fgets(line, MAX_LINE_SIZE, fp) != NULL)
        	if( !isalpha(*result) )
    			break;
    			
    	while(fgets(line, MAX_LINE_SIZE, fp) != NULL){
    		
    		cnt++;
    		
    		struct R3 *temp = malloc(sizeof(struct R3));
    		
    		result = strtok(line, ",");
    		temp->year = atoi(result);
    		
    		result = strtok(NULL, ",");
    		temp->month = atoi(result);
    		
    		result = strtok(NULL, ",");
    		temp->day = atoi(result);
    		
    		result = strtok(NULL, ",");
    		temp->weight = atof(result);
    		
    		result = strtok(NULL, ",");
    		temp->heat = atof(result);
    		
    		result = strtok(NULL, ",");
    		temp->bld = atoi(result);
    			
    		current->next = temp;
    		current = temp;
    		
    		if(cnt == 1)
    			head = temp;
    	}
    	
    	if(!cnt)
    		return NULL;
    	
    	return head;
}

//查看先前所有輸入的資料
void R3_View(struct R3 *Head){

	if(!Head){
		printf("The profile is empty!!!\n");
		return;
	}
	
	struct R3 *temp = Head;
	printf("\nYear\tMonth\tDay\tWeight\tHeat\tBLD\n");
	while(temp){
		printf("%d\t", temp->year);
		printf("%d\t", temp->month);
		printf("%d\t", temp->day);
		printf("%.1f\t", temp->weight);
		printf("%.1f\t", temp->heat);
		printf("%d\n", temp->bld);
		temp = temp->next;
	}
	
	return;
		
}

//按照年月日插入資料
void R3_Insert(struct R3 **Head){
	
	struct R3 *temp, *current;
	temp = *Head;
	current = temp;
	
	struct R3 *temp_insert = malloc(sizeof(struct R3));
	
	int y, m, d, b;
	float w, h;
	
	printf("\nPlease input the data as below\n");
	printf("example:2022 5 5 58.2 1682.2\n");
	scanf("%d %d %d %f %f", &y, &m, &d, &w, &h);
	
	while(!y || !m || !d || !w || !h || (y < 0) || (m < 0) || (d < 0) || (w < 0) || (h < 0) ){
		printf("\nPlease input the data as example\n");
		scanf("%d %d %d %f %f", &y, &m, &d, &w, &h);
	}
	
	printf("[1] breakfast [2] lunch [3] dinner\n");
	scanf("%d", &b);
	
	while( !((b == 1) || (b == 2) || (b == 3)) ){
		printf("\nPlease input 1, 2 or 3\n");
		scanf("%d", &b);
	}
	
	temp_insert->year = y;
	temp_insert->month = m;
	temp_insert->day = d;
	temp_insert->weight = w;
	temp_insert->heat = h;
	temp_insert->bld = b;
	temp_insert->next = NULL;
	
	if(!temp){
		*Head = temp_insert;
		temp_insert->next = NULL;
		return;
	}
	
	temp = temp->next;
	
	if( ( current->year > temp_insert->year)){
		*Head = temp_insert;
		temp_insert->next = current;
		return;
	}
	else{
		if( (current->month > temp_insert->month) ){
			*Head = temp_insert;
			temp_insert->next = current;
			return;
		}
		else{
			if( (current->day > temp_insert->day) ){
				*Head = temp_insert;
				temp_insert->next = current;
				return;
			}
		}
	}
	
	while( current->next ){
		
		if( ( temp->year > temp_insert->year)){
			current->next = temp_insert;
			temp_insert->next = temp;
			break;
		}
		else{
			if( (temp->month > temp_insert->month) ){
				current->next = temp_insert;
				temp_insert->next = temp;
				break;
			}
			else{
				if( (temp->day > temp_insert->day) ){
					current->next = temp_insert;
					temp_insert->next = temp;
					break;
				}
			}
		}
		
		
		current = temp;
		temp = temp->next;
		
	}
	
	if( !temp_insert->next ){
		current->next = temp_insert;
		temp_insert->next = NULL;
	}
	
	return;
		
}