#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <float.h>
#include <string.h>
#define floatsize 50

double Function1(double x)
{
    double y = x/(pow(x,4)+4);
    return y;
}

double Function2(double x)
{
    double y = sin(3*x/2)+0.5;
    return y;
}

double Function3(double x)
{
    double y = 4*pow(x,3) - 3*pow(x,2) + 1;
    return y;
}

int GetInt(char* buf)
{
    bool notspace = false;
    bool afterspace = false;
    int i = 0;
    memset(buf, 0, floatsize);

    if (fgets(buf, sizeof(char)*floatsize, stdin) == NULL)
    {
        return 0;
    }

    if(buf[i] != '\n')
        while(buf[i] != '\n')
        {
            if (!notspace && !afterspace)
            {
                if (buf[i] == ' ')
                {
                    i++;
                    continue;
                }
                else if (buf[i]>'0' && buf[i]<'2')
                {
                    notspace=true;
                    i++;
                    continue;
                }
                else return 0;
            }
            else if (notspace)
            {
                if (buf[i] > '0' && buf[i] < '2')
                {
                    afterspace = true;
                    notspace = false;
                    i++;
                    continue;
                }
                else if (buf[i] == ' ')
                {
                    afterspace = true;
                    notspace = false;
                    i++;
                    continue;
                }
                else return 0;
            }
            else if (afterspace)
            {
                if (buf[i] == ' ')
                {
                    i++;
                    continue;
                }
                else return 0;
            }
        }
    else
    {
        return 0;
    }

    return atoi(buf);
}

int Choose(char* buf)
{
    bool notspace = false;
    bool afterspace = false;
    int i = 0;

    memset(buf,0,floatsize);
    printf("Choose the function you want to integrate:\n"
           "1.x/(x^4+4)\n"
           "2.sin(3*x/2)+1/2\n"
           "3.4x^3-3x^2+1\n");

    if (fgets(buf, sizeof(char)*floatsize, stdin)==NULL)
    {
        printf("Invalid input, try again\n");
        return 0;
    }

    if (buf[i] != '\n')
        while (buf[i] != '\n')
        {
            if (!notspace && !afterspace)
            {
                    if (buf[i] == ' ')
                    {
                        i++;
                        continue;
                    }
                    else if (buf[i] > '0' && buf[i] < '4')
                    {
                        notspace = true;
                        i++;
                        continue;
                    }
                    else
                    {
                        printf("Invalid input, try again\n");
                        return 0;
                    }
            }
            else if (notspace)
            {
                if (buf[i] > '0' && buf[i] < '4')
                {
                    afterspace=true;
                    notspace=false;
                    i++;
                    continue;
                }
                else if (buf[i]==' ')
                {
                    afterspace=true;
                    notspace=false;
                    i++;
                    continue;
                }
                else
                {
                    printf("Invalid input, try again\n");
                    return 0;
                }
            }
            else if (afterspace)
            {
                if (buf[i] == ' ')
                {
                    i++;
                    continue;
                }
                else
                {
                    printf("Invalid input, try again\n");
                    return 0;
                }
            }
        }
    else
    {
        printf("Invalid input, try again\n");
        return 0;
    }

    return atoi(buf);
}

bool GetDouble(char* buf)
{
    bool point = false;
    bool notspace = false;
    bool afterspace = false;
    int i = 0;

    memset(buf, 0, floatsize);
    if (fgets(buf, sizeof(char)*floatsize, stdin) == NULL)
    {
        printf("Invalid input, try again\n");
        return false;
    }

    if(buf[i] != '\n')
        while(buf[i] != '\n')
        {
            if (!notspace && !afterspace)
            {
                    if (buf[i] == ' ')
                    {
                        i++;
                        continue;
                    }
                    else if (buf[i] >= '0' && buf[i] <= '9')
                    {
                        notspace = true;
                        i++;
                        continue;
                    }
                    else if (buf[i] == '-' && buf[i+1] >= '0' && buf[i+1] <= '9')
                    {
                        notspace = true;
                        i++;
                        continue;
                    }
                    else
                    {
                        printf("Invalid input, try again\n");
                        return false;
                    }
            }
            else if (notspace)
            {
                if (buf[i] >= '0' && buf[i] <= '9')
                {
                    i++;
                    continue;
                }
                else if (buf[i] == ' ')
                {
                    afterspace = true;
                    notspace = false;
                    i++;
                    continue;
                }
                else if (buf[i] == '.' && point == false)
                {
                    point = true;
                    i++;
                    continue;
                }
                else if (buf[i] == ',' && point == false)
                {
                    buf[i] = '.';
                    point = true;
                    i++;
                    continue;
                }
                else
                {
                    printf("Invalid input, try again\n");
                    return false;
                }
            }
            else if (afterspace)
            {
                if (buf[i] == ' ')
                {
                    i++;
                    continue;
                }
                else
                {
                    printf("Invalid input, try again\n");
                    return false;
                }
            }
        }
    else
    {
        printf("Invalid input, try again\n");
        return false;
    }
    return true;
}

