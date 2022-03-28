#include<bits/stdc++.h>
using namespace std;

struct Node
    {
        int mark=0;//endmark
        unordered_map<char,Node*>children;
    };
class Trie
{
    private:
        Node* head= new Node();
        
    public:
        Node *p=head;
        void insertWord(string word)
        {
            p=head;
            for(int i=0;i<word.size();i++)
            {
                if(p->children[word[i]]==NULL)
                {
                    Node*n =new Node();
                    p->children[word[i]]=n;
                    p=n;
                }
                else
                    p= p->children[word[i]];
            }
            p->mark=1;
        }
    
    Node* gethead()
    {
        return head;
    }
    int searchword(string& word)
    {
        p=head;
        for(int i=0;i<word.size();i++)
        {
            if(p->children[word[i]]!=NULL)
            {
                p=p->children[word[i]];
            }
            else
                return 0;
        }
        return p->mark;
    }
};