#include <stdio.h>
#include <stdlib.h>

typedef struct BiTNode
{
    char data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

// 先序构造二叉树，pre为先序序列，index为当前读取位置
void CreateBiTree(BiTree *T, char *pre, int *index)
{
    if (pre[*index] == '\0' || pre[*index] == '#')
    {
        (*index)++;
        *T = NULL;
        return;
    }
    *T = (BiTree)malloc(sizeof(BiTNode));
    (*T)->data = pre[*index];
    (*index)++;
    CreateBiTree(&((*T)->lchild), pre, index);
    CreateBiTree(&((*T)->rchild), pre, index);
}

// 统计叶结点个数
int CountLeaf(BiTree T)
{
    if (T == NULL)
        return 0;
    if (T->lchild == NULL && T->rchild == NULL)
        return 1;
    return CountLeaf(T->lchild) + CountLeaf(T->rchild);
}

// 求二叉树高度
int BiTreeDepth(BiTree T)
{
    if (T == NULL) return 0;
    int lchild = BiTreeDepth(T->lchild);
    int rchild = BiTreeDepth(T->rchild);
    return (lchild > rchild) ? (lchild + 1) : (rchild + 1);
}

// 释放二叉树
void DestroyBiTree(BiTree *T)
{
    if (*T == NULL) return;
    DestroyBiTree(&((*T)->lchild));
    DestroyBiTree(&((*T)->rchild));
    free(*T);
    *T = NULL;
}

int main()
{
    BiTree bt = NULL;
    char pre[] = "ABD###CE#G##F##";
    int index = 0;

    CreateBiTree(&bt, pre, &index);

    printf("先序序列: %s\n", pre);
    printf("叶结点个数: %d\n", CountLeaf(bt));
    printf("二叉树高度: %d\n", BiTreeDepth(bt));

    DestroyBiTree(&bt);
    return 0;
}