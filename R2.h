#ifndef R2_H
#define R2_H

/*********************** 
 * record 2 相關之函式 *
 ***********************/

struct R2{
	int year, month, day;
	float weight, heat;
	struct R2 *next;
};

struct R2 *R2_Read_File(FILE *fp);

void R2_View(struct R2 *Head);


void R2_Insert(struct R2 **Head);

#endif
