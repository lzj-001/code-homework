#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    char data;
    struct node *lchild, *rchild;
} bnode, *blink;

// 向二叉排序树插入结点
blink add(blink bt, char ch)
{
    if (bt == NULL)                     // 此位置为空，创建新结点插入数据
    {
        bt = (blink)malloc(sizeof(bnode));
        bt->data = ch;
        bt->lchild = bt->rchild = NULL;
    }
    else if (ch < bt->data)             // 小于根，递归插入左子树
        bt->lchild = add(bt->lchild, ch);
    else                                // 大于等于根，递归插入右子树
        bt->rchild = add(bt->rchild, ch);

    return bt;                          // 返回根结点指针
}

// 中序遍历
void inorder(blink bt)
{
    if (bt == NULL) return;
    inorder(bt->lchild);
    printf("%c ", bt->data);
    inorder(bt->rchild);
}

int main()
{
    blink root = NULL;
    int i, n;
    char x;
    scanf("%d", &n); // 结点总个数为n
    getchar();       // 获取上面语句中多余的回车符
    for (i = 1; i <= n; i++)
    {
        x = getchar();
        root = add(root, x);
    }
    inorder(root);
    printf("\n");
    return 0;
}