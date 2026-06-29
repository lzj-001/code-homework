/*
1：理解哈夫曼树及哈夫曼编码的思想；假设用于通信的电文仅由五个字母组成，字母在电文中出现的频率分别为2，4，8，12，13。
试为这五个字母（假设为A--E）设计哈夫曼编码。要求画出哈夫曼树，写出各字母的哈夫曼编码。

2：编程实现构造哈夫曼树及进行哈夫蔓编码；编程实现基本任务一中题目的内容，要求：
1）定义哈夫曼树的结点结构；
2）定义存放单个叶结点编码的哈夫蔓编码结构体；
3）编写建立哈夫曼树的算法
4）编写求哈夫曼编码的算法
5）在主程序中调用以上相关算法输出上面题目中的哈夫曼树数组的终态及各字符对应的哈夫曼编码
*/
#include <stdio.h>
#include <string.h>
#define N 100

typedef struct
{
    char date;                  // 结点值
    double weight;              // 权重
    int parent, lchild, rchild; // 双亲结点，以及左，右孩子节点
} HTNode;

typedef struct
{
    char cd[N]; // 存放当前节点的哈夫曼编码
    int start;  // 表示cd[start...n0]部分是哈夫曼编码
} HCode;

void CreateHT(HTNode ht[], int n0) // 构造哈夫曼树
{
    int i, k, lnode, rnode;
    double min1, min2;
    for (i = 0; i < 2 * n0 - 1; i++)
    {
        ht[i].parent = ht[i].lchild = ht[i].rchild = -1; // 所有结点相关域置初值为-1
    }
    for (i = n0; i < 2 * n0 - 1; i++) // 构造哈夫曼树的n0-1个分支结点
    {
        min1 = min2 = 32767;
        lnode = rnode = -1; // lnode,rnode分别指向最小的两个权值min1,min2
        for (k = 0; k <= i - 1; k++)
        {
            if (ht[k].parent == -1) // 若当前节点还未被使用
            {
                // 找到最小的两个权值
                if (ht[k].weight < min1)
                {
                    min2 = min1;
                    rnode = lnode;
                    min1 = ht[k].weight;
                    lnode = k;
                }
                else if (ht[k].weight < min2)
                {
                    min2 = ht[k].weight;
                    rnode = k;
                }
            }
        }
        ht[i].weight = ht[lnode].weight + ht[rnode].weight;
        ht[i].lchild = lnode;
        ht[i].rchild = rnode;
        ht[lnode].parent = ht[rnode].parent = i;
    }
}

void CreateHCode(HTNode ht[], HCode hcd[], int n0) // 哈夫曼树对应的哈夫曼编码（左分支设为0，右分支设为1）
{
    int i, f, c;
    HCode hc;
    for (i = 0; i < n0; i++)
    {
        hc.start = n0;
        c = i;
        f = ht[i].parent;
        // 倒序存入哈夫曼编码
        while (f != -1)
        {
            if (ht[f].lchild == c) // 当前结点是双亲结点的左孩子
                hc.cd[hc.start--] = '0';
            else // 当前结点是双亲结点的右孩子
                hc.cd[hc.start--] = '1';
            c = f;
            f = ht[f].parent;
        }
        hc.start++; // start指向哈夫曼编码最开始的字符
        hcd[i] = hc;
    }
}

/*关于解码算法
1.设置指针p指向哈夫曼树的根结点
2.对于接收的编码
如果bit = 0, 则p = p->left
如果bit = 1, 则p = p->right
3.判断p是否为叶结点
如果是, 输出该叶结点对应字符
不是, 则继续读下一位
4.重复, 直到结束*/
void Decoding(HTNode ht[], int n0, char bit[], int length)
{
    int i = 0, p, root = 2 * n0 - 2; // 根结点下标
    while (i < length)
    {
        p = root;
        // 从根走到叶结点
        while (!(ht[p].lchild == -1 && ht[p].rchild == -1))
        {
            char ch = bit[i++];
            if (ch == '0')
                p = ht[p].lchild;
            else if (ch == '1')
                p = ht[p].rchild;
        }
        printf("%c", ht[p].date);
    }
    printf("\n");
}

int main()
{
    int i, n = 5;
    double weight[] = {2, 4, 8, 12, 13};
    char code[] = {'A', 'B', 'C', 'D', 'E'};
    char bit[N];

    HTNode ht[2 * n - 1];
    HCode hcd[n];

    // 初始化叶结点
    for (i = 0; i < n; i++)
    {
        ht[i].date = code[i];
        ht[i].weight = weight[i];
    }

    CreateHT(ht, n);
    CreateHCode(ht, hcd, n);

    printf("%-4s %-4s %-6s %-6s %-6s %-6s\n", "下标", "字符", "权重", "父结点", "左孩子", "右孩子");
    for (i = 0; i < 2 * n - 1; i++)
    {
        printf("%-4d %-4c %-6.0f %-6d %-6d %-6d\n",
               i,
               ht[i].date ? ht[i].date : '-',
               ht[i].weight,
               ht[i].parent,
               ht[i].lchild,
               ht[i].rchild);
    }

    printf("各字符的哈夫曼编码:\n");
    for (i = 0; i < n; i++)
    {
        printf("%c: ", ht[i].date);
        for (int j = hcd[i].start; j <= n; j++)
            printf("%c", hcd[i].cd[j]);
        printf("\n");
    }

    printf("请输入密文: ");
    scanf("%s", bit);
    printf("解码结果: ");
    Decoding(ht, n, bit, strlen(bit));

    return 0;
}