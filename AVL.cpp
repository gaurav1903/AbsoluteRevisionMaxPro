#include<bits/stdc++.h>
typedef long long ll;
using namespace std;




struct Node
{
    int val;
    Node* left=NULL,*right=NULL,*parent=NULL;//VV IMPORTANT LOOK AT IT 
    int leftheight=0,rightheight=0;
};

void inorder(Node* root)
{
    if(root->left!=NULL)
        inorder(root->left);
    // cout<<root->val<<" "<<root->leftheight<<" "<<root->rightheight<<" here"<<endl;
    cout<<root->val<<" "<<root->leftheight<<" "<<root->rightheight<<endl;
    if(root->right!=NULL)
        inorder(root->right);
}

void postorder(Node* root)
{
    if(root->left!=NULL)
        postorder(root->left);
    if(root->right!=NULL)
        postorder(root->right);
    cout<<root->val<<" ";
}
//    1
//   /  \
//  1    3
Node* insertNode(Node* root,Node* p)//p is poiniting to node to be added, root is pointer to our root node
{
    // cout<<"root "<<root->val<<endl;
    
    Node* prob=NULL;
    if(root->val>=p->val)//equal main left subtree
    {
        root->leftheight+=1;
        if(abs(root->leftheight-root->rightheight)>1)
        {
            prob=root;
            // cout<<"prob found at "<<prob->val<<endl;
        } 
        if(root->left!=NULL)
        {
            Node* x=insertNode(root->left,p);
            if(x!=NULL)
                return x;
            else
                return prob;
        }
        else
        {
            p->parent=root;
            root->left=p;
            return prob;    
        }
    }
    else
    {
        root->rightheight+=1;
        if(abs(root->rightheight-root->leftheight)>1)
           {
            prob=root;
            // cout<<"probb at "<<prob->val<<endl;
           }
        if(root->right!=NULL)
        {
            Node* x= insertNode(root->right,p);
            if(x!=NULL)
                return x;
            else
                return prob;
        }
        else
        {
            // cout<<"case 2.2"<<endl;
            root->right=p;
            p->parent=root;
            return prob;
        }  
        
    }
    return NULL;   
}
void llfix(Node *x,Node** root)//right rot
{
    // cout<<"llfix or r rot to "<<x->val<<endl; 
    Node* p=x->parent;
    Node* y=x->left;
    Node* z=y->right;
    x->left=z;
    y->right=x;
    x->parent=y;
    if(z!=NULL)
        {
            z->parent=x;
            x->leftheight=max(z->leftheight,z->rightheight)+1;
        }
    else
        x->leftheight=0;
    y->parent=p;
    y->rightheight=max(x->leftheight,x->rightheight)+1;
    if(p!=NULL)
    {
        if(p->left!=NULL && p->left->val==x->val)
        {
            p->left=y;
            p->leftheight=max(y->leftheight,y->rightheight)+1;
        }
        else
        {
            p->right=y;
            p->rightheight=max(y->leftheight,y->rightheight)+1;
        }
    }
    else
        *root=y;
}

void rrfix(Node *x,Node** root)//left rot fixed
{
    // cout<<"left rot/rrfix to "<<x->val<<" applied"<<endl;
    Node* p=x->parent;
    Node* y=x->right;
    Node *z=y->left;
    x->right=z;
    x->parent=y;
    if(z!=NULL)
    {
        x->rightheight=max(z->leftheight,z->rightheight)+1;  
        z->parent=x; 
    }
    else
        x->rightheight=0;
    y->left=x;
    y->leftheight=max(x->rightheight,x->leftheight)+1;
    if(p!=NULL)
    {
        if(p->left!=NULL && p->left->val==x->val)
           {

           p->left=y;
           p->leftheight=max(y->leftheight,y->rightheight)+1;
           }
        else
        {
            p->right=y;
            p->rightheight=max(y->leftheight,y->rightheight)+1;
        }
        y->parent=p;
    }
    else
    {
        *root=y;
        y->parent=NULL;
    }
    // inorder(*root);
}

void adjustNode(Node* n,int val,Node** root)
{
    Node* y=n;
    //see the prob type
    string prob="";
    for(int i=0;i<2;i++)
    {
        if(n->val>=val)
            {
                prob+="L";
                n=n->left;
            }
        else
        {
            prob+="R";
            n=n->right;
        }
    }
    // cout<<"prob with "<<y->val<<" "<<prob<<endl;
    if(prob=="LL")
        llfix(y,root);  
    else if(prob=="RR")
        rrfix(y,root);
    else if(prob=="LR")
    {
        rrfix(y->left,root);
        llfix(y,root);
    }
    else//RL
    {
        llfix(y->right,root);
        rrfix(y,root);
    }
}


int main()
{
    Node* root= new Node();
    vector<int>data={21,26,30,9,4,14,28,18,15,10};
    // vector<int>data={21,26,30,9,4};
    root->val=data[0];
    
    for(int i=1;i<data.size();i++)
    {
        // cout<<"insert Node "<<data[i]<<" root "<<root->val<<" "<<root->leftheight<<" "<<root->rightheight<<endl;
        Node* p= new Node();
        p->val=data[i];
        Node *prob=insertNode(root,p);
        if(prob!=NULL)
            adjustNode(prob,data[i],&root);
        // cout<<root->val<<" root"<<endl;
        
        // cout<<root->leftheight<<" "<<root->rightheight<<endl;
    }
    cout<<"inorder"<<endl;
        inorder(root);
        cout<<"\npostorder"<<endl;
        postorder(root);
        cout<<endl;
    
}