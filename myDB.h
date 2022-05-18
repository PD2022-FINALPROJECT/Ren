#ifndef myDB_H
#define myDB_H
/*
 * FTN = Food_Type_Name
 * FTC = Food_Type_Calorie
 * FTS = Food_Type_Serving
 */
char *FTN[] = {"Fruit", "Vegetable", "Grains", "Protein", "Milk"};
int FTC[] = { 60, 25, 70, 75, 42};
int FTS[] = { 6, 3, 3, 3, 6};

struct diet{
    int fruit, vegetable, grains, protein, milk;
    struct node *prior, *next;
};



#endif