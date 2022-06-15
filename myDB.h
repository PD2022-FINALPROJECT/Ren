
//myDB.h
#ifndef myDB_H
#define myDB_H
#define fruit_datanum 16
#define vegetable_datanum 7
#define grains_datanum 6
#define protein_datanum 20
#define milk_datanum 4

//food_data 資料庫參考網站：https://www.cfs.gov.hk/tc_chi/nutrient/search1.php
int type_num[5] = {fruit_datanum, vegetable_datanum, grains_datanum, protein_datanum, milk_datanum};

//【1】水果類【2】蔬菜類【3】全榖根莖類【4】豆蛋魚肉類【5】低脂乳品類
const char *food_data[5][100][2] = {{{"durian", "136"}, {"canna", "124"}, {"shakya", "104"}, {"apple banana", "93"}, {"avocado", "92"}, {"american green grapes", "87"}, {"american Purple Grape", "80"}, {"cherry", "75"}, {"longan", "73"}, {"seedless red grapes", "72"}, {"white cherry", "69"}, {"American red grapes", "69"}, {"yuhebao lychee", "68"}, {"passion fruit", "66"}, {"black beauty Grape", "66"}, {"Kyoho grapes", "64"}},
                                    {{"cabbage","13"},{"winter melon","13"},{"pumpkin","26"},{"lettuce","24"},{"spinach","23"},{"radish","16"},{"water spinach","27"}},
                                    {{"oat","389"},{"white sticky rice","97"},{"rice","130"},{"brown rice","112"},{"corn","348"},{"porridge","46"}},
                                    {{"pig skin", "491"}, {"beef pork belly hot pot pork slices", "430"}, {"bone in beef short ribs", "360"}, {"pork trotters", "331"}, {"duck reward", "304"}, {"boneless Beef Short Ribs", "290"}, {"duck legs", "282"}, {"beef hot pot slices", "250"}, {"braised pork feet", "237"}, {"pig ear", "233"}, {"Cherry Duck Breast Fillets", "227"}, {"skin-on chicken breast", "219"}, {"grilled chicken wings", "217"}, {"chicken feet", "216"}, {"Silkie", "213"}, {"ground pork", "218"}, {"beef rib", "225"}, {"roast chicken", "233"}, {"Milkfish", "200"}, {"Salmon", "222"}},
                                    {{"cheese","43"},{"fresh goat milk","59"},{"milkshake","110"},{"milk","54"}}};
                                    


#endif