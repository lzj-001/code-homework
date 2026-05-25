// 1：定义稀疏矩阵的三元组表的存储结构
// 包括三元组数据类型和三元组顺序表的类型
// 2：把二维稀疏矩阵用三元组表表示和存储
// 采用以行序为主序的方式遍历建立对应的三元组表
// 3：稀疏矩阵的转置
// 将已用三元组表存储好的稀疏矩阵进行转置
// 4：对给定的如下稀疏矩阵进行转置，并输出转置后的三元组表
// 综合使用以上算法实现数组的转置运算稀疏
// 需转置的矩阵如下图所示：
// 3 0 0 0 0
// 0 4 0 1 0
// 5 0 0 0 0
#include<stdio.h>
#define MAXSIZE 100
#define ROW 3
#define COL 5

typedef int Elemtype;
typedef struct 
{
    int col; // 列号
    int row; // 行号
    Elemtype date;

} TupNode; // 三元组定义

typedef struct 
{
    int cols; // 行数
    int rows; // 列数
    int nums; // 非零元的个数
    TupNode date[MAXSIZE]; // 非零元数据元素
    
} TSMatrix; // 三元组顺序表

void CreateMat(TSMatrix &t, Elemtype A[ROW][COL]) // 创建三元组(二维稀疏矩阵用三元组表的表示)
{
    int i, j;
    t.cols = COL;
    t.rows = ROW;
    t.nums = 0;
    for(i = 0;i < t.rows;i++)
    {
        for(j = 0;j < t.cols;j++)
        {
            if(A[i][j] != 0) // 储存非零元素
            {
                t.date[t.nums].date = A[i][j];
                t.date[t.nums].col = j;
                t.date[t.nums].row = i;
                t.nums++;
            }
        }
    }
}

bool Value(TSMatrix &t, Elemtype x, int i, int j) // 为三元组的元素赋值(二维稀疏矩阵用三元组表的存储)
{
    int k = 0, k1;
    if(i >= t.rows || j >= t.cols)
        return false;
    
    // 查找插入位置k
    while(k < t.nums && i > t.date[k].row) // 查找第i行的第一个非零元素
        k++;
    while(k < t.nums && i == t.date[k].row && j > t.date[k].col) // 在的i行查找非零元素
        k++;
    
    if(t.date[k].row == i && t.date[k].col == j)
        t.date[k].date = x;
    else
    {
        for(k1 = t.nums - 1;k1 >= k;k1--) // 使k位置之后的非零元素均后移一格,空出下标为k的位置
        {
            t.date[k1 + 1].date = t.date[k1].date;
            t.date[k1 + 1].col = t.date[k1].col;
            t.date[k1 + 1].row = t.date[k1].row;
        }
        // 插入
        t.date[k].date = x;
        t.date[k].col = j;
        t.date[k].row = i;
        t.nums++;
    }

    return true;
}

void DisMat(TSMatrix t) // 输出三元组
{
    int k;
    if(t.nums <= 0)
        return;
    printf("\trow\tcol\tnum\n");
    printf("\t--------------------\n");
    for(k = 0;k < t.nums;k++)
    {
        printf("\t%d\t%d\t%d\n",t.date[k].row,t.date[k].col,t.date[k].date);
    }
}

void TranTat(TSMatrix t,TSMatrix &tb)
{
    int k, k1 = 0, v;
    tb.cols = t.cols;
    tb.rows = t.rows;
    tb.nums = t.nums;
    if(t.nums != 0)
    {
        for(v = 0;v < t.cols;v++) // 按列循环，使从0~t.cols的列在转置后变为按从0开始的行序输出，省去再次排序的步骤
        {
            for(k = 0;k < t.nums;k++) // k用来扫描所有非零元
            {
                if(t.date[k].col == v) // 当t中存在列号为v的列时
                // t中非零元在行列交换后放入tb中
                {
                    tb.date[k1].date = t.date[k].date;
                    tb.date[k1].col = t.date[k].row;
                    tb.date[k1].row = t.date[k].col;
                    k1++; // k1用以记录tb中非零元的个数
                }
            }
        }
    }
}



Elemtype A[ROW][COL];
int main()
{
    TSMatrix t, tb;

    // A[0][0] = 3;
    // A[1][1] = 4;
    // A[1][3] = 1;
    // A[2][0] = 5;

    CreateMat(t,A);
    printf("%d",t.cols);
    printf("%d",t.rows);
    printf("%d",t.nums);

    Value(t,3,0,0);
    Value(t,4,1,1);
    Value(t,1,1,3);
    Value(t,5,2,0);

    printf("%d",t.nums);

    DisMat(t);

    TranTat(t,tb);

    DisMat(tb);

    return 0;
}



//     查找插入位置k的标准公式
//     while(k < t.nums && i > t.date[k].row) // 查找第i行的第一个非零元素
//         k++;
//     while(k < t.nums && i == t.date[k].row && j > t.date[k].col)
//         k++;