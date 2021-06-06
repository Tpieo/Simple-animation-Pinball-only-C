#include <stdio.h>
#include <math.h>
#include <Windows.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

#define HIGH 27
#define WIDTH 100

int cnt = 0;
struct BALL
{
    int wX;       //在二维数组中，球在x方向的实际显示位置（整数）
    int wY;       //在二维数组中，球在y方向的实际显示位置（整数）
    int X;        //球在x方向的精确位置（实数）
    int Y;        //球在y方向的精确位置（实数）
    int dX;       //球在x方向的速度（实数）
    int dY;       //球在y方向的速度（实数）
};

int main()
{
    srand(time(NULL));
    printf("请输入球的个数：");
    int num; //球的个数
    scanf("%d", &num);

    //图像初始化
    char pic[HIGH][WIDTH] = {0};
    int i, j;
    for (i = 0; i < HIGH; i++)
    {
        for (j = 0; j < WIDTH; j++)
        {
            pic[i][j] = ' ';
        }
    }
    for (i = 0; i < HIGH; i++)
    {
        pic[i][WIDTH - 1] = '\n';
        pic[i][0] = '|';
        pic[i][WIDTH - 2] = '|';
    }
    for (i = 0; i < WIDTH - 1; i++)
    {
        pic[0][i] = '*';
        pic[HIGH - 1][i] = '*';
    }
    pic[HIGH - 1][WIDTH - 1] = '\0';

    //初始化球
    struct BALL *ball = (struct BALL *)malloc(sizeof(struct BALL) * num);
    for (int i = 0; i < num; i++)
    {
        (ball + i)->X = rand() % (HIGH - 3) + 1;
        (ball + i)->Y = rand() % (WIDTH - 3) + 1;
        (ball + i)->dX = rand() % 2 + 1;
        (ball + i)->dY = rand() % 2 + 1;
    }

    while (1)
    {
        //打印
        for (int i = 0; i < num; i++)
            pic[(ball + i)->X][(ball + i)->Y] = 'o';
        printf("%s", pic);
        for (int i = 0; i < num; i++)
            pic[(ball + i)->X][(ball + i)->Y] = ' ';
        for (int i = 0; i < num; i++)
        {
            (ball + i)->X += (ball + i)->dX;
            (ball + i)->Y += (ball + i)->dY;
        }

        //边界检测
        for (int i = 0; i < num; i++)
        {
            if ((ball + i)->X >= HIGH - 3)
            {
                (ball + i)->dX = -(ball + i)->dX;
                cnt++;
                putchar('\7');
            }
            if ((ball + i)->X <= 2)
                (ball + i)->dX = -(ball + i)->dX;
            if ((ball + i)->Y >= WIDTH - 5)
                (ball + i)->dY = -(ball + i)->dY;
            if ((ball + i)->Y <= 2)
                (ball + i)->dY = -(ball + i)->dY;
        }
        printf("\n落地次数%d", cnt);

        //碰撞检测
        for (int i = 0; i < num; i++)
        {
            for (int j = i + 1; j < num; j++)
            {
                double dist = sqrt(pow((ball + i)->X - (ball + j)->X, 2) + pow((ball + i)->Y - ((ball + j)->Y), 2));
                if (dist <= 1)
                {
                    (ball + i)->dX = -(ball + i)->dX;
                    (ball + i)->dY = -(ball + i)->dY;
                    (ball + j)->dX = -(ball + j)->dX;
                    (ball + j)->dY = -(ball + j)->dY;
                }
            }
        }

        Sleep(3);
        system("cls");
    }

    return 0;
}