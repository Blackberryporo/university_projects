#include <iostream>
using namespace std;

long long GCD(long, long);

int main()
{
    long a, b;
    cout << "Finding greatest common divisor using Euclidean algorithm.\nEnter two numbers:\n";
    cin >> a >> b;
    cout << GCD(a, b);
    return 0;
}

long long GCD(long a, long b)
{
    long r = 0;
    if (a == 0)
    {
        return b;
    }
    else if (b == 0)
    {
        return a;
    }

    a = (a < 0) ? -a : a;
    b = (b < 0) ? -b : b;
    r = a%b;

    if (r != 0)
    {
        a = b;
        b = r;
        GCD(a, b);
    }
    else return b;
}

