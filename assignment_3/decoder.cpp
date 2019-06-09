#include <bits/stdc++.h>
#include<iomanip>
using namespace std;

struct tree
{
    float val;
    bool isleaf;
    char a;
    struct tree *left;
    struct tree *right;
};

struct tree* newnode(float val)
{
    struct tree *tmp;
    tmp = new tree;
    tmp->val = val;
    tmp->isleaf= false;
    tmp->a = '@';
    tmp->left = NULL;
    tmp->right = NULL;
    return tmp;
};

struct tree* newnode(float val, char a)
{
    struct tree *tmp;
    tmp = new tree;
    tmp->val = val;
    tmp->isleaf = true;
    tmp->a = a;
    tmp->left = NULL;
    tmp->right = NULL;
    return tmp;
};

void inorder(struct tree *root)
{
    if(root==NULL)
        return;
    inorder(root->left);
    //cout<<fixed;
    cout<<root->val<<setprecision(3)<<"\n";
    if(root->isleaf)
        cout<<root->a<<"\n";
    inorder(root->right);
}

int main()
{
    struct tree* root = newnode(1);
    root->left = newnode(0.58);
    root->right = newnode(0.42);
    root->left->left = newnode(0.3,'a');
    root->left->right = newnode(0.28);
    root->left->right->left = newnode(0.15,'c');
    root->left->right->right = newnode(0.13);
    root->left->right->right->left = newnode(0.07,'e');
    root->left->right->right->right = newnode(0.06);
    root->left->right->right->right->left = newnode(0.03,'h');
    root->left->right->right->right->right = newnode(0.03);
    root->left->right->right->right->right->left = newnode(0.02,'i');
    root->left->right->right->right->right->right = newnode(0.01,'j');
    root->right->right = newnode(0.2,'b');
    root->right->left = newnode(0.22);
    root->right->left->left = newnode(0.12,'d');
    root->right->left->right = newnode(0.1);
    root->right->left->right->left = newnode(0.06,'f');
    root->right->left->right->right = newnode(0.04,'g');
    //inorder(root);

    ifstream f;
    f.open("Code.txt",ios::in);
    string s;
    f>>s;
    cout<<s;
    cout<<"\n";
    string s1 = "";
    struct tree *tmp = root;
    cout<<s.length()<<"\n";
    for(int i=0; i<s.length(); i++)
    {
        if(tmp->left == NULL && tmp->right==NULL)
        {
            s1 = s1 + tmp->a;
            tmp = root;
        }
        if(s[i]=='0')
            tmp = tmp->left;
        else if(s[i]=='1')
            tmp = tmp->right;
    }
    s1 = s1 + tmp->a;
    cout<<"\nDecoded: "<<s1;
    return 0;
}
