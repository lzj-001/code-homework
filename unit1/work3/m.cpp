#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 50

typedef int DateType;
typedef struct LNode
{
    DateType date;
    LNode* next;
}LNode;

void CreateListF(LNode *&L, DateType a[], int n)
{
    LNode *p;
    L = (LNode*)malloc(sizeof(LNode));
    L->next = NULL;
    for(int i = 0;i < n;i++)
    {
        p = (LNode*)malloc(sizeof(LNode));
        p->date = a[i];
        p->next = L->next;
        L->next = p;
    }
}

void PrintList(LNode *&L, DateType a[], int n)
{
    LNode *p;
    p = L->next;//因为要输出数值，所以要跳过头结点
    for(int i = 0;i < n;i++)
    {
        printf("%d ",p->date);
        p = p->next;
        if(p == NULL)
            break;
    }
    printf("\n");
}

int main()
{
    int n;
    LNode *L = NULL;
    DateType date[MAXSIZE];


    printf("length:");
    scanf("%d",&n);
    printf("date:");
    for(int i = 0;i < n;i++)
    {
        scanf("%d",&date[i]);
    }

    CreateListF(L,date,n);
    PrintList(L,date,n);

    return 0;
}