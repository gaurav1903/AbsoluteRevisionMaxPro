#include<iostream>
#include<bits/stdc++.h>
#include<string>
typedef long long ll;
typedef unsigned int ui;
#define infin (ll)(998244353)
using namespace std;
vector<int> readfromline()
{
    string temp;
    vector<int>v;
    getline(cin,temp,'\n');
    stringstream s;
    s<<temp;
    int x;
    while(s>>x)
    {
        v.push_back(x);
    }
    return v;
}


ll prim(vector<vector<pair<int,int>>>graph)// returns sum of edges and takes vector whose each member is a vector 0th vector denoting 1 vertex is connected to other vertices each of ths is apair
//{vertex it is connected to,weight of edge connecting them}
{
    ll sum=0;
    set<int>vertex_found;
    vertex_found.insert(1);
    priority_queue<pair<int,int>> min_heap;///by default priority queue is max heap
    //weight*-1 ,second vertex
    // vector<vector<pair<int,int>>>tree;

    for(int i=0;i<graph[0].size();i++)
    {
        min_heap.push({graph[0][i].second*-1,graph[0][i].first});
    }
    while (vertex_found.size()!=graph.size())
    {
        pair<int,int>edge=min_heap.top();
        min_heap.pop();
        while(vertex_found.find(edge.second)!=vertex_found.end())
        {
            edge=min_heap.top();
            min_heap.pop();
        }
        vertex_found.insert(edge.second);
        sum+=edge.first*-1;
        for(int i=0;i<graph[edge.second-1].size();i++)
        {
             min_heap.push({graph[edge.second-1][i].second*-1,graph[edge.second-1][i].first});
        }

    }
    return sum;
}
void set_segment_tree(vector<ll>& segment_tree,int i,int val,int size)//size is v.size() -?no. of eelemnts in official array
{
    //i is index of official  array of size n 
    // if(rx-lx==1)
    // {
    //     segment_tree[x]=val;
    //     return ;
    // }
    // int m=lx+rx/2;
    // if(i<m)
    //   set_segment_tree(segment_tree,i,lx,m,2*x+1,val);
    // else
    //   set_segment_tree(segment_tree,i,m,rx,2*x+2,val);
    // segment_tree[x]=segment_tree[2*x+1]+segment_tree[2*x+2];
    int k=segment_tree.size()-size+i;
    segment_tree[k]=val;
    while(k>0)
    {
        if(k%2==0)
        {
            k=(k-2)/2;
            segment_tree[k]=segment_tree[2*k+1]+segment_tree[2*k+2];
        }
        else
        {
            k=(k-1)/2;
            segment_tree[k]=segment_tree[2*k+1]+segment_tree[2*k+2];
        }
    }
}
ll sum_segment_tree(vector<ll>&segment_tree,int l,int r,int left,int right,int x)//left and right are current boundaries and both boundaries are included of l and r and right and left
{
    if(left>=r|| right<=l)
    {
        return 0;
    }
    else if(l<=left && r>=right)
    {
        
      return segment_tree[x];
    }
    else
    {
        return sum_segment_tree(segment_tree,l,r,left,(left+right)/2,2*x+1)+sum_segment_tree(segment_tree,l,r,(left+right)/2,right,2*x+2);
    }
}
vector<ll> segment_tree(vector<int>&v)
{
    int size=log2((int)v.size());
    if(pow(2,size)<(ll)v.size())
    {
        ll x=pow(2,size+1)-v.size();
        while(x!=0)
        {
            v.push_back(0);
            x--;
        }
        size=pow(2,size+1);
    }
    else
      size=pow(2,size);
    for(auto x:v)
    {
        cout<<x<<" ";
    }
    cout<<endl;
    vector<ll>ans(2*size-1);
    int j=ans.size()-1;
    // cout<<2*size-1<<endl;
    for(int i=v.size()-1;i>=0;i--)
    {
        ans[j]=v[i];
        j--;
    }
    int k=size/2;
    int y=k;
    while(k!=0)
    {
        ans[j]=ans[2*j+1]+ans[2*j+2];
        k--;
        j--;
        if(k==0)
        {
            k=y/2;
            y=k;
        }
    }
    for(auto x:ans)
    {
        cout<<x<<" ";
    }
    cout<<endl;
    return ans;
}
ll max_segment_tree(vector<ll>&segment_tree,int l,int r,int left,int right,int x)//left and right are current boundaries and l is included while r  is not
{
    if(left>=r|| right<=l)
    {
        return 0;
    }
    else if(l<=left && r>=right)
    {
        
      return segment_tree[x];
    }
    else
    {
        return max(max_segment_tree(segment_tree,l,r,left,(left+right)/2,2*x+1),max_segment_tree(segment_tree,l,r,(left+right)/2,right,2*x+2));
    }
}
int main()
{
    vector<int>v={5,4,2,3,9};
    vector<ll>ans=segment_tree(v);
    // set_segment_tree(ans,2,25,v.size());
    for(auto y:ans)
    {
        cout<<y<<" ";
    }
    cout<<endl;
    cout<<"now printing"<<endl;
    cout<<max_segment_tree(ans,0,4,0,v.size(),0)<<endl;//r not included l included
}