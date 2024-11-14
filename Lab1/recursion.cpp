#include <iostream>
#include <string>

using namespace std;

long long sumOfS(int n) //Ex1
{
    if (n == 1) return 1;
    return n + sumOfS(n - 1);
}

long long factorial(int n) // Ex2
{
    if (n == 1) return 1;
    return n * factorial(n - 1);
}

long long power(int x, int n) //Ex 3
{
    if (n == 1) return x;
    return x * power(x, n - 1);
}

int numberOfDigits(int n) //Ex4
{
    if (n <= 9) return 1;
    return 1 + numberOfDigits(n / 10);
}

int evenDigits(int n) //Ex5
{
    if (n % 2 != 0) return 0;
    if (n == 0) return 1;
    return evenDigits(n / 10);
}

int CD(int a, int b, int k)
{
    if (k == 1) return 1;
    if (a % k == 0 && b % k == 0)
        return 1 + CD(a, b. k - 1);
    return CD(a, b, k - 1);
}

int GCD(int a, int b)
{
    if (b == 0) return a;
    return GCD(b, a & b);
}

long long LCM(int a, int b)
{
    return a * b / GCD(a, b);
}

int reverseValue(int n, int ans)
{
    if (n == 0) return ans;
    ans = ans*10 + n % 10;
    return reverseValue(n / 10, ans);
}

long long fibonacci(int n)
{
    if (n == 0) return 0;
    if (n == 1) return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}
void printOut(string raw, int p[])
{
    for (int i = 0; i < 4; ++i) {
        cout << raw[p[i]];
    }
    cout << endl;
}

void permutation(string raw, int k, int c[], int p[])
{
    if (k == 4) printOut(raw, p);
    for (int i = 0; i < 4; ++i) {
        if (!(c[i])) {
            p[k] = i;
            c[i] = 1;
            permutation(raw, k + 1, c, p);
            c[i] = 0;
        }
    }
}

int binarySearch(int a[]. int l, int r, int x)
{
    if (l > r) return -1;
    int mid = (l + r) / 2;
    if (a[mid] == x) return mid;
    if (a[mid] > x) return binarySearch(a, l, mid - 1, x);
    return binarySearch(a, mid + 1, r, x);
}

int main()
{
    int c[5] = {0}, p[5];
    permutation("ABCD", 0, c, p);
}
