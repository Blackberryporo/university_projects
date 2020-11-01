#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <float.h>
#include <string.h>
#include <math.h>
#include <limits>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


#define floatsize 50
#define _USE_MATH_DEFINES

using namespace std;

static const int SCREEN_HEIGHT = 600;
static const int SCREEN_WEIDTH = 600;
static const int CENTER_X = SCREEN_WEIDTH / 2;
static const int CENTER_y = SCREEN_HEIGHT / 2;

SDL_Renderer *renderer = NULL;
SDL_Window *window = NULL;
SDL_Surface *surface = NULL;
SDL_Surface* gCurrentSurface = NULL;

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

    fflush(stdin);
    memset(buf, 0, floatsize);
    if (fgets(buf, sizeof(char)*floatsize, stdin) == NULL)
    {
        printf("Invalid input, try again\n");
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

double Function1(double x)
{
    double y = cos(x);
    return y;
}

double Function2(double x)
{
    double y = log(x);
    return y;
}

double Function3(double x)
{
    double y = pow(x, 2);
    return y;
}

double Multiply(double x, int n)
{
    double mul = 1;
    for (int i = 0; i < n; i++)
    {
        if (x >= 0)
        {
            mul *= x - i;
        }
        else
        {
            mul *= x + i;
        }
    }

    return mul;
}

void DrawPoint(SDL_Renderer *renderer, int x, int y)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderDrawLine(renderer, x, y, x-2, y-2);
    SDL_RenderDrawLine(renderer, x, y, x-2, y+2);
    SDL_RenderDrawLine(renderer, x, y, x+2, y-2);
    SDL_RenderDrawLine(renderer, x, y, x+2, y+2);
}

void DrawPoint0(SDL_Renderer *renderer,int x, int y)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0);
    SDL_RenderDrawLine(renderer, x, y, x-3, y-3);
    SDL_RenderDrawLine(renderer, x, y, x-3, y+3);
    SDL_RenderDrawLine(renderer, x, y, x+3, y-3);
    SDL_RenderDrawLine(renderer, x, y, x+3, y+3);
}

void DrawFunc(SDL_Renderer *renderer, double (*Func)(int,double,double,double,double*,double*,double,double**),int n,
    double h,double middle,double x_get,double* x,double *y,double y_get,double** dy, double scale,double x0,double xn)
{
    int count = 0;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Point *points = (SDL_Point *)malloc(sizeof(SDL_Point) * scale * 10 * SCREEN_WEIDTH);
    if (x0 > 0)
    {
        x_get = x0;
    }
    else
    {
        x_get = 0;
    }

    if (xn > 0)
    {
        for(int i = 0; i < SCREEN_WEIDTH * scale* 10; i++)
        {
            points[i].x = CENTER_X + x_get * scale;
            points[i].y = CENTER_y - (*Func)(n,h,middle,x_get,x,y,y_get,dy) * scale;
            if (x_get >= xn) break;
            x_get += 0.01;
            count++;
        }
    }

    SDL_RenderDrawLines(renderer, points, count);
    free(points);
    points = (SDL_Point *)malloc(sizeof(SDL_Point) * scale * 10 * SCREEN_WEIDTH);
    if (xn < 0)
    {
        x_get = xn;
    }
    else
    {
        x_get = 0;
    }
    count = 0;
    if (x0 < 0)
    {
        for(int i = 0; i < SCREEN_WEIDTH * scale*10; i++)
        {
            points[i].x = CENTER_X - x_get * scale;
            points[i].y = CENTER_y - (*Func)(n,h,middle,-x_get,x,y,y_get,dy) * scale;
            if (-x_get <= x0) break;
            x_get += 0.01;
            count++;
        }
    }
    SDL_RenderDrawLines(renderer, points, count);
    free(points);
}

