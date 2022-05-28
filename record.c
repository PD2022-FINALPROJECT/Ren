#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "path.h"
#include "Record.h"

//將csv檔內資料串成link list
struct Record *Read_File(FILE *fp_r, int record){

	char line[MAX_LINE_SIZE];
    	char *result = NULL;
    	int cnt = 0;
    	
    	struct Record *head, *current;
    	
    	while( fgets(line, MAX_LINE_SIZE, fp_r) ){	
    		cnt++;
    		
    		struct Record *temp = malloc(sizeof(struct Record));
    		
    		result = strtok(line, ",");
    		temp->year = atoi(result);
    		
    		result = strtok(NULL, ",");
    		temp->month = atoi(result);
    		
    		result = strtok(NULL, ",");
    		temp->day = atoi(result);
    		
    		result = strtok(NULL, ",");
    		temp->weight = atof(result);
    		
    		if( record >= 4 ){
	    		result = strtok(NULL, ",");
	    		temp->metabolism = atof(result);
    		}
    		
    		if (!(record == 1)){
    			result = strtok(NULL, ",");
    			temp->heat = atof(result);
    		}
    		
    		if( record == 3 || record == 5 ){
    			result = strtok(NULL, ",");
    			temp->bld = atoi(result);
    		}
    		
    		if(cnt == 1){
    			head = temp;
    			current = head;
    		}
    		else{
    			current->next = temp;
    			current = temp;
    		}
    	}
    	
    	if(!cnt)
    		return NULL;
    	
    	return head;
}

//查看先前所有輸入的資料
void View(struct Record *Head, int record){

	if(!Head){
		printf("The profile is empty!!!\n");
		return;
	}
	
	struct Record *temp = Head;
	printf("\nYear\tMonth\tDay\tWeight");
	
	switch (record){
		case 1:
			printf("\n");
			break;
		case 2:
			printf("\tHeat\n");
			break;
		case 3:
			printf("\tHeat\tBLD\n");
			break;
		case 4:
			printf("\tMetabolism\tHeat\n");
			break;
		case 5:
			printf("\tMetabolism\tHeat\tBLD\n");
			break;
	}
	
	while(temp){
		printf("%d\t", temp->year);
		printf("%d\t", temp->month);
		printf("%d\t", temp->day);
		printf("%.1f\t", temp->weight);
		
		switch (record){
			case 1:
				printf("\n");
				break;
			case 2:
				printf("%.1f\n", temp->heat);
				break;
			case 3:
				printf("%.1f\t", temp->heat);
				printf("%d\n", temp->bld);
				break;
			case 4:
				printf("%.1f\t\t", temp->metabolism);
				printf("%.1f\n", temp->heat);
				break;
			case 5:
				printf("%.1f\t\t", temp->metabolism);
				printf("%.1f\t", temp->heat);
				printf("%d\n", temp->bld);
				break;
		}
		
		temp = temp->next;
	}
	
	return;
		
}

