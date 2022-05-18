#ifndef R3_H
#define R3_H
 
/*********************** 
 * record 3 相關之函式 *
 ***********************/

//different record type have different struct


struct R3{
	int year, month, day, bld;
	float weight, heat;
	struct R3 *next;
};

struct R3 *R3_Read_File(FILE *fp);

void R3_View(struct R3 *Head);

void R3_Insert(struct R3 **Head);

#endif