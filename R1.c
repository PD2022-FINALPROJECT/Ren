#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "record.h"
#include "R1.h"

//將csv檔內資料串成link list
struct R1 *R1_Read_File(FILE *fp){

	char line[MAX_LINE_SIZE];
    	char *result = NULL;
    	int cnt = 0;
    	
    	struct R1 *head, *current;
	
	while(fgets(line, MAX_LINE_SIZE, fp) != NULL)
        	if( !isalpha(*result) )
    			break;
    			
    	while(fgets(line, MAX_LINE_SIZE, fp) != NULL){
    		
    		cnt++;
    		
    		struct R1 *temp = malloc(sizeof(struct R1));
    		
    		result = strtok(line, ",");
    		temp->year = atoi(result);
    		
    		result = strtok(NULL, ",");
    		temp->month = atoi(result);
    		
    		result = strtok(NULL, ",");
    		temp->day = atoi(result);
    		
    		result = strtok(NULL, ",");
    		temp->weight = atof(result);
    			
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
void R1_View(struct R1 *Head){

	if(!Head){
		printf("The profile is empty!!!\n");
		return;
	}
	
	struct R1 *temp = Head;
	printf("\nYear\tMonth\tDay\tWeight\n");
	while(temp){
		printf("%d\t", temp->year);
		printf("%d\t", temp->month);
		printf("%d\t", temp->day);
		printf("%.1f\n", temp->weight);
		temp = temp->next;
	}
	
	return;
		
}

//按照年月日插入資料
void R1_Insert(struct R1 **Head){
	
	struct R1 *temp, *current;
	temp = *Head;
	current = temp;
	
	struct R1 *temp_insert = malloc(sizeof(struct R1));
	
	int y, m, d;
	float w;
	
	printf("\nPlease input the data as below\n");
	printf("example:2022 5 5 58.2\n");
	scanf("%d %d %d %f", &y, &m, &d, &w);
	while(!y || !m || !d || !w || (y < 0) || (m < 0) || (d < 0) || (w < 0)){
		printf("\nPlease input the data as example\n");
		scanf("%d %d %d %f", &y, &m, &d, &w);
	}
	
	temp_insert->year = y;
	temp_insert->month = m;
	temp_insert->day = d;
	temp_insert->weight = w;
	temp_insert->next = NULL;
	
	if(!temp){
		*Head = temp_insert;
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