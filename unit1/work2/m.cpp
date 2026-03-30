/*
任务二：线性表的链式表示和实现
1：用尾插法生成单链表,新建一个包含4个结点15,20,25,30的单链表
   每次都在当前最后一个数据元素结点之后插入新元素结点,如为第一个数据元素结点就直接放在头结点后面成为第一个数据元素结点
2：输出单链表中元素的值；依次输出链表中结点的值;
   访问单链表每次只能从头结点出发顺次向后查找或访问结点的值;
3：在单链表中插入元素；在链表的某个位置插入值为35的一个结点并输出插入后的结果
    在单链表中第i个位置（1<=i<=n+1），插入某个元素
4：在单链表中删除元素；在链表某个位置删除一个结点，然后输出删除后的结果
   删除单链表中第i个位置（1<=i<=n）的元素
5：销毁链表;释放链表中的所有结点所占用的空间。
*/
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

bool InsertList(LNode *&L, int i, DateType e, DateType a[], int n)
{
    int j = 0;
    LNode *p, *q;
    p = L;

    if(i <= 0)
    {
        printf("i值不合法！\n");
        return false;
    }
    //j < i-1用来满足(p需要指向第i-1个结点)的条件，此时只要满足 p->next != NULL (此时p指向第i-1个结点)就可以插入，即使是第n+1个位置也可以
    while(j < i-1 && p->next != NULL)//p需要指向第i-1个结点，才能定位第i个结点
    {
        j++;
        p= p->next;
    }
    if(p->next == NULL)
    {
        return false;
    }

    else
    {
        q = (LNode*)malloc(sizeof(LNode));
        q->date = e;
        q->next = p->next;
        p->next = q;
    }

    PrintList(L,a,n+1);
    return true;
}

bool DeleteList(LNode *&L, int i, DateType &e, DateType a[], int n)
{
    int j = 0;
    LNode *p, *q;
    p = L;

    if(i <= 0)
    {
        printf("i值不合法！\n");
        return false;
    }
    while(j < i-1 && p->next != NULL)//p需要指向第i-1个结点，才能定位第i个结点
    {
        j++;
        p= p->next;
    }
    if(p->next == NULL)
    {
        return false;
    }

    else
    {
        q = p->next;

        //不存在第i个结点
        if(q == NULL)
        {
            return false;
        }

        e = q->date;
        p->next = q->next;
        free(q);

        PrintList(L,a,n);
        return true;
    }
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
    LNode *L = NULL;
    DateType date[MAXSIZE], insert_date, delete_date;

    printf("length:");
    scanf("%d",&n);
    printf("date:");
    for(int i = 0;i < n;i++)
    {
        scanf("%d",&date[i]);
    }

    CreateListR(L,date,n);
    PrintList(L,date,n);

    printf("insert_index,insert_date:");
    scanf("%d",&insert_index);
    scanf("%d",&insert_date);
    InsertList(L,insert_index,insert_date,date,n);
    
    printf("delete_index:");
    scanf("%d",&delete_index);
    DeleteList(L,delete_index,delete_date,date,n);

    CloseList(L,n);

    return 0;
}