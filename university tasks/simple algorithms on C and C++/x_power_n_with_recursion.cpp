#include <iostream>
using namespace std;

double Power(double, int);
static int function_calls_count = 0;

int main()
{
    double X;
    int N;
    cout << "Recursive function for finding x^n using statements below:\n"
            "1. x^0 = 1;\n"
            "2. x^n = (x^(n/2))^2 if n - even number\n"
            "3. x^n = x * x^(n-1) if n - uneven number\n"
            "4. x^n = 1/(x^n) if n < 0\n"
            "Enter x and n:\n";
    cin >> X >> N;
    cout << Power(X, N);
    cout << "\nfunction was called " << function_calls_count << " times";

    return 0;
}

double Power(double X, int N)
{
    function_calls_count++;
    if (N == 0)
    {
        return 1;
    }
    else if (N < 0)
    {
        return 1/Power(X,-N);
    }
    else
    {
        if ( N%2 != 0 || N == 2)
        {
            return X * Power(X, N-1);
        }

        else
        {
            return Power(Power(X, N/2), 2);
        }

    }

}
