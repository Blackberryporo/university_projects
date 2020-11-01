#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cmath>
#include <math.h>
#include <time.h>
#include <float.h>
#include <string.h>
#include <limits>
#include <string>

#define floatsize 50
#define _USE_MATH_DEFINES

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 640;
const int CENTER_X = SCREEN_WIDTH / 2;
const int CENTER_Y = SCREEN_HEIGHT / 2;

struct LTexture
{
    public:
    LTexture();

    ~LTexture();

    bool loadFromFile(string path);

    bool loadFromRenderedText(string textureText, SDL_Color textColor);

    void free();

    void setColor(Uint8 red, Uint8 green, Uint8 blue);

    void setBlendMode(SDL_BlendMode blending);

    void setAlpha(Uint8 alpha);

    void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL,
            SDL_RendererFlip flip = SDL_FLIP_NONE);

    int getWidth();
    int getHeight();

    private:
    SDL_Texture* mTexture;

    int mWidth;
    int mHeight;
};

void init();

void close();

SDL_Window* gWindow;
SDL_Renderer* gRenderer;
TTF_Font *gFont;
LTexture gTextTexture;

LTexture::LTexture()
{
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture()
{
    free();
}

bool LTexture::loadFromRenderedText(string textureText, SDL_Color textColor)
{
    free();

    SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);

    if (textSurface == NULL)
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    }
    else
    {
        mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);

        if (mTexture == NULL)
        {
            printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        }
        else
        {
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }

        SDL_FreeSurface( textSurface );
    }

    return mTexture != NULL;
}

void LTexture::free()
{
    if(mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
    SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::setBlendMode(SDL_BlendMode blending)
{
    SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::setAlpha(Uint8 alpha)
{
    SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LTexture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};

    if(clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int LTexture::getWidth()
{
    return mWidth;
}

int LTexture::getHeight()
{
    return mHeight;
}

void init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    }

    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    {
        printf("Warning: Linear texture filtering not enabled!");
    }

    gWindow = SDL_CreateWindow("LAB3", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
                    SDL_WINDOW_SHOWN);

    if (gWindow == NULL)
    {
        printf( "Window could not be created! SDL Error: %s\n", SDL_GetError());
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (gRenderer == NULL)
    {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
    }

    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);

    if (TTF_Init() == -1)
    {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
    }

}

bool loadMedia(char *text)
{
    gFont = TTF_OpenFont("arial.ttf", 8);

    if(gFont == NULL)
    {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
    }

    SDL_Color textColor = {0, 0, 0};

    if(!gTextTexture.loadFromRenderedText(text, textColor))
    {
        printf("Failed to render text texture!\n");
    }
}

void close()
{
    gTextTexture.free();

    TTF_CloseFont(gFont);
    gFont = NULL;

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    TTF_Quit();
    SDL_Quit();
}

void CoordAxis(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderDrawLine(renderer, SCREEN_WIDTH/2, 20, SCREEN_WIDTH/2, SCREEN_HEIGHT - 20);
    SDL_RenderDrawLine(renderer, 20, SCREEN_HEIGHT/2, SCREEN_WIDTH - 20, SCREEN_HEIGHT/2);

    SDL_RenderDrawLine(renderer, SCREEN_WIDTH/2, 20, SCREEN_WIDTH/2 - 5, 25);
    SDL_RenderDrawLine(renderer, SCREEN_WIDTH/2, 20, SCREEN_WIDTH/2 + 5, 25);

    SDL_RenderDrawLine(renderer, SCREEN_WIDTH - 20, SCREEN_HEIGHT/2, SCREEN_WIDTH - 25, SCREEN_HEIGHT/2 - 5);
    SDL_RenderDrawLine(renderer, SCREEN_WIDTH - 20, SCREEN_HEIGHT/2, SCREEN_WIDTH - 25, SCREEN_HEIGHT/2 + 5);
}

void DrawPoint(SDL_Renderer *renderer, int x, int y)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderDrawLine(renderer, x, y, x-2, y-2);
    SDL_RenderDrawLine(renderer, x, y, x-2, y+2);
    SDL_RenderDrawLine(renderer, x, y, x+2, y-2);
    SDL_RenderDrawLine(renderer, x, y, x+2, y+2);
}

void DrawFunc(SDL_Renderer *renderer, double (*Func)(int,double,double,double,double*,double*,double,double**),int n,
    double h,double middle,double x_get,double* x,double *y,double y_get,double** dy, double scale,double x0,double xn)
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Point *points = (SDL_Point *)malloc(sizeof(SDL_Point) * scale * 10 * SCREEN_WIDTH);
    if (x0 > 0)
    {
        x_get = x0;
    }
    else
    {
        x_get = 0;
    }

    int count = 0;
    if (xn > 0)
    {
        for(int i = 0; i < SCREEN_WIDTH * scale* 10; i++)
        {
            points[i].x = CENTER_X + x_get * scale;
            points[i].y = CENTER_Y - (*Func)(n,h,middle,x_get,x,y,y_get,dy) * scale;
            if (x_get >= xn)
            {
                break;
            }
            x_get += 0.001;
            count++;
        }
    }
    SDL_RenderDrawLines(renderer, points, count);
    free(points);
    points = (SDL_Point *)malloc(sizeof(SDL_Point) * scale * 10 * SCREEN_WIDTH);
    if (xn < 0)
    {
        x_get=xn;
    }
    else
    {
        x_get = 0;
    }

    count = 0;
    if (x0 < 0)
    {
        for(int i = 0; i < SCREEN_WIDTH * scale * 10; i++)
        {
            points[i].x = CENTER_X - x_get * scale;
            points[i].y = CENTER_Y - (*Func)(n, h, middle, -x_get, x, y, y_get, dy) * scale;
            if (-x_get <= x0) break;
            x_get += 0.001;
            count++;
        }
    }
    SDL_RenderDrawLines(renderer, points, count);
    free(points);
}

