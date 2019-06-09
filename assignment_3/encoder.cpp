#import <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main()
{
    fstream f, f1;
    f.open("Code.txt",ios::out);
    f1.open("string.txt",ios::out);
    vector<pair<char,int> > v;
    v.push_back(make_pair('a',30));
    v.push_back(make_pair('b',20));
    v.push_back(make_pair('c',15));
    v.push_back(make_pair('d',12));
    v.push_back(make_pair('e',7));
    v.push_back(make_pair('f',6));
    v.push_back(make_pair('g',4));
    v.push_back(make_pair('h',3));
    v.push_back(make_pair('i',2));
    v.push_back(make_pair('j',1));

    char arr[100];
    for(int i=0; i<100; i++)
    {
        if(i<30)
            arr[i]='a';
        else if(i<50)
            arr[i]='b';
        else if(i<65)
            arr[i]='c';
        else if(i<77)
            arr[i]='d';
        else if(i<84)
            arr[i]='e';
        else if(i<90)
            arr[i]='f';
        else if(i<94)
            arr[i]='g';
        else if(i<97)
            arr[i]='h';
        else if(i<99)
            arr[i]='i';
        else
            arr[i]='j';
    }

    for(ll i=0; i<10000000; i++)
    {
        int a = rand()%100;
        int b = rand()%100;
        while(a==b)
            b=rand()%100;
        swap(arr[a],arr[b]);
    }
    for(int i=0; i<100; i++)
    {
        cout<<arr[i];
        f1<<arr[i];
    }
    cout<<"\n";
    string s = "";
    map<char,string> m;
    m.insert(make_pair('a',"00"));
    m.insert(make_pair('b',"11"));
    m.insert(make_pair('c',"010"));
    m.insert(make_pair('d',"100"));
    m.insert(make_pair('e',"0110"));
    m.insert(make_pair('f',"1010"));
    m.insert(make_pair('g',"1011"));
    m.insert(make_pair('h',"01110"));
    m.insert(make_pair('i',"011110"));
    m.insert(make_pair('j',"011111"));

    for(int i=0; i<100; i++)
    {
        s = s + m[arr[i]];
    }
    cout<<"Huffman Encoding: ";
    cout<<s<<"\n";
    f<<s;
    f.close();
    f1.close();
    return 0;
}
