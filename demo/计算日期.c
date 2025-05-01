#include <stdio.h>

typedef struct
{
    int year;
    int month;
    int day;
} date;

int if_leapyear(int year);
void NumofDay(int const *month, date a);

int main(void)
{
    date a;
    const int month1[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    const int month2[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    scanf("%d%d%d", &a.year, &a.month, &a.day);
    if (if_leapyear(a.year))
        NumofDay(month2, a);
    else if (a.month > 12||!if_leapyear(a.year) && (a.month == 2 && a.day == 29))
        printf("不存在这样的日期");
    else
        NumofDay(month1, a);

    return 0;
}

int if_leapyear(int year)
{
    if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0))
    {
        return 1;
    }
    else
        return 0;
}

void NumofDay(int const *month, date a)
{
    int num = 0;
    if (a.month == 1)
    {
        num = a.day;
    }
    else if (a.month > 1)
    {
        for (int i = 1; i < a.month; i++)
        {
            num += month[i - 1];
        }
        num += a.day;
    }
    printf("%d", num);
}