void CoordNumb(SDL_Renderer *renderer, int scale)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    char number[3];
    char minus[4];
    number[0] = '1';
    number[1] = 0;
    number[2] = 0;

    minus[0] = '-';
    minus[1] = '1';
    minus[2] = 0;
    minus[3] = 0;

    for(int i = scale; i < CENTER_X - 20; i += scale)
    {
        loadMedia(number);
        SDL_RenderDrawLine(renderer, CENTER_X + i, CENTER_Y - 5, CENTER_X + i, CENTER_Y + 5);
        SDL_RenderDrawLine(renderer, CENTER_X - i, CENTER_Y - 5, CENTER_X - i, CENTER_Y + 5);
        gTextTexture.render(i + CENTER_X, CENTER_Y + 10);

        loadMedia(minus);
        gTextTexture.render(- i + CENTER_X, CENTER_Y + 10);

        if(number[0] >= '9')
        {
        number[0] = '1';
        number[1] = '0';
        }
        else if(number[1] >= '0') number[1] += 1;
        else number[0] += 1;

        if(minus[1] >= '9')
        {
            minus[1] = '1';
            minus[2] = '0';
        }
        else if(minus[2] >= '0') minus[2] += 1;
        else minus[1] += 1;
    }

    number[0] = '1';
    number[1] = 0;
    number[2] = 0;

    minus[0] = '-';
    minus[1] = '1';
    minus[2] = 0;
    minus[3] = 0;

    for(int i = scale; i < CENTER_Y - 20; i += scale)
    {
        loadMedia(number);
        SDL_RenderDrawLine(renderer, CENTER_X + 5, CENTER_Y + i, CENTER_X - 5, CENTER_Y + i);
        SDL_RenderDrawLine(renderer, CENTER_X + 5, CENTER_Y - i, CENTER_X - 5, CENTER_Y - i);
        gTextTexture.render(CENTER_X + 10, CENTER_Y - i);

        loadMedia(minus);
        gTextTexture.render(CENTER_X + 10, CENTER_Y + i);

        if (number[0] >= '9')
        {
            number[0] = '1';
            number[1] = '0';
        }
        else if (number[1] >= '0')
        {
            number[1] += 1;
        }
        else
        {
            number[0] += 1;
        }

        if (minus[1] >= '9')
        {
            minus[1] = '1';
            minus[2] = '0';
        }
        else if (minus[2] >= '0')
        {
            minus[2] += 1;
        }
        else
        {
            minus[1] += 1;
        }
    }
}

