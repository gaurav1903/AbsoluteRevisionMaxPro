#include<bits/stdc++.h>

using namespace std;
vector<int>parent;
vector<int>ranks;
vector<int>sizes;
int totalsets;
void make_dsu(int n)
{
    totalsets=n-1;
    ranks.resize(n);
    sizes.resize(n,1);
    for(int i=0;i<n;i++)
    {
        parent.push_back(i);
    }
}


int find_dsu(int n)//finding parent and path compression 
{
    
    if(parent[n]!=n)
    {
        // cout<<n<<" "<<parent[n]<<endl;
        parent[n]=find_dsu(parent[n]);
    }
    return parent[n];
}

int givesize(int n)
{
    int p=find_dsu(n);
    return sizes[p];
}

void union_dsu(int a,int b)//using rank heurisitics
{
    int x=find_dsu(a);
    int y=find_dsu(b);
    // cout<<x<<" "<<y<<endl;
    if(x==y)
        return ;
    else
    {
        totalsets--;
        if(ranks[x]<ranks[y])
        {
            parent[x]=y;
            sizes[y]+=sizes[x];
        }
        else if(ranks[x]>ranks[y])
        {
            parent[y]=x;
            sizes[x]+=sizes[y];
        }
        else
        {
            parent[x]=y;
            ranks[y]++;
            sizes[y]+=sizes[x];
        }
    }
}

int main()
{
    make_dsu(n+1);

}