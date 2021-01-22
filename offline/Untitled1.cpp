#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,count;
    cin>>n;
    if(n<3)
        return 0;
    int a[n];
    for(int i=1; i<n-1; i++)
    {
        if((a[i]<a[i-1]&&a[i]<a[i+1])||(a[i]>a[i-1]&&a[i]>a[i+1]))
            count++;
    }
    cout<<count;


    return 0;
}
