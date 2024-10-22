#include<bits/stdc++.h>
# define ll long long
using namespace std;
ll FibonacciRecursion(ll n){
if(n<=1)return n;
else return FibonacciRecursion(n-1)+FibonacciRecursion(n-2);
}
int main()
{
    ll n;cin>>n;
    cout<<FibonacciRecursion(n);
    return 0;
}
