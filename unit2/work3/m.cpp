/*
1：定义循环队列的结构体(提示:与顺序队列同),假设最大空间为8
   顺序队列结构体的定义，包括数组、队头指针及队尾指针
2：实现循环队列各种基本操作的算法；
包括：队列的初始化算法,入队算法,出队算法,判空算法，判满算法；(注:以牺牲掉一个存储空间作为判满的条件)；
初始化一个空队列，让元素入队，让队头元素出队，判断队列中是否已无元素，判断队列中元素是否已满。
3：在主函数中定义一个循环队列,并调用相应的函数实现队列的初始化、让一组数据2,3,4,5,6入队列、然后让前3个数据出队列,
然后再让7,8,9,10,11,12这些数据入队列,最后让队列中所剩的数据全部出队列；要求显示每一次操作的结果;
*/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<windows.h>
#define MAXSIZE 9//用了头指针始终为空的办法判断队列是否已满，所以长度为数据元素个数+1


typedef int ElemType;
typedef struct
{
    ElemType date[MAXSIZE];
    int front, rear;
} SqQueue;

//初始化队列
void CreatQueue(SqQueue *&q)
{
    q = (SqQueue*)malloc(sizeof(SqQueue));
    q->front = -1;
    q->rear = -1;
}

//判空队列
bool QueueEmpty(SqQueue *q)
{
    if(q->front == q->rear) return true;//空

    return false;//非空
}

//判满队列
bool QueueFull(SqQueue *q)
{
    if(((q->rear + 1) % MAXSIZE) == q->front) return true;//满

    return false;//未满
}

//入队
bool IntoQueue(SqQueue *&q, ElemType e)
{
    //判断队列是否已满
    if(QueueFull(q)) return false;

    //printf("%d\n",e);
    q->rear = (q->rear + 1) % MAXSIZE;
    q->date[q->rear] = e;
    return true;
}

//出队
bool OutQueue(SqQueue *&q, ElemType &e)
{
    //判断队列是否为空
    if(QueueEmpty(q)) return false;

    q->front = (q->front + 1) % MAXSIZE;
    e = q->date[q->front];
    return true;
}

/*在主函数中定义一个循环队列,并调用相应的函数实现队列的初始化、让一组数据2,3,4,5,6入队列、然后让前3个数据出队列,
然后再让7,8,9,10,11,12这些数据入队列,最后让队列中所剩的数据全部出队列；要求显示每一次操作的结果*/
int main()
{
    // 设置控制台为UTF-8编码
    SetConsoleOutputCP(65001);

    SqQueue *q = NULL;
    CreatQueue(q);
    ElemType date1[5] = {2,3,4,5,6}, date2[6] = {7,8,9,10,11,12};
    ElemType e;

    for(int i = 0;i < 5;i++)
    {
        IntoQueue(q,date1[i]);
    }

    printf("第一次输出：");
    for(int i = 0;i < 3;i++)
    {
        OutQueue(q,e);
        printf("%d ",e);
    }

    for(int i = 0;i < 6;i++)
    {
        IntoQueue(q,date2[i]);
    }
    printf("\n");

    printf("第二次输出：");
    while(!QueueEmpty(q))
    {
        OutQueue(q,e);
        printf("%d ",e);
    }


    return 0;
}