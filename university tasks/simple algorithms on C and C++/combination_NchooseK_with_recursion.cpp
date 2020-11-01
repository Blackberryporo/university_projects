#include <iostream>
using namespace std;

int Combin(int, int);

int main()
{
    int N, K;
    cout << "To find combination N choose K enter N and K (N >= K, K >= 0, N > 0):\n";
    cin >> N >> K;
    cout << Combin(N, K);

    return 0;
}

int Combin(int N, int K)
{
    if (K == 0 || K == N)
    {
        return 1;
    }
    else
    {
        return (Combin(N-1, K) + Combin(N-1, K-1));
    }
}
