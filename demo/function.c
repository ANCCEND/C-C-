// 组合数的计算
int C(int m, int i) {
    int x = 1;
    if (i - m < i / 2.0) m = i - m;
    for (int n = i; n > i - m; n--)
        x *= n;
    while (m > 1) {
        x /= m;
        m--;
    }
    return x;
}

// 打印n行的杨辉三角
void triangle(int n) {
    int x, space, i;
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        for (space = 1; space <= n - i; space++)
            printf("  ");
        for (int m = 0; m <= i; m++) {
            if (m == 0 || m == i) x = 1;
            else if (m < i) x = C(m, i);
            printf("%4d", x);

        }
        printf("\n");
    }
}

//素数(prime)
int isprime(int m) {
    if (m < 1) return 0;
    for (int i = 2; i * i <= m; i++) {
        if (!(m % i)) return 0;
    }

    return 1;
}

//检测m,n的各位数字是否相同（不足五位数的在前面添加0表示一位数）
int why(int m, int n) {
    int str[10] = { 0 };
    int i;
    for (i = 0; i <= 4; i++) {
        if (m != 0) {
            str[i] = m % 10;
            m /= 10;
        }
    }
    for (; i <= 9; i++) {
        if (n != 0) {
            str[i] = n % 10;
            n /= 10;
        }
    }
    for (i = 0; i <= 9; i++) {
        for (int x = i + 1; x <= 9; x++) {
            if (str[i] != str[x]) continue;
            else return 0;
        }
    }
    return 1;
}

//斐波那契数列前n项和(记忆递归)

/*long fabo[255];全局变量
long fabonacci(int n) {
    if (n <= 2) return 1;
    if (fabo[n] != 0) return fabo[n];
    fabo[n] = fabonacci(n - 1) + fabonacci(n - 2);
    return fabo[n];
}
*/

//x的n次方
double mulx(double x, int n)
{
    int i;
    double z = 1.0;
    for (i = 0; i <= n; i++)
    {
        z *= x;
    }
    return z;
}

//n的阶乘
long fac(int n)
{
    int s = 1;
    if (n == 0) return s;
    else {
        for (int i = 1; i <= n; i++) {
            s *= i;
        }
    }
    return s;
}

//最大公约数(递归并展示辗转相除过程)
int gcd(int x, int y) {
    int m;
    if (y) {
        m = x % y;
        printf("%d %d", x, y);
        return gcd(y, m);
    }
    else {
        printf("%d %d", x, y);
        return x;
    }
}

//数组从小到大冒泡排列
void selectSort(int arr[], int n) {
    int i, m, x;
    while (n > 1) {
        for (i = 0; i < n - 1; i++) {
            if (arr[i] > arr[i + 1]) {
                m = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = m;
            }
        }
        n--;
    }
}

//输入n个整数到数组u中，再输入正整数k(0< k < n )，k将数组u的n个元素划分为u[0]，……，u[k-1]和u[k]，……，u[n-1]两段，
// 将两段元素交换位置但仍然存放在数组u中，输出重新排列后的数组元素。

/*示例如下：
假设n = 7，k = 3；
数组元素u[0]，……，u[6]依次为1, 2, 3, 4, 5, 6, 7；
则被交换的两段元素是：u[0]，……，u[6]交换的结果是4, 5, 6, 7, 1, 2, 3。*/

void move(int arr[], int n, int k) {
    int m, s;
    s = k;
    if (k <= 0 || k >= n - 1) return;
    else if (k > n / 2.0) {
        for (int i = k; i < n; i++) {
            m = arr[i];
            for (int j = s - 1; j >= i - k; j--) {
                arr[j + 1] = arr[j];
            }
            arr[i - k] = m;
            s++;
        }
    }
    else {
        for (int i = k - 1; i >= 0; i--) {
            m = arr[i];
            for (int j = s; j <= n - 1 - (k - 1 - i); j++) {
                arr[j - 1] = arr[j];
            }
            arr[n - 1 - (k - 1 - i)] = m;
            s--;
        }
    }

}

//使用数组计数字符串中各字符出现的次数（空格和标点等算为others）（getchar输入）
void count(char ch, int num[]) {
    if (ch >= '0' && ch <= '9')
        num[ch]++;
    else if (ch >= 'a' && ch <= 'z') {
        num[ch - 'a' + 10]++;
    }
    else if (ch >= 'A' && ch <= 'Z')
        num[ch - 'A' + 10]++;
    else num[36]++;
}

void printnum(int num[]) {
    for (int i = 0; i < 37; i++) {
        if (i < 10) {
            if (num[i] != 0)
                printf("%d:%d\n", i, num[i]);
        }
        else if (i >= 10) {
            if (num[i] != 0)
                printf("%c:%d\n", i - 10 + 'A', num[i]);
        }
    }
}

//回文判断
int isPalindrome(char arr[], int len)
{
    if (len >= 0 && len <= strlen(arr) && isPalindrome(arr, len - 1))
    {
        if (arr[len] == arr[strlen(arr) - len - 1])
            return 1;
        else
            return 0;
    }
    else if (len == -1)
        return 1;
    else
        return 0;
}

//从第n个字符后插入文字
void strnins(char t[], char s[], int n)
{
    int j, m, i, k;
    k=strlen(t);
    m=strlen(s);
    for (int i = k; i >= n; i--) {
        t[i + m] = t[i];
    }
    for (int i = 0; i < m; i++) {
        t[n + i] = s[i];
    }
    
    puts(t);//fputs

}