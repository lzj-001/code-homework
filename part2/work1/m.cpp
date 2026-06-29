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
    ElemType date[MAXSIZE],put[MAXSIZE];
    int length, i;

    InitStack(&s);

    printf("length:");
    scanf("%d",&length);
    printf("date:");
    for(i = 0;i < length;i++)
    {
        scanf("%d",&date[i]);
    }

    for(i = 0;i < length;i++)
    {
        PushStack(&s,date[i]);
    }

    for(i = 0;i < length;i++)
    {
        PopStack(&s,&put[i]);
    }

    for(i = 0;i < length;i++)
    {
        printf("%d ",put[i]);
    }
    printf("\n");

    return 0;
}