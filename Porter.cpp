#include "cheker.h"
#include <iostream>

using namespace std;

boost::regex PUNCTSIGN("[^а-€]"); //,|\\.|\\?|\\(|\\)|(-$)|:|;|\\\\|//|!|Ч|Ђ|ї");
boost::regex PERFECTIVE_GERUND("((([а€]{1,1})(вшись|вши|в))|(ившись|ивши|ив|ывшись|ывши|ыв))$");
boost::regex ADJECTIVE("(ее|ие|ые|ое|ими|ыми|ей|ий|ый|ой|ем|им|ым|ом|его|ого|ему|ому|их|ых|ую|юю|а€|€€|ою|ею)$");
boost::regex PARTICIPLE("((([а€]{1,1})(ем|нн|вш|ющ|щ))|(ивш|ывш|ующ))$");
boost::regex REFLEXIVE("(с€|сь)$");
boost::regex VERB("((([а€]{1,1})(ла|на|ете|йте|ли|й|л|ем|н|ло|но|ет|ют|ны|ть|ешь|нно))|(ила|ыла|ена|ейте|уйте|ите|или|ыли|ей|уй|ил|ыл|им|ым|ен|ило|ыло|ено|€т|ует|уют|ит|ыт|ены|ить|ыть|ишь|ую|ю))$");
boost::regex NOUN("(а|ев|ов|ие|ье|е|и€ми|€ми|ами|еи|ии|и|ией|ей|ой|ий|й|и€м|€м|ием|ем|ам|ом|о|у|ах|и€х|€х|ы|ь|ию|ью|ю|и€|ь€|€)$");
boost::regex SUPERLATIVE("(ейше|ейш)$");
boost::regex DERIVATIONAL("(ость|ост)$");
boost::regex I("и$");
boost::regex NN("нн$");
boost::regex P("ь$");
boost::regex E("(Є|®)");
boost::regex RV("^(.*?[аеиоуыэю€])");
boost::regex R2("(^(.*?[аеиоуыэю€].?[^(аеиоуыэю€)]))..?[^(аеиоуыэю€)]");

string tolow(string s)
{
    const int temp='а'-'ј';
    for(int i=0; i<s.length(); ++i)
    {
        if((s[i]>='ј') && (s[i]<='я')) s[i]+=temp;
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

