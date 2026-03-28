/*
 * 实验一：线性表的顺序存储结构
 * 实验内容：
 * 1：初始化线性表
 * 2：完成线性表中插入元素算法
 * 3：完成在线性表中删除元素的算法
 * 4：输出线性表中所有元素的算法
 * 5：在主函数中调用这些算法，实现初始化线性表L,并且向其中依次调用插入函数顺序插入值6，22，33，44；然后删除原线性表中第1个元素，显示输出剩下的元素
 */
#include<stdio.h>
#define MAXSIZE 50
typedef int DateType;
typedef struct SqList//线性表数据类型的定义
{
    DateType date[MAXSIZE];
    int length;
}SqList;

void InitSqList(SqList *L)//初始化
{
    L->length=0;
}

void InsertSqList(SqList *L, int i, DateType x)//插入元素
{
    int j;
    if(L->length>MAXSIZE)
    {
        printf("表已满，无法插入!\n");
        return;
    }
    if(i<1||i>L->length+1)
    {
        printf("插入元素错误!\n");
        return;
    }

    for(j=L->length;j>=i;j--)
    {
        L->date[j]=L->date[j-1];
    }
    
    L->date[j]=x;//此时j为i-1，对应顺序表第i个位置
    L->length++;
}

void DeleteSqList(SqList *L, int i)//删除函数
{
    int j;
    if(i<1||i>L->length)
    {
        printf("删除位置不合法!\n");
    }

    for(j=i;j<=L->length;j++)
    {
        L->date[j-1]=L->date[j];
    }
    L->length--;
}

void PrintList(SqList L)//输出函数
{
    int i;
    if(L.length==0)
    {
        printf("表为空!\n");
        return;
    }
    for(i=0;i<L.length;i++)
    {
        printf("%d ",L.date[i]);
    }
        printf("\n");
}

int main()
{
    SqList L;
    int i, a[4]={6, 22, 33, 44};
    InitSqList(&L);

    for(i=1;i<=4;i++)
    {
        InsertSqList(&L, i, a[i-1]);
    }

    PrintList(L);
    DeleteSqList(&L, 1);
    PrintList(L);

    return 0;
}