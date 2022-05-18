#ifndef R5_H
#define R5_H
 
/*********************** 
 * record 5 相關之函式 *
 ***********************/

//different record type have different struct

struct R5{
	int year, month, day, bld;
	float weight, heat, metabolism;
	struct R5 *next;
};
struct R5 *R5_Read_File(FILE *fp);
void R5_View(struct R5 *Head);
void R5_Insert(struct R5 **Head, int gender, int age, float height);

#endif