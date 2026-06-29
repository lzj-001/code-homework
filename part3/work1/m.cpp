/*
1：定义串的静态顺序存储结构
   包括存储串的数组及串长
2：串的简单模式匹配算法实现；
  在匹配过程中，若匹配失败时，主串回溯到上次起点的下一个位置，子串从头开始；
3：在主函数中调用模式匹配算法,对子串T=”abcac”和主串S=”ababcabcacbab”进行模式匹配并返回相应的结果
*/
#include <stdio.h>
#define MAXSIZE 100

typedef struct Sqstring
{
    char data[MAXSIZE];
    int length;
} Sqstring;

int BF(Sqstring s, Sqstring t)
{
    int i = 0, j = 0, index;
    while (i < s.length && j < t.length)
    {
        if (s.data[i] == t.data[j])
        {
            i++;
            j++;
        }
        else
        {
            i = i - j + 1; // i-j使主串返回最初与子串第一个字符配对的位置，而后+1使主串后移一位，开始下一次比较
            j = 0;
        }
    }
    if (j >= t.length) // 匹配成功
    {
        index = i - t.length; // 计入主串中第一次出现的子串的位置
        printf("匹配成功，主串中存在子串，索引位置为%d", index);
        return index;
    }
    else // 匹配失败
    {
        printf("i:%d,j:%d", i, j);
        printf("匹配失败");
        return -1;
    }
}

int main()
{
    Sqstring s, t;
    s.length = 0;
    t.length = 0;
    int l1, l2;

    printf("S_length: ");
    scanf("%d", &l1);
    getchar();

    printf("S: ");
    for (int i = 0; i < l1; i++)
    {
        scanf("%c", &s.data[i]);
        s.length++;
    }
    getchar();

    printf("T_length: ");
    scanf("%d", &l2);
    getchar();

    printf("T: ");
    for (int i = 0; i < l2; i++)
    {
        scanf("%c", &t.data[i]);
        t.length++;
    }
    getchar();

    BF(s, t);

    return 0;
}