#ifndef Record_H
#define Record_H
 
/*********************** 
 * record  相關之函式 *
 ***********************/

//different record type have different struct

struct Record{
	int year, month, day, bld;
	float weight, heat, metabolism;
	struct Record *next;
};

struct Record *Read_File(FILE *fp, int record);

void View(struct Record *Head, int record);

void Insert(struct Record **Head, int record, int gender, int age, float height);

void Delete(struct Record **Head, int record);

void Modify(struct Record *Head, int record, int gender, int age, float height);

int Search(struct Record *Head, int y, int m, int d, int type, int bld);

#endif