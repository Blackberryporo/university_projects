#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int get_int(int *param)
{
    char buffer[16] = {0};
    char *p;

    fgets(buffer, 16, stdin);
    if (buffer == NULL)
    {
        return 1;
    }

    for(p = buffer; *p; ++p)
    {
        if(*p != '\n' && (*p < '0' || *p > '9'))
        {
            return 2;
        }
    }
    *param = atoi(buffer);

    if (*param == 0)
    {
        return 3;
    }

    return 0;
}

int main()
{
    const int N = 10;
    int array[N];
    int i;

    srand(time(0)); /*initialization of the seed of the random number generator */

    printf("First task\nRandom generated array of %d integers:\n", N);

    for (i = 0; i < N; ++i)
    {
        array[i] = rand() % 4;
        printf("%d ", array[i]);
    }

    int max = 0, max_id = 0;
    for (i = 0; i < N; ++i)
    {
        if (array[i] > max)
        {
            max = array[i];
            max_id = i;
        }
    }
    printf("Max element: array[%d] = %d\n", max_id, max);

    printf("Finding the sum of the elements between the first two positive elements of the array:\n");
    int sum = 0;
    int found = 0;
    for(i = 0; i < N; ++i)
    {
        if(array[i] > 0)
        {
            printf("First positive element at %d\n", i);
            found++;
            i++;
            while(array[i] <= 0 && i < N)
            {
                sum += array[i];
                i++;
            }
            if(i < N)
            {
                printf("Second positive element at %d\n", i);
                found++;
            }
            break;
        }
    }

    if(found == 2)
    {
        printf("Sum of elements between them: %d\n", sum);
    }
    else
    {
        printf("Couldn't compute the sum of elements between the first and the second positive numbers."
                "Perhaps there was no valid selection\n");
    }

    printf("Sorting array so that all zero values will go to the end of the array by swapping:\n");
    int j;
    for(i = 0; i < N-1; ++i)
    {
        if(array[i] == 0)
        {
            printf("Detected zero at %d, trying to swap...\n", i);
            for(j = N - 1; j > i ; --j)
            {
                if(array[j] != 0)
                {
                    printf("Found non-zero value at %d, swapping.\n", j);
                    int temp = array[j];
                    array[j] = 0;
                    array[i] = temp;
                    break;
                }
            }
        }
    }

    printf("Sorted array:\n");
    for(i = 0; i < N; ++i)
    {
        printf("%d ", array[i]);
    }

    printf("\nSecond task:\nPlease provide the n for n x n matrix (positive integer):\n");
    unsigned int n;
    int result;
    do
    {
        result = get_int(&n);
        if (result == 1)
        {
            printf("Wrong input, try again\n");
        }
        else if (result == 2)
        {
            printf("Not integer or negative value, try again\n");
        }
        else if (result == 3)
        {
            printf("Not positive value, try again\n");
        }
    }
    while (result != 0);
    /*creating a pointer to pointers and then immediately allocating data for n pointers*/
    float **matrix = (float**)malloc(sizeof(float*) * n);
    float **new_matrix = (float**)malloc(sizeof(float*) * n);

    /*allocating n floats for every pointer in the pointer array*/
    for(i = 0; i < n; ++i) matrix[i] = (float*)malloc(sizeof(float) * n);
    for(i = 0; i < n; ++i) new_matrix[i] = (float*)malloc(sizeof(float) * n);

    printf("Random generated matrix %d x %d:\n", n, n);
    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            (matrix[i])[j] = (float)(rand() % 30 - 15);
            printf("%5.1f\t", (matrix[i])[j]);
        }
        printf("\n");
    }

    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            float sum = 0.0f;
            int count = 0;
            if (i > 0)
            {
                sum += (matrix[i-1])[j];
                count++;
            }
            if (i < n - 1)
            {
                sum += (matrix[i+1])[j];
                count++;
            }
            if (j > 0)
            {
                sum += (matrix[i])[j-1];
                count++;
            }
            if (j < n - 1)
            {
                sum += (matrix[i])[j+1];
                count++;
            }

            sum /= count;

            (new_matrix[i])[j] = sum;
        }
    }

    printf("Resulting matrix where values are arithmetical means of all nearest positions (except diagonal) in original matrix:\n");
    for(i = 0; i < n; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            printf("%5.1f\t", (new_matrix[i])[j]);
        }
        free(matrix[i]);
        free(new_matrix[i]);
        printf("\n");
    }
    free(matrix);
    free(new_matrix);

    return 0;
}