bool GetDouble(char* buf)
{
    bool point = false;
    bool notspace = false;
    bool afterspace = false;
    int i = 0;
    fflush(stdin);
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

double Func(double x, double y)
{
    double dY = 1/cos(x) - y*tan(x);
    return dY;
}

double Multiply(double x, int n)
{
    double mul = 1;
    for (int i = 0; i < n; i++)
    {
        if (x >= 0)
        {
            mul *= x-i;
        }
        else
        {
            mul *= x+i;
        }
    }
    return mul;
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

double Runge(double x0, double y0, double h)
{
    double k0 = Func(x0, y0);
    double k1 = Func(x0 + h/2, y0 + h*k0/2);
    double k2 = Func(x0 + h/2, y0 + h*k1/2);
    double k3 = Func(x0 + h, y0 + h*k2);
    double y = y0 + h/6*(k0 + 2*k1 + 2*k2 + k3);
    return y;
}

void Adams(double *dY, double *y, double *x, int n, double h)
{
    double d1Y=0;
    double d2Y=0;
    double d3Y=0;
    for (int i = 4; i < n; i++)
    {
        x[i] = x[i-1] + h;
        d1Y = dY[i-1] - dY[i-2];
        d2Y = dY[i-1] - 2*dY[i-2] + dY[i-3];
        d3Y = dY[i-1] - 3*dY[i-2] + 3*dY[i-3] - dY[i-4];
        y[i] = y[i-1] + h*dY[i-1] + ((pow(h,2))*d1Y)/2 + ((pow(h,3))*d2Y*5)/12 + ((pow(h,4))*d3Y*3)/8;
        dY[i] = Func(x[i],y[i]);
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

int main(int argc, char* args[])
{
    while(1)
    {
        bool flag = false;
        bool quit = false;
        int n = 0;
        double scale = 40;
        double middle = 0;
        double h = 0;
        double eps = 0;
        double x0 = 0;
        double y0 = 0;
        double xn = 0;
        double x_get;
        double y_get = 0;
        char buf[floatsize] = {0};
        double *x;
        double *y;
        double *dY;
        double **dy;

        system("cls");
        printf("y' = 1/cos(x) - y*tg(x); y(x0) = y0\n");
        printf("Enter x0:\n");
        do
        {
            flag = GetDouble(buf);
        }
        while (flag == false);

        flag = false;
        x0 = atof(buf);
        printf("Enter y0:\n");
        do
        {
            flag = GetDouble(buf);
        }
        while (flag == false);

        flag=false;
        y0 = atof(buf);
        printf("Enter xn (xn > x0):\n");
        do
        {
            flag = GetDouble(buf);
            if (flag == true && atof(buf) <= x0)
            {
                printf("Invalid input, try again\n");
            }
        }
        while (flag == false || atof(buf) <= x0);

        flag=false;
        xn = atof(buf);
        printf("Enter accuracy (eps!=0):\n");
        do
        {
            flag = GetDouble(buf);
            if (flag == true && atof(buf) == 0 || flag == true && ((pow(fabs(atof(buf)),1.0/3)) > ((xn-x0)/4)))
            {
                printf("Invalid input, try again\n");
            }
        }
        while (flag == false || atof(buf) == 0 || ((pow(fabs(atof(buf)),1.0/3)) > ((xn-x0)/4)));

        flag = false;
        eps = atof(buf);
        system("cls");
        printf("y'= 1/cos(x) - y*tg(x); y(x0) = y0\n");

        h = pow(fabs(eps),1.0/3);
        printf("h = %f\n",h);
        n = floor((xn-x0)/h) + 2;
        if(xn < 0)
        {
            middle = xn - (xn-x0)/2;
        }
        else
        {
            middle = x0 + (xn-x0)/2;
        }
        printf("n = %i\n",n);

        x = new double[n];
        y = new double[n];
        dY = new double[n];
        dy = new double*[n-1];
        for(int i = 0; i < n-1; i++)
        {
            dy[i] = new double[n-1-i];
        }
        x[0] = x0;
        y[0] = y0;
        dY[0] = Func(x[0], y[0]);

        for (int i = 1; i < 4; i++)
        {
            x[i] = x0 + i*h;
            y[i] = Runge(x[i-1], y[i-1], h);
            dY[i] = Func(x[i], y[i]);
        }
        Adams(dY, y, x, n, h);
        Difference(n, y, dy);

        printf("i\tx\t\ty\t\tdY\t\n");
        for (int i = 0; i < n; i++)
        {
            printf("%i\t%f\t%f\t%f\t\n", i, x[i], y[i], dY[i]);
        }
        init();
        SDL_Event e;
        SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 0);
        SDL_RenderClear(gRenderer);

        CoordAxis(gRenderer);
        CoordNumb(gRenderer, scale);
        DrawFunc(gRenderer, &NewtonPolynomial, n, h, middle, x_get, x, y, y_get, dy, scale, x0, xn);
        SDL_RenderPresent(gRenderer);

        while(!quit)
        {
            while(SDL_PollEvent(&e) != 0)
            {
                if(e.type == SDL_QUIT)
                    quit = true;
                if(e.type == SDL_KEYDOWN)
                    scale -= 10;
                if(e.type == SDL_MOUSEWHEEL)
                    scale += 10;
            }
            SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 0);
            SDL_RenderClear(gRenderer);

            CoordAxis(gRenderer);
            CoordNumb(gRenderer, scale);
            DrawFunc(gRenderer, &NewtonPolynomial,n,h,middle,x_get,x,y,y_get,dy,scale,x0,xn);

            for(int i = 0; i < n; i++)
            {
                DrawPoint(gRenderer, CENTER_X + x[i]*scale, CENTER_Y - y[i]*scale);
            }
            SDL_RenderPresent(gRenderer);
        }
        close();
    }
    return 0;
}