void DrawFunc0(SDL_Renderer *renderer, double (*Func)(double), double scale)
{
    double p = 0;
    SDL_Point *points = (SDL_Point *)malloc(sizeof(SDL_Point) * scale * 100  * SCREEN_WEIDTH);
    SDL_SetRenderDrawColor(renderer, 0, 180, 0, 255);

    for(int i = 0; i < SCREEN_WEIDTH * scale * 100; i++)
    {
        points[i].x = CENTER_X + p * scale;
        points[i].y = CENTER_y - (*Func)(p) * scale;
        p += 0.0001;
    }
    SDL_RenderDrawLines(renderer, points, SCREEN_WEIDTH * scale * 100);
    free(points);

    points = (SDL_Point *)malloc(sizeof(SDL_Point) * scale * 100 * SCREEN_WEIDTH);
    p = 0;

    for(int i = 0; i < SCREEN_WEIDTH * scale * 100; i++)
    {
        points[i].x = CENTER_X - p * scale;
        points[i].y = CENTER_y - (*Func)(-p) * scale;
        p += 0.0001;
    }
    SDL_RenderDrawLines(renderer, points, SCREEN_WEIDTH * scale * 100);
    free(points);
}

void DrawAxes(SDL_Renderer *renderer, int scale)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawLine(renderer, CENTER_X, 0, CENTER_X, SCREEN_HEIGHT);
    SDL_RenderDrawLine(renderer, 0, CENTER_y, SCREEN_WEIDTH, CENTER_y);

    SDL_RenderDrawLine(renderer, CENTER_X, 0, CENTER_X - 5, 5);
    SDL_RenderDrawLine(renderer, CENTER_X, 0, CENTER_X + 5, 5);

    SDL_RenderDrawLine(renderer, SCREEN_WEIDTH, CENTER_y, SCREEN_WEIDTH - 5, CENTER_y - 5);
    SDL_RenderDrawLine(renderer, SCREEN_WEIDTH, CENTER_y, SCREEN_WEIDTH - 5, CENTER_y + 5);

    for (int i = 0; i < SCREEN_WEIDTH; i += scale)
    {
        SDL_RenderDrawLine(renderer, CENTER_X+i, CENTER_y, CENTER_X+i, CENTER_y + 1);
        SDL_RenderDrawLine(renderer, CENTER_X+i, CENTER_y, CENTER_X+i, CENTER_y - 1);
        SDL_RenderDrawLine(renderer, CENTER_X-i, CENTER_y, CENTER_X-i, CENTER_y + 1);
        SDL_RenderDrawLine(renderer, CENTER_X-i, CENTER_y, CENTER_X-i, CENTER_y - 1);
        SDL_RenderDrawLine(renderer, CENTER_X, CENTER_y+i, CENTER_X + 1, CENTER_y + i);
        SDL_RenderDrawLine(renderer, CENTER_X, CENTER_y+i, CENTER_X - 1, CENTER_y + i);
        SDL_RenderDrawLine(renderer, CENTER_X, CENTER_y-i, CENTER_X + 1, CENTER_y - i);
        SDL_RenderDrawLine(renderer, CENTER_X, CENTER_y-i, CENTER_X - 1, CENTER_y - i);
    }
}
void Difference(int n, double *y, double** dy)
{
    for (int j = 0; j < n-1; j++)
    {
        dy[0][j] = y[j+1] - y[j];
    }

    for (int i = 1; i < n-1; i++)
        for (int j = 0;j < n-1-i; j++)
        {
            dy[i][j] = dy[i-1][j+1] - dy[i-1][j];
        }
}

