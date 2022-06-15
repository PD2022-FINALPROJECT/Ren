
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<unistd.h>

#include "myDB.h"
#include "RecommendCalories.h"

void recommend()
{

    int weight, sex;
    char sex_c;
    double body_coefficient;
    printf("\n");
    printf("We will calculate your calorie requirement using the formula below：\n");
    printf("----------------------------------------\n");
    printf("Weight (kg) x (Girls 22/Boys 24) x Physical Activity Coefficient\n");
    printf("Physical activity coefficients are as follows:\n");
    printf("【1.1】Long-term bedridden or inability to walk\n");
    printf("【1.3】Sedentary or little activity\n");
    printf("【1.5】Occasionally walk or stand\n");
    printf("【1.7】Long-term walking or standing\n");
    printf("【1.9】Hard worker, high activity level\n");
    printf("------------------\n");

    printf("Please enter your weight: ");
    scanf("%d", &weight);
    printf("please input your gender in 'f'(female) or 'm'(male): ");


    scanf("%c",&sex_c);
    while(sex_c != 'f' && sex_c !='m')
    {
        printf("Please input the right formula.\n");
        printf("please input your gender in 'f'(female) or 'm'(male): ");
        scanf("%c", &sex_c);

    }

    if(sex_c == 'f') sex = 22;
    if(sex_c == 'm') sex = 24;
    printf("\n");
    printf("Please enter your Physical Activity Coefficient: ");
    scanf("%lf", &body_coefficient);

    double need_calories = weight * sex * body_coefficient;
    printf("Your daily calorie requirement is: %.2lf\n", need_calories);

    int sum_calories = 1000;
    if(sum_calories > need_calories)
    {
        printf("You have consumed more calories than your recommended daily requirement.\n");
        return ;
    }

    int differ_calories = need_calories - sum_calories;
    int recommend_calories = 0;
    int recommend_count = 0;
    int rand_type, rand_food;
    int cal;

    printf("We recommend the following diet (kcal/100g): \n");
    while(recommend_calories < differ_calories-50)
    {

        do
        {
            rand_type=rand()%4;
            rand_food = rand() % type_num[rand_type];
            cal = atoi(food_data[rand_type][rand_food][1]);
        } while (cal + recommend_calories > differ_calories);

        recommend_count++;
        recommend_calories = recommend_calories + cal;
        printf("【%d】%s: %s\n", recommend_count, food_data[rand_type][rand_food][0], food_data[rand_type][rand_food][1]);
    }
    printf("If you eat them, your final calories is: %d kcal\n", recommend_calories + sum_calories);
}

int count_calories() //會回傳總攝取熱量
{
    int kind; //決定輸入食物類別
    char input_name[100]; //輸入的食物名稱
    int sum_calories = 0; //儲存總類別熱量。
    int temp_calories = 0; //儲存暫時輸入熱量。
    int is_keep_input = 0; //決定是否繼續輸入。

    //此迴圈可以搜尋目標食物，得知其熱量後可輸入攝取值。
    do
    {
        //輸入欲輸入食物類別，並導引目標資料庫
        printf("\n");
        printf("What kind of food do you want to enter？\n");
        printf("Please enter the corresponding number：");
        printf("【1】Fruits【2】Vegetables 【3】Whole grains and roots 【4】Beans, eggs, fish and meat 【5】Low-fat dairy\n");
        scanf("%d", &kind);

        //輸入食物名稱
        printf("Please enter the name of the kind you ingested and we will list all items in the database that contain this name. (Please always enter lowercase)！\n");
        printf("Your input：");
        scanf("%s", input_name);

        //輸出結果
        printf("The name you entered, the database contains the following results:\n");

        //開始搜尋
        int count = 0; //宣告總結果量
        int room = 0;
        while(room < type_num[kind-1])
        {
            if(strstr(food_data[kind-1][room][0],input_name)!=NULL)
            {
                count++;
                printf("【%d】 %s：%s\t(kcal/100g)\n", count, food_data[kind-1][room][0], food_data[kind-1][room][1]);
                
            }
            room++;
        }
        printf("The database has a total of %d results。\n",count);

        //開始輸入攝取熱量
        if(count != 0)
        {
            printf("Please enter your calorie intake:");
            scanf("%d", &temp_calories);
            sum_calories = sum_calories + temp_calories;
        }
        else
        {
            printf("The database does not have an item with this name.\n");
        }
        
        //詢問是否繼續輸入
        printf("If you want to continue, please enter 【1】, otherwise please enter 【0】\n");
        scanf("%d", &is_keep_input);

    } while (is_keep_input == 1);

    //輸出總熱量
    printf("Your total current calorie intake is: %d\n", sum_calories);
    return sum_calories;
}
