#include "astronomy.hpp"
#include "curl_data.h"
using namespace std;
namespace wunderground
{

Astronomy::Astronomy(string key): Weather(key)
{

}

void Astronomy::loadData(string city,string state)
{
   MyCurl::get_file(city,state,APIkey,(char *)"astronomy",(char *)"astronomy.xml");

    TiXmlDocument doc;
    string text;
    string text1;
    string text2;
    string value;
    if(!doc.LoadFile("astronomy.xml"))
	{
		std::cerr <<"Could't open file! Is it downloaded?";
		return;
	}

    TiXmlElement* root = doc.FirstChildElement();

	if(root == NULL)
	{
		std::cerr << "Failed to load file: No root element.";
		doc.Clear();
		return ;
	}

if(root->FirstChildElement("error"))
{

    string test = root->FirstChildElement("error")->FirstChildElement("type")->GetText();
    if(test=="keynotfound")
        std::cout<<"\n Wrong key! Try again with different key.";
    else if(test=="querynotfound")
        std::cout<<"\n Wrong city or state. Try again with different name of city or state.";
}
else
{


for( TiXmlElement* elem = root->FirstChildElement("sun_phase")->FirstChildElement(); elem!=NULL; elem = elem->NextSiblingElement() )
    {



            if(elem&& elem->Value())
            {
            value = elem->Value();

            if(value=="sunset")
            {
                text1 = elem->FirstChildElement("hour")->GetText();
                text2 = elem->FirstChildElement("minute")->GetText();
                text = text1 + ":" + text2;
                lista.push_back(make_pair(value,text));

            }
            if(value=="sunrise")
            {
                text1 = elem->FirstChildElement("hour")->GetText();
                text2 = elem->FirstChildElement("minute")->GetText();
                text = text1 + ":" + text2;
                lista.push_back(make_pair(value,text));
            }


            }

    }

    }
}


string Astronomy::getCondition(string condition)
{
    auto pos = find_if(lista.begin(),lista.end(),
                    [&condition](pair<string,string> const& elem)
                    {
                        return elem.first == condition;
                    });
                    if(pos!=lista.end())
                        return (*pos).second;
                    else
                        return "Not found!";
}


}
