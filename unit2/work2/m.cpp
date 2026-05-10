/*
利用栈将10进制数25转化为对应的2进制数输出
   利用栈后进先出的特点刚好可以符合10进制数向非10进制数中求余以及输出余数的过程。
*/
#include<stdio.h>
#define MAXSIZE 100

typedef int ElemType;
typedef struct
{
    ElemType date[MAXSIZE];
    int top;
} SqStack;

void InitStack(SqStack *s)
{
    s->top = 0;
}

int  StackEmpty(SqStack *s)
{
    return (s->top == 0);
}

int StackFull(SqStack *s)
{
    return (s->top == MAXSIZE);
}

int PushStack(SqStack *s,ElemType x)
{
    if(StackFull(s))
    {
        printf("表已满！\n");
        return -1;
    }
    s->date[s->top] = x;
    s->top++;
    return 1;
}

int PopStack(SqStack *s,ElemType *x)
{
    if(StackEmpty(s))
    {
        printf("表为空！\n");
        return -1;
    }
    s->top--;
    *x = s->date[s->top];
    return 1;
}

int main()
{
    SqStack s;
    ElemType a, b[MAXSIZE], c, put[MAXSIZE];
    int i, length;

    InitStack(&s);

    printf("输入十进制数：");
    scanf("%d",&a);

    c = a;
    for(i = 0;c != 0;i++)
    {
        b[i] = c % 2;
        c = c / 2;
        PushStack(&s,b[i]);
    }
    length = i;
    
    for(i = 0;i < length;i++)
    {
        PopStack(&s,&put[i]);
    }

    printf("二进制数为：");
    for(i = 0;i < length;i++)
    {
        printf("%d ",put[i]);
    }
    printf("\n");



    return 0;
}