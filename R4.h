#ifndef R4_H
#define R4_H
 
/*********************** 
 * record 4 相關之函式 *
 ***********************/

//different record type have different struct

struct R4{
	int year, month, day;
	float weight, heat, metabolism;
	struct R4 *next;
};

struct R4 *R4_Read_File(FILE *fp);

void R4_View(struct R4 *Head);

void R4_Insert(struct R4 **Head, int gender, int age, float height);

#endif