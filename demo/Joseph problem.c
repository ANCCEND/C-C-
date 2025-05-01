#include <stdio.h>

// 约瑟夫问题
int main(void)
{
    int M, N;
    scanf("%d%d", &M, &N);
    int a[M];
    int i, j, k;
    for (i = 0; i < M; i++)
        a[i] = i + 1;

    for (i = M, j = 0; i > 1; i--)// 直到剩下一个元素
    { 
        for (k = 1; k <= N; k++) // 每次跳N步
        {
            j++;
            if (j > M)
                j = 1; // 如果超出范围，回到0
            while (a[j - 1] == 0)// 如果这个位置已经是0，继续跳
            { 
                j++;
                if (j > M)
                    j = 1; // 环形跳
            }
        }
        
        a[j - 1] = 0;// 将跳到的位置标记为0
    }

    for (i = 0; i < M; i++)
    {
        if (a[i] != 0)
        {
            printf("%d\n", a[i]);
            break;
        }
    }

    return 0;
}
