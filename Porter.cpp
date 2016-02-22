#include "cheker.h"
#include <iostream>

using namespace std;

boost::regex PUNCTSIGN("[^�-�]"); //,|\\.|\\?|\\(|\\)|(-$)|:|;|\\\\|//|!|�|�|�");
boost::regex PERFECTIVE_GERUND("((([��]{1,1})(�����|���|�))|(������|����|��|������|����|��))$");
boost::regex ADJECTIVE("(��|��|��|��|���|���|��|��|��|��|��|��|��|��|���|���|���|���|��|��|��|��|��|��|��|��)$");
boost::regex PARTICIPLE("((([��]{1,1})(��|��|��|��|�))|(���|���|���))$");
boost::regex REFLEXIVE("(��|��)$");
boost::regex VERB("((([��]{1,1})(��|��|���|���|��|�|�|��|�|��|��|��|��|��|��|���|���))|(���|���|���|����|����|���|���|���|��|��|��|��|��|��|��|���|���|���|��|���|���|��|��|���|���|���|���|��|�))$");
boost::regex NOUN("(�|��|��|��|��|�|����|���|���|��|��|�|���|��|��|��|�|���|��|���|��|��|��|�|�|��|���|��|�|�|��|��|�|��|��|�)$");
boost::regex SUPERLATIVE("(����|���)$");
boost::regex DERIVATIONAL("(����|���)$");
boost::regex I("�$");
boost::regex NN("��$");
boost::regex P("�$");
boost::regex E("(�|�)");
boost::regex RV("^(.*?[���������])");
boost::regex R2("(^(.*?[���������].?[^(���������)]))..?[^(���������)]");

string tolow(string s)
{
    const int temp='�'-'�';
    for(int i=0; i<s.length(); ++i)
    {
        if((s[i]>='�') && (s[i]<='�')) s[i]+=temp;
    }
    return s;
}

string step0(string s)
{
    s=tolow(s);
    s=regex_replace(s,E,"e");
    s=regex_replace(s,PUNCTSIGN,"");
    return s;
}

string step1(string s)
{
    string checkRV=regex_replace(s,RV,"");
    if(regex_search(checkRV,PERFECTIVE_GERUND))
    {
        s=regex_replace(s,PERFECTIVE_GERUND,"");
        return s;
    }
    if(regex_search(checkRV,REFLEXIVE))
    {
        s=regex_replace(s,REFLEXIVE,"");
    }
    if(regex_search(checkRV,ADJECTIVE))
    {
        s=regex_replace(s,ADJECTIVE,"");
        string t=regex_replace(checkRV,ADJECTIVE,"");
        if(regex_search(t,PARTICIPLE))
        {
            s=regex_replace(s,PARTICIPLE,"");
        }
    }
    if(regex_search(checkRV,VERB))
    {
        s=regex_replace(s,VERB,"");
    }
    if(regex_search(checkRV,NOUN))
    {
        s=regex_replace(s,NOUN,"");
    }
    return s;
}

string step2(string s)
{
    string checkRV=regex_replace(s,RV,"");
    if(regex_search(checkRV,I))
    {
        s=regex_replace(s,I,"");
    }
    return s;
}

string step3(string s)
{
    string checkR2=regex_replace(s,R2,"");
    if(regex_search(checkR2,DERIVATIONAL))
    {
        s=regex_replace(s,DERIVATIONAL,"");
    }
    return s;
}

string step4(string s)
{
    string checkRV=regex_replace(s,RV,"");
    if(regex_search(checkRV,NN))
    {
        s=regex_replace(s,NN,"n");
        return s;
    }
    if(regex_search(checkRV,SUPERLATIVE))
    {
        s=regex_replace(s,SUPERLATIVE,"");
        s=step4(s);
        return s;
    }
    if(regex_search(checkRV,P))
    {
        s=regex_replace(s,P,"");
        return s;
    }
    return s;
}


string check(string s)
{
    s=step0(s);
    s=step1(s);
    s=step2(s);
    s=step3(s);
    s=step4(s);
    return s;
}

