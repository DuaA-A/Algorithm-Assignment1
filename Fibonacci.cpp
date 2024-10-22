#include<bits/stdc++.h>
# define ll long long
using namespace std;
ll FibonaccRecursion(ll n){
if(n<=1)return n;
else return FibonacciRecursion(n-1)+FibonaccRecursion(n-2);
}
int main()
{
    ll n;cin>>n;
    cout<<FibonacciRecursion(n);
    return 0;
}
