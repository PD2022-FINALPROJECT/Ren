#ifndef R1_H
#define R1_H
 
/*********************** 
 * record 1 相關之函式 *
 ***********************/

//different record type have different struct

struct R1{
	int year, month, day;
	float weight;
	struct R1 *next;
};

struct R1 *R1_Read_File(FILE *fp);

void R1_View(struct R1 *Head);

void R1_Insert(struct R1 **Head);

#endif