#include <iostream>
#include <map>
#include<fstream>
#include<iterator>
#include <string>
#include "cheker.h"

using namespace std;


void input(map<string,int> &words)
{
    ifstream in;
    string s;
    in.open("obl.txt");
    while(in>>s)
    {
        s=check(s);
        if(s.length()<1) continue;
        if (words.count(s)>0)
            words[s]++;
        else
            words.insert(pair<string,int>(s,1));
    }
}

bool compare(map<string,int>::value_type &i1, map<string,int>::value_type &i2)
{
    return i1.second<i2.second;
}

void output(map<string,int> &words)
{
    ofstream out;
	out.open("out.txt");
	//map <string,int>::iterator cur;
    while(words.size()!=0)
    {
        auto cur =max_element(words.begin(), words.end(),compare);
        out << cur->first<<" : "<<cur->second<<endl;
        words.erase(cur);
    }

}


int main()
{
    setlocale(LC_ALL, "rus");
    map<string,int> words;
    input(words);
    output(words);
    return 0;
}
