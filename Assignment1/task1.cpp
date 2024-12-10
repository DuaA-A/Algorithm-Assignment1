#include <iostream>
#include <vector>
# define ll long long
using namespace std;
const int m = 1e9 + 7;

ll FibonacciRecursion(ll n){
if(n<=1)return n;
else return FibonacciRecursion(n-1)+FibonacciRecursion(n-2);
}
void multiply(vector<vector<ll>>& a, vector<vector<ll>>& b){

    vector<vector<ll>>r(2,vector<ll>(2));
    r[0][0]=(a[0][0]*b[0][0]+a[0][1]*b[1][0])%m;
    r[0][1]=(a[0][0]*b[0][1]+a[0][1]*b[1][1])%m;
    r[1][0]=(a[1][0]*b[0][0]+a[1][1]*b[1][0])%m;
    r[1][1]=(a[1][0]*b[0][1]+a[1][1]*b[1][1])%m;

    a = r;
}

vector<vector<ll>> getPower(vector<vector<ll>>& M, int expo){
    vector<vector<ll>>res={{1, 0}, {0, 1}};
    while (expo>0) {
        if (expo%2)
            multiply(res,M);

        multiply(M,M);
        expo/=2;
    }
    return res;
}

int FibonacciMatrixMaltiplication(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    vector<vector<long long>> M = {{1, 1}, {1, 0}};
    vector<vector<long long>> res = getPower(M, n - 1);
    return res[0][0];
}


int DP_Fibonacci(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;

    vector<int> fib(n + 1);
    fib[0] = 0;
    fib[1] = 1;

    for (int i = 2; i <= n; ++i) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    return fib[n];
}

int main()
{
    int n;
    cout << "Enter the position of Fibonacci you want: ";
    cin >> n;
    char tryAgain;
    do{
    cout<<"choose the way you want to implement with\n"
        <<"1. Recursion\n"
        <<"2. Matrix Exponentiation\n"
        <<"3. with DP\n";

    int choice;
    cin>>choice;
    if(choice==1)
           cout<< "The Fibonacci number of "<<n<<"th is: " << FibonacciRecursion(n)<< "\n";
    else if(choice==2){
            cout<< "The Fibonacci number of "<<n<<"th is: " << FibonacciMatrixMaltiplication(n) << "\n";
    }
    else if(choice==3){
            cout<< "The Fibonacci number of "<<n<<"th is: " << DP_Fibonacci(n) << "\n";
    }
    cout<<"If you want to rechoice Again press :(y/n)\n";
    cin>>tryAgain;
    }while(tryAgain=='y');
    return 0;
}
