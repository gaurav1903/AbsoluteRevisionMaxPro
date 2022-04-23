#include<bits/stdc++.h>
using namespace std;

vector<int> prefix_func(string s)
{
    //count[i]= len of substr which is prefix and suffix of s[0:i]//i is included and not complete s[0:i]
    vector<int>count(s.size());
    for(int i=1;i<s.size();i++)
    {
        int x=count[i-1];
        while(x>0 && s[i]!=s[x])
        {
            x=count[x-1];
        }
        if(s[x]==s[i])
            count[i]=x+1;
        else
            count[i]=x;
    }
    return count;
}


vector<int> zfunc(string s)//z[i]= len of biggest prefix of s and s[i:]
{
    vector<int>z(s.size());
    int l=0,r=0;
    z[0]=0;
    for(int i=1;i<s.size();i++)
    {
        if(i<=r)
        {
            z[i]=min(r-i+1,z[i-l]);
        }   
        while(i+z[i]<s.size() && s[z[i]]==s[i+z[i]])
        {
            z[i]++;
        }
        if(z[i]+i-1>r)
        {
            r=z[i]+i-1;
            l=i;
        }
    }
    return z;
}
int main()
{
    vector<int>v=zfunc("aaaaa");
    vector<int>v1=zfunc("aaabaab");
    vector<int>v2=zfunc("abacaba");
    for(auto x:v)
        cout<<x<<" ";
    cout<<endl;
    for(auto x:v1)
        cout<<x<<" ";
    cout<<endl;
    for(auto x:v2)
        cout<<x<<" ";
    cout<<endl;
}