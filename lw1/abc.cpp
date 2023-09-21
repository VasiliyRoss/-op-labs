#include <cstdio>

int main()
{
    int a = 0;
    int b = 0;
    int c = 0;
    std::printf("Введите число a:");
    std::scanf("%d", &a);

    std::printf("\nВведите число b:");
    std::scanf("%d", &b);

    std::printf("\nВведите число c:");
    std::scanf("%d", &c);

    std::printf("\na+b+c=%d\n", a+b+c);
}