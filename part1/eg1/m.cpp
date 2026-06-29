#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 50

typedef int DateType;
typedef struct LNode
{
    DateType date;
    LNode* next;
}LNode;

void CreateListR(LNode *&L, DateType a[], int n)
{
    LNode *p, *s;
    L = (LNode*)malloc(sizeof(LNode));
    s = L;
    for(int i = 0;i < n;i++)
    {
        p = (LNode*)malloc(sizeof(LNode));
        p->date = a[i];
        s->next = p;
        s = s->next;
    }
    s->next = NULL; 
}

void Split(LNode *&L, LNode *&L1, LNode *&L2)//L1为头插法，L2为尾插法，所以L1需要r1定位尾结点，L2只需要一个指针定位
{
    LNode *p, *q, *r1;
    L1 = L;
    r1 = L1;
    p = L1->next;
    L2 = (LNode*)malloc(sizeof(LNode));
    L2->next = NULL;
    while(p != NULL)
    {
        r1->next = p;
        r1 = p;
        p = p->next;
        if(p != NULL) {
            q = p->next;
            p->next = L2->next;
            L2->next = p;
            p = q;
        }
    }
    r1->next = NULL;
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

void CloseList(LNode *&L, int n)
{
    LNode *p, *q;
    p = L;
    q = p->next;
    while(q != NULL)
    {
        free(p);
        p = q;
        q = q->next;
    }
    free(p);
}

int main()
{
    int n, insert_index, delete_index;
    LNode *L, *L1, *L2;
    DateType date[MAXSIZE], insert_date, delete_date;
    L = NULL;

    printf("length:");
    scanf("%d",&n);
    printf("date:");
    for(int i = 0;i < n;i++)
    {
        scanf("%d",&date[i]);
    }

    CreateListR(L,date,n);
    PrintList(L,date,n);

    Split(L, L1, L2);
    PrintList(L1,date,n);
    PrintList(L2,date,n);
    CloseList(L,n);

    return 0;
}