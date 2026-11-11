#include <stdio.h>

#define N 7
#define M 8

int main()
{
    float arr[N][M];
    float x;
    int k, i, j;
    int match_count = 0;

    printf("Вкажіть шукане дійсне число x: ");
    scanf("%f", &x);

    for (i = 0; i < N; i++)
    {
        printf("Заповніть %d-й рядок (%d чисел за незменшенням): ", i + 1, M);
        for (j = 0; j < M; j++)
        {
            scanf("%f", &arr[i][j]);
        }
    }

    printf("\nОтримана матриця має вигляд:\n");
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            printf("%7.2f ", arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    for (k = 0; k < N; k++)
    {
        int l = 0;
        int r = M - 1;
        int found_I = -1;

        while (l <= r)
        {
            int I = l + (r - l) / 2; 

            if (arr[k][I] == x)
            {
                found_I = I; 
                r = I - 1; 
            }
            else if (arr[k][I] < x)
            {
                l = I + 1;
            }
            else
            {
                r = I - 1;
            }
        }

        if (found_I != -1)
        {
            printf("Елемент присутній за координатами: [%d][%d]\n", k, found_I);
            match_count++;
        }
    }

    if (match_count == 0)
    {
        printf("Шукане число відсутнє у масиві.\n");
    }

    return 0;
}