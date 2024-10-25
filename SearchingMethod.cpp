#include<iostream>
#include<vector>
#include<unordered_map>
#include <algorithm>
#include<set>
#include<queue>
#include<stack>
#include<string>
#include<cstring>
# define ll long long
using namespace std;
ll SequentialSearch(ll arr[],ll n,ll target){
    bool ok=0;
    for(int i=0;i<n;i++){
        if(arr[i]==target){
            ok=1;
            return i;
        }
    }
    if(!ok){
        return -1;
    }
}
ll IterativeBinarySearch(ll arr[],ll left,ll right,ll target){
    while(left<=right){
        ll mid=ceil((left+right)/2);
        if(target==arr[mid])
            return mid;
        else if(target>arr[mid])    
            left=mid+1;
        else if(target<arr[mid])
            right=mid-1;
    }
    return -1;
}
ll RecursiveBinarySearch(ll arr[],ll left,ll right,ll target){
    if(left>right)
        return -1;
    ll mid=ceil((left+right)/2);
    if(target==arr[mid])
        return mid;
    else if(target>arr[mid])    
        RecursiveBinarySearch(arr,mid+1,right,target);
    else if(target<arr[mid])
        RecursiveBinarySearch(arr,left,mid-1,target);
}
ll recursiveSequentialSearch(ll arr[],ll n, ll target, ll i = 0){
    if(i>=n)
        return -1;
    if(arr[i]==target)
        return i;
    return recursiveSequentialSearch(arr,n,target,i+1);
}
int main(){
    cout<<"enter an array of size 10\n";
    ll arr[10];
    for(int i=0;i<10;i++)
        cin>>arr[i];
    ll target;cin>>target;
    char rechoice;
    do{
    cout<<"Enter type of search:\n "
        <<"1-Sequential Search \n"
        <<"2-Recursive Sequential Search \n"
        <<"3-Binary Search \n "
        <<"4-Recursive Binary Search\n";
    int choice;
    cin>>choice;
    ll index;
    switch(choice){
    case 1:
        index=SequentialSearch(arr,10,target);
        if(index==-1)
            cout<<"Target is not found\n";
        else
            cout<<"Target is found in index: "<<index<<"\n";
    break;
case 2:
    sort(arr,arr+10);
    index=recursiveSequentialSearch(arr,10,target);
    if(index==-1)
        cout<<"Target is not found\n";
    else 
        cout<<"Target is found in index: "<<index<<"\n";
    break;
case 3:
    sort(arr,arr+10);
    index=IterativeBinarySearch(arr,0,10,target);
    if(index==-1)   
        cout<<"Target is not found\n";
    else 
        cout<<"Target is found in index: "<<index<<"\n";
    break;
case 4:
    sort(arr,arr+10);
    index=RecursiveBinarySearch(arr,0,10,target);
    if(index==-1)
        cout<<"Target is not found\n";
    else    
        cout<<"Target is found in index: "<<index<<"\n";
    break;
    default:
            cout << "Invalid choice\n";
            break;
    }
    cout<<"If you want to return Search function press y"<<"\n";
    cin>>rechoice;
    }
    while(rechoice=='y');
    return 0;
}
