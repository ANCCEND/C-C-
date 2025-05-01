#include <stdio.h>

void generateSpiralMatrix(int n, int matrix[n][n]) {
    int top = 0, bottom = n - 1; // 上、下边界
    int left = 0, right = n - 1; // 左、右边界
    int num = 1; // 填充的数字

    while (num <= n * n) {
        // 从左到右填充
        for (int i = left; i <= right; i++) {
            matrix[top][i] = num++;
        }
        top++; // 收缩上边界

        // 从上到下填充
        for (int i = top; i <= bottom; i++) {
            matrix[i][right] = num++;
        }
        right--; // 收缩右边界

        // 从右到左填充
        for (int i = right; i >= left; i--) {
            matrix[bottom][i] = num++;
        }
        bottom--; // 收缩下边界

        // 从下到上填充
        for (int i = bottom; i >= top; i--) {
            matrix[i][left] = num++;
        }
        left++; // 收缩左边界
    }
}

void printMatrix(int n, int matrix[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%3d ", matrix[i][j]); // 格式化输出，保持对齐
        }
        printf("\n");
    }
}

int main() {
    int n;
    printf("请输入方阵阶数 n: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("阶数必须为正整数。\n");
        return 1;
    }

    int matrix[n][n];
    generateSpiralMatrix(n, matrix);
    printMatrix(n, matrix);

    return 0;
}