double NewtonPolynomial(int n, double h, double middle, double x_get, double *x, double *y, double y_get, double **dy)
{
    int i0 = 0;
    double t = 0;
    double min = fabs(x_get - x[0]);
    y_get = 0;

    for (int i = 0; i < n; i++)
        if (x_get == x[i])
        {
            return y[i];
        }

    for (int i = 0; i < n; i++)
        if (fabs(x_get - x[i]) < min)
        {
            min = fabs(x_get - x[i]);
            i0 = i;
        }

    if (x_get <= middle)
    {
        t = (x_get - x[i0])/h;
        y_get = y[i0];
        for (int i = 0; i < n-i0-1; i++)
        {
            y_get += dy[i][i0] * Multiply(t, i+1)/Multiply(i+1, i+1);
        }
    }
    else
    {
        t = (x_get - x[n-1])/h;
        y_get = y[n-1];
        for (int i = 0; i < n-i0; i++)
        {
            y_get += dy[i][n-2-i] * Multiply(t, i+1)/Multiply(i+1, i+1);
        }
    }
    return y_get;
}
int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Event event;
    while(1)
    {
        bool flag = false;
        int n = 0;
        double scale = 80;
        double middle = 0;
        double h = 0;
        double x0 = 0;
        double xn = 0;
        double x_get;
        double y_get = 0;
        char buf[floatsize] = {0};
        double *x;
        double *y;
        double *x_int;
        double *y_int;
        double **dy;
        double (*func)(double ) = NULL;
        int menu = 0;
        int menu1 = 0;

        system("cls");
        printf("For each func there are 3 different sets of values on interval between x0 and xn\n"
               "Choose the function:\n"
               "1.cos(x)\n"
               "2.ln(x)\n"
               "3.x^2\n");
        do
        {
            menu = Choose(buf);
        }
        while (menu == 0);

        system("cls");
        printf("Enter x0 (note that it should be above 0 for function ln(x)):\n");
        do
        {
            flag = GetDouble(buf);
            if (flag == true && (atof(buf) == 0 && menu == 4 || atof(buf) <= 0 && menu == 2))
            {
                printf("Invalid input, try again\n");
            }
        }
        while (flag == false || atof(buf) == 0 && menu == 4 || atof(buf) <= 0 && menu == 2);
        flag = false;
        x0 = atof(buf);

        system("cls");
        printf("Enter xn (note that it should be greater than %f and above 0 for function ln(x)):\n", x0);
        do
        {
            flag = GetDouble(buf);
            if (flag == true && (atof(buf) == 0 && menu == 4 || atof(buf) <= 0 && menu == 2))
            {
                printf("Invalid input, try again\n");
            }
            else if (flag == true && atof(buf) <= x0)
            {
                printf("Invalid input, try again\n");
            }
        }
        while (flag == false || atof(buf) == 0 && menu == 4 || atof(buf) <= 0 && menu == 2 || atof(buf) <= x0);
        xn = atof(buf);
        flag = false;

        system("cls");
        printf("Enter the step(h) (note that it should be above 0 and shouldn't be greater than %f:\n",(xn-x0)/4);
        do
        {
            flag = GetDouble(buf);
            if (flag == true && (atof(buf) <= 0 || atof(buf) > (xn-x0)/4))
            {
                printf("Invalid input, try again\n");
            }
        }
        while (flag == false || atof(buf) <= 0 || atof(buf) > (xn-x0)/4);
        h = atof(buf);
        flag = false;

        system("cls");
        if (menu == 1)
        {
            func = &Function1;
        }
        else if (menu == 2)
        {
            func = &Function2;
        }
        else
        {
            func = &Function3;
        }
        n = floor((xn-x0)/h) + 1;
        if (xn < 0)
        {
            middle = xn - (xn-x0)/2;
        }
        else
        {
            middle = x0 + (xn-x0)/2;
        }

        printf("Please choose data for interpolation:\n"
               "1.Interval is between %f and %f with %f step\n"
               "2.Interval is between %f and %f with %f step\n"
               "3.Interval from the previous option but with one different y\n", x0, xn, h, x0 + h/16, xn + h/16, h/2);
        do
        {
            menu1 = Choose(buf);
        }
        while (menu1 == 0);

        system("cls");
        if (menu1 == 1)
        {
            x = new double[n];
            y = new double[n];
            y_int = new double[n*2];
            x_int = new double[n*2];
            dy = new double*[n-1];
            for (int i = 0; i < n-1; i++)
            {
                dy[i] = new double[n-1-i];
            }

            printf("x\t\ty\n");
            for (int i = 0; i < n;i++)
            {
                x[i] = x0 + i*h;
                y[i] = (*func)(x[i]);
                printf("%f\t%f\n", x[i], y[i]);
            }
        }
        else
        {
            int i0 = 3;
            x0 = x0 + h/16;
            xn = xn + h/16;
            h = h/2;
            n = floor((xn-x0)/h) + 1;

            if (xn < 0)
            {
                middle = xn - (xn-x0)/2;
            }
            else
            {
                middle = x0 + (xn-x0)/2;
            }
            x = new double[n];
            y = new double[n];
            y_int = new double[n*2];
            x_int = new double[n*2];
            dy = new double*[n-1];

            for(int i = 0; i < n-1;i++)
            {
                dy[i] = new double[n-1-i];
            }

            printf("x\t\ty\n");
            for (int i = 0; i < n;i++)
            {
                x[i] = x0 + i*h;
                y[i] = (*func)(x[i]);
                if (menu1 == 3 && i == i0)
                {
                    y[i] -= y[i]*3;
                }
                printf("%f\t%f\n", x[i], y[i]);
            }
        }

        Difference(n, y, dy);
        for (int i = 0; i < 120; i += 7.5)
        {
            if (fabs(x0)>i || fabs(xn)>i)
            {
                scale /= 2;
            }
            if ((*func)(x0) > (i+7.5) || (*func)(xn) > (i+7.5))
            {
                scale /= 2;
            }
        }

        int count = 0;
        while (1)
        {
                fflush(stdin);
                printf("Enter your x (note that it should be between %f and %f):\n", x0, xn);
                do
                {
                        flag = GetDouble(buf);
                        if (flag == true && (xn < atof(buf) || atof(buf) < x0))
                        {
                            printf("Invalid input, try again\n");
                        }
                }
                while (flag == false || atof(buf) < x0 || atof(buf) > xn);

                x_get = atof(buf);
                flag = false;
                y_get = NewtonPolynomial(n, h, middle, x_get, x, y, y_get, dy);
                printf("y(%f)=%f\n", x_get, y_get);
                x_int[count] = x_get;
                y_int[count] = y_get;
                count++;
                printf("Press 1 to continue or any other key to break:\n");
                if (GetInt(buf) != 1)
                {
                    break;
                }
        }
        window = SDL_CreateWindow("DRAW FUNC", 700, SDL_WINDOWPOS_UNDEFINED, SCREEN_WEIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        surface = SDL_GetWindowSurface(window);
        bool quit = false;
        SDL_Event e;

        while (!quit)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255 , 255);
            SDL_RenderClear(renderer);
            for(int i = 0; i < n; i++)
            {
                DrawPoint(renderer, CENTER_X + x[i]*scale, CENTER_y - y[i]*scale);
            }

            for(int i=0;i<count;i++)
            {
                DrawPoint0(renderer, CENTER_X + x_int[i]*scale, CENTER_y - y_int[i]*scale);
            }

            DrawAxes(renderer,scale);
            DrawFunc0(renderer, func, scale);
            DrawFunc(renderer, &NewtonPolynomial, n, h, middle, x_get, x, y, y_get, dy, scale, x0, xn);
            SDL_RenderPresent(renderer);

            while (SDL_PollEvent(&e))
            {
                if ((e.type == SDL_QUIT) || (e.type == SDL_MOUSEBUTTONDOWN))
                {
                    quit = true;
                }
            }
        }
        SDL_FreeSurface(surface);
        surface = NULL;

        SDL_DestroyWindow(window);
        window = NULL;
        SDL_Quit();
        delete[] x;
        delete[] y;
        for(int i = 0; i < n-1; i++)
        {
            delete[] dy[i];
        }

        delete[] dy;
        delete[] y_int;
        delete[] x_int;

        printf("Press 1 to get back to start menu or any other key to exit:\n");
        if (GetInt(buf) != 1)
        {
            break;
        }
    }
    return 0;
}