//按照年月日插入資料
void Insert(struct Record **Head, int record,  int gender, int age, float height){
	
	struct Record *temp, *current;
	temp = *Head;
	current = temp;
	
	struct Record *temp_insert = malloc(sizeof(struct Record));
	
	int y, m, d, b = 0;
	float w, h;
	
	printf("\nPlease input the data as below\n");
	printf("example:2022 5 5 58.2");
	
	if( record == 1 ){
		printf("\n");
		scanf("%d %d %d %f", &y, &m, &d, &w);
		while(!y || !m || !d || !w || (y < 0) || (m < 0) || (d < 0) || (w < 0) || (m > 12) || (d > 31)){
			printf("\nPlease input the data as example\n");
			scanf("%d %d %d %f", &y, &m, &d, &w);
		}
	}
	
	else{
		printf(" 1682.2\n");
		scanf("%d %d %d %f %f", &y, &m, &d, &w, &h);
		while(!y || !m || !d || !w || (y < 0) || (m < 0) || (d < 0) || (w < 0) || (m > 12) || (d > 31)){
			printf("\nPlease input the data as example\n");
			scanf("%d %d %d %f %f", &y, &m, &d, &w, &h);
		}
	}
	
	if( record == 3 || record == 5 ){
		printf("[1] breakfast [2] lunch [3] dinner\n");
		scanf("%d", &b);
		
		while( !((b == 1) || (b == 2) || (b == 3)) ){
			printf("\nPlease input 1, 2 or 3\n");
			scanf("%d", &b);
		}
		
		temp_insert->bld = b;
	}
	
	temp_insert->year = y;
	temp_insert->month = m;
	temp_insert->day = d;
	temp_insert->weight = w;
	
	if ( record != 1 )
		temp_insert->heat = h;
	
	temp_insert->next = NULL;
	
	if( gender == 1 )
		temp_insert->metabolism = (10*temp_insert->weight) + (6.25*height) - (5*age) + 5;
		
	else if( gender == 2 )
		temp_insert->metabolism = (10*temp_insert->weight) + (6.25*height) - (5*age) - 161;
	
	if(!temp){
		*Head = temp_insert;
		temp_insert->next = NULL;
		return;
	}
	
	int check;
	check = Search(temp, y, m, d, 1, b);
	
	temp = temp->next;
	
	if( ( current->year > temp_insert->year) ){
		*Head = temp_insert;
		temp_insert->next = current;
		return;
	}
	else if( ( current->year == temp_insert->year) ){
		if( (current->month > temp_insert->month) ){
			*Head = temp_insert;
			temp_insert->next = current;
			return;
		}
		else if( ( current->month == temp_insert->month) ){
			if( (current->day > temp_insert->day) ){
				*Head = temp_insert;
				temp_insert->next = current;
				return;
			}
		}
	}
	
	while( current->next ){
		
		if( ( temp->year > temp_insert->year) ){
			current->next = temp_insert;
			temp_insert->next = temp;
			break;
		}
		else if( ( temp->year == temp_insert->year) ){
			if( (temp->month > temp_insert->month) ){
				current->next = temp_insert;
				temp_insert->next = temp;
				break;
			}
			else if( ( temp->month == temp_insert->month) ){
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

//按照年月日刪除資料
void Delete(struct Record **Head, int record){
	
	struct Record *temp, *current;
	temp = *Head;
	current = temp;
	
	int y, m, d, b = 0;
	float w;
	
	if(!temp){
		printf("The profile is empty!!!\n");
		return;
	}
	
	printf("\nPlease input the data which you want to delete as below\n");
	printf("example:2022 5 5\n");
	scanf("%d %d %d", &y, &m, &d);
	while(!y || !m || !d || (y < 0) || (m < 0) || (d < 0)){
		printf("\nPlease input the data as example\n");
		scanf("%d %d %d", &y, &m, &d);
	}
	
	if( (record == 3) || (record == 5)){
		printf("Please input the data breakfast , lunch or dinner which you want to delete\n");
		printf("[1] breakfast [2] lunch [3] dinner\n");
		scanf("%d", &b);
		while( !((b == 1) || (b == 2) || (b == 3)) ){
			printf("\nPlease input 1, 2 or 3\n");
			scanf("%d", &b);
		}
	}
	
	int check;
	check = Search(temp, y, m, d, 2, b);
	
	if(!check)
		return;
	
	temp = temp->next;
	if( (record == 3) || (record == 5)){
		if( ( current->year == y ) && ( current->month == m ) && ( current->day == d ) &&( current->bld == b )){
			*Head = temp;
			free(current);
			return;
		}
		
		while( temp ){
		
			if( ( temp->year == y ) && ( temp->month == m ) && ( temp->day == d ) && ( temp->bld == b )){
				current->next = temp->next;
				free(temp);
				return;
			}
			
			current = temp;
			temp = temp->next;
		}
	}
	
	else {
		if( ( current->year == y ) && ( current->month == m ) && ( current->day == d ) ){
			*Head = temp;
			free(current);
			return;
		}
		
		while( temp ){
		
			if( ( temp->year == y ) && ( temp->month == m ) && ( temp->day == d ) ){
				current->next = temp->next;
				free(temp);
				return;
			}
			
			current = temp;
			temp = temp->next;
		}
	}
	
	
	while( temp ){
		
		if( ( temp->year == y ) && ( temp->month == m ) && ( temp->day == d )){
			current->next = temp->next;
			free(temp);
			return;
		}
		
		current = temp;
		temp = temp->next;
	}
	
	
	return;
		
}

// Revise
void Modify(struct Record *Head, int record, int gender, int age, float height){

	struct Record *cur;
	int y, m, d, b = 0;
	float w, h;// new stored data

	printf("\nThe data only can modify the weight or heat\n");
	printf("If you want to modify the date\n");
	printf("Please delete the data which you dislike\n");
	printf("And insert the data\n");
	
	int mod;
	printf("\nInput whether you want to only modify the weight or heat\n");
	printf("\n[1] Yes [2] No\n");
	scanf("%d", &mod);
	while( !((mod == 1) || (mod == 2)) ){
		printf("\nPlease input 1 or 2\n");
		scanf("%d", &mod);
	}

	if(mod == 2)
		return;

	printf("\nPlease input the date you want to modify as below\n");
	printf("example:2022 5 5\n");
	scanf("%d %d %d", &y, &m, &d);
	while(!y || !m || !d || (y < 0) || (m < 0) || (d < 0)  || (m > 12) || (d > 31)){
		printf("\nPlease input the data as example\n");
		scanf("%d %d %d", &y, &m, &d);
	}
	
	if( record == 3 || record == 5 ){
		printf("Breakfast, Lunch or Dinner\n");
		scanf("%d", &b);
		
		while( !((b == 1) || (b == 2) || (b == 3)) ){
			printf("\nPlease input 1, 2 or 3\n");
			scanf("%d", &b);
		}
	}
	
	int check;
	check = Search(Head, y, m, d, 3, b);
	
	if(!check)
		return;
		
	for(cur = Head; cur ;cur = cur->next)
		if(cur->year == y && cur->month == m && cur->day == d && cur->bld == b )
			break;
		
	printf("\nPlease input the data modified as below\n");
	printf("example:58.2");
	
	if( record != 1 ){
		printf(" %.1f\n", 1682.2);
		
		scanf("%f %f", &w, &h);
		while( !w || (w < 0) || !h || (h < 0) ){
			printf("\nPlease input the data >0\n");
			scanf("%f %f", &w, &h);
		}

		cur->weight = w;
		cur->heat = h;
		
		if( (record == 4) || (record == 5 )){
			if( gender == 1 )
				cur->metabolism = (10*w) + (6.25*height) - (5*age) + 5;
			
			else
				cur->metabolism = (10*w) + (6.25*height) - (5*age) - 161;
		}
	}
	
	else{ 
		printf("\n");
		scanf("%f", &w);
		while( !w || (w < 0)){
			printf("\nPlease input the data >0\n");
			scanf("%f", &w);
		}
		cur->weight = w;
	}
	
	return;
}

//查找當前的資料是否存在
int Search(struct Record *Head, int y, int m, int d, int type, int bld){
	
	struct Record *cur;
	
	if( !bld ){
		for(cur = Head; cur ;cur = cur->next)
			if(cur->year == y && cur->month == m && cur->day == d)
				break;
	}
	else{
		for(cur = Head; cur ;cur = cur->next)
			if(cur->year == y && cur->month == m && cur->day == d && cur->bld == bld)
				break;
	}
	
	if( cur && (type == 1)){
		printf("This data already exist!!!\n");
		printf("You can choose modify option to modify this data\n");
		return 1;
	}
	
	if(!cur){
		switch (type){
		
			case 2:
				printf("This data doesn't exist!!!\n");
				break;
			case 3:
				printf("This data doesn't exist!!!\n");
				printf("You can choose insert option to insert this data\n");
				break;
		}
		return 0;
	}
	
	return 1;
	 
}

//將link list 寫入 csv檔內
void Write_File(FILE *fp, struct Record *Head, int record, int node_number){
	struct Record *csv_ptr;
	csv_ptr = Head;
	
	char line[MAX_LINE_SIZE];
	char *result = NULL;
	
	int check = 0;
	switch (record)
	{
		case 1:
			while(csv_ptr){
				check++;
				fprintf(fp, "%d,%d,%d,%.1f\n", csv_ptr->year, csv_ptr->month, csv_ptr->day, csv_ptr->weight);
				csv_ptr = csv_ptr->next;
			}
			while(check < node_number){
				fprintf(fp, "NULL,NULL,NULL,NULL\n");
				check++;
			}
			break;
		case 2:
			while(csv_ptr){
				check++;
				fprintf(fp, "%d,%d,%d,%.1f, %.1f\n", csv_ptr->year, csv_ptr->month, csv_ptr->day, csv_ptr->weight, csv_ptr->heat);
				csv_ptr = csv_ptr->next;
			}
			while(check < node_number){
				fprintf(fp, "NULL,NULL,NULL,NULL,NULL\n");
				check++;
			}
			break;
		case 3:
			while(csv_ptr){
				check++;
				fprintf(fp, "%d,%d,%d,%.1f,%.1f,%d\n", csv_ptr->year, csv_ptr->month, csv_ptr->day, csv_ptr->weight, csv_ptr->heat, csv_ptr->bld);
				csv_ptr = csv_ptr->next;
			}
			while(check < node_number){
				fprintf(fp, "NULL,NULL,NULL,NULL,NULL,NULL\n");
				check++;
			}
			break;
		case 4:
			while(csv_ptr){
				check++;
				fprintf(fp, "%d,%d,%d,%.1f,%.1f,%.1f\n", csv_ptr->year, csv_ptr->month, csv_ptr->day, csv_ptr->weight, csv_ptr->metabolism, csv_ptr->heat);
				csv_ptr = csv_ptr->next;
			}
			while(check < node_number){
				fprintf(fp, "NULL,NULL,NULL,NULL,NULL,NULL\n");
				check++;
			}
			break;
		case 5:
			while(csv_ptr){
				check++;
				fprintf(fp, "%d,%d,%d,%.1f,%.1f,%.1f,%d\n", csv_ptr->year, csv_ptr->month, csv_ptr->day, csv_ptr->weight, csv_ptr->metabolism, csv_ptr->heat, csv_ptr->bld);
				csv_ptr = csv_ptr->next;
			}
			while(check < node_number){
				fprintf(fp, "NULL,NULL,NULL,NULL,NULL,NULL,NULL\n");
				check++;
			}
			break;
	}
}

//用link list 創一個繪圖的csv檔
void Create_Draw_Csv_File(FILE *fp, struct Record *Head, int record, int node_number){
	struct Record *csv_ptr, *current, *prior, *temp_delete;
	csv_ptr = Head;
	
	char line[MAX_LINE_SIZE];
	char *result = NULL;
	
	
	if( (record == 3) || (record == 5) ){
		current = csv_ptr->next;
		prior = csv_ptr;
		while(current){
			struct Record *temp_delete = current;
			if( (current->year == prior->year) && (current->month == prior->month) && (current->day == prior->day) && (current->bld != prior->bld) ){
				prior->heat = prior->heat + current->heat;
				prior->next = current->next;
				current = current->next;
				free(temp_delete);
			}
			else{
				prior = current;
				current = current->next;
			}
		}
	}
	
	int check = 0;
	switch (record)
	{
		case 1:
			while(csv_ptr){
				check++;
				fprintf(fp, "%d,%d,%d,%.1f\n", csv_ptr->year, csv_ptr->month, csv_ptr->day, csv_ptr->weight);
				csv_ptr = csv_ptr->next;
			}
			break;
		case 2:
			while(csv_ptr){
				check++;
				fprintf(fp, "%d,%d,%d,%.1f, %.1f\n", csv_ptr->year, csv_ptr->month, csv_ptr->day, csv_ptr->weight, csv_ptr->heat);
				csv_ptr = csv_ptr->next;
			}
			break;
		case 3:
			while(csv_ptr){
				check++;
				fprintf(fp, "%d,%d,%d,%.1f,%.1f\n", csv_ptr->year, csv_ptr->month, csv_ptr->day, csv_ptr->weight, csv_ptr->heat);
				csv_ptr = csv_ptr->next;
			}
			break;
		case 4:
			while(csv_ptr){
				check++;
				fprintf(fp, "%d,%d,%d,%.1f,%.1f,%.1f\n", csv_ptr->year, csv_ptr->month, csv_ptr->day, csv_ptr->weight, csv_ptr->metabolism, csv_ptr->heat);
				csv_ptr = csv_ptr->next;
			}
			break;
		case 5:
			while(csv_ptr){
				check++;
				fprintf(fp, "%d,%d,%d,%.1f,%.1f,%.1f\n", csv_ptr->year, csv_ptr->month, csv_ptr->day, csv_ptr->weight, csv_ptr->metabolism, csv_ptr->heat);
				csv_ptr = csv_ptr->next;
			}
			break;
	}
}