double Method(double (*pointer2Func)(double ), double eps, double uplim, double lowlim, int *n1, double *Integral_1)
{
    int n0 = 1;
    double Integral_0 = 0;
    double step = 0;
    *n1 = n0;
    *Integral_1 = 0;
    step = (uplim-lowlim)/(2*n0);

    for (int i = 1; i < 2*n0; i++)
        if (i%2 != 0)
        {
            Integral_0 += 4*(*pointer2Func)(lowlim + i*step);
        }
        else
        {
            Integral_0 += 2*(*pointer2Func)(lowlim + i*step);
        }

    Integral_0 += (*pointer2Func)(lowlim)+(*pointer2Func)(lowlim + 2*n0*step);
    Integral_0 *= step/3;
    *Integral_1 = Integral_0;

    do
    {
        Integral_0 = *Integral_1;
        *Integral_1 = 0;
        n0 = *n1;
        *n1 = 2*n0;
        step = (uplim - lowlim)/(2*(*n1));
        for (int i = 1; i < 2*(*n1); i++)
        if (i%2 != 0)
        {
            *Integral_1 += 4*(*pointer2Func)(lowlim + i*step);
        }
        else
        {
            *Integral_1 += 2*(*pointer2Func)(lowlim + i*step);
        }
        *Integral_1 += (*pointer2Func)(lowlim) + (*pointer2Func)(lowlim + 2*(*n1)*step);
        *Integral_1 *= step/3;
    }
    while ((fabs(*Integral_1 - Integral_0))/15 > fabs(eps));

    return ((fabs(*Integral_1 - Integral_0))/15);
}

int main()
{
    while(1)
    {
        int n1 = 0;
        double Integral_1 = 0;
        char buf[floatsize] = {0};
        int menu = 0;
        bool minus = false;
        bool flag = false;
        double uplim = 0;
        double lowlim = 0;
        double swap = 0;
        double eps = 0;
        double (*pointer2Func)(double ) = NULL;

        fflush(stdin);
        do
        {
            menu = Choose(buf);
        }
        while (menu == 0);

        if (menu==1)
        {
            pointer2Func = &Function1;
        }
        else if (menu==2)
        {
            pointer2Func = &Function2;
        }
        else
        {
            pointer2Func = &Function3;
        }

        printf("Enter the upper limit:\n");
        do
        {
            flag = GetDouble(buf);
        }
        while (flag == false);

        uplim = atof(buf);
        printf("Enter the lower limit:\n");
        do
        {
            flag = GetDouble(buf);
        }
        while (flag == false);

        lowlim = atof(buf);
        if (lowlim > uplim)
        {
            minus = true;
            swap = lowlim;
            lowlim = uplim;
            uplim = swap;
        }

        printf("Enter the accuracy:\n");
        do
        {
            flag = GetDouble(buf);
            if (flag == true && atof(buf) == 0)
            {
                printf("Invalid input, try again\n");
            }
        }
        while (flag == false || atof(buf) == 0);

        eps = atof(buf);
        printf("Error = %f\n", Method(pointer2Func, eps, uplim, lowlim, &n1, &Integral_1));

        if (minus)
        {
            Integral_1 = -(Integral_1);
        }

        printf("Number of parts = %i\n", n1);
        printf("Integral = %f\n", Integral_1);
        printf("Press 1 to continue or any other key to exit:\n");
        if (GetInt(buf) != 1) break;
    }
    return 0;
}
