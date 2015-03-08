
#include "forecast.hpp"
#include "curl_data.h"

using namespace std;
namespace wunderground
{

Forecast::Forecast(string key):Weather(key)
{
}

void Forecast::loadData(string city,string state)
{
   MyCurl::get_file(city,state,APIkey,(char *)"forecast",(char *)"forecast.xml");

    TiXmlDocument doc;
    string value;
    string text;
    if(!doc.LoadFile("forecast.xml"))
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
for( TiXmlElement* child = root->FirstChildElement("forecast")->FirstChildElement("simpleforecast")->FirstChildElement("forecastdays")->FirstChildElement(); child!=NULL; child = child->NextSiblingElement() )
    {

        for( TiXmlElement* elem = child->FirstChildElement(); elem!=NULL; elem = elem->NextSiblingElement() )
{

            if(elem&& elem->Value())
            {
            value = elem->Value();

            if(value=="date")
            {
                text = elem->FirstChildElement("pretty")->GetText();
                lista.push_back(make_pair("date",text));
                text = elem->FirstChildElement("weekday")->GetText();
                lista.push_back(make_pair("day",text));


            }
            if(value=="high")
            {
                text = elem->FirstChildElement("celsius")->GetText();
                lista.push_back(make_pair("high temperature",text));
            }
            if(value=="low")
            {
                text = elem->FirstChildElement("celsius")->GetText();
                lista.push_back(make_pair("low temperature",text));
            }
             if(value=="conditions")
            {
                text = elem->GetText();
                lista.push_back(make_pair("weather",text));
            }
            if(value=="qpf_allday")
            {
                text = elem->FirstChildElement("mm")->GetText();
                lista.push_back(make_pair("precipitation",text));
            }
            if(value=="avewind")
            {
                text = elem->FirstChildElement("kph")->GetText();
                lista.push_back(make_pair("wind speed",text));
                text = elem->FirstChildElement("dir")->GetText();
                lista.push_back(make_pair("wind direction",text));
            }
            if(value=="avehumidity")
            {
                text = elem->GetText();
                lista.push_back(make_pair("humidity",text));
            }
            }


}

    }

    }

}

string Forecast::getCondition(string condition,string day)
{
   // day[0] = toupper(day[0]);

    auto first = find_if(lista.begin(),lista.end(),
                    [&day](pair<string,string> const& elem)
                    {
                        return elem.second == day;
                    });
    auto pos = find_if(first,lista.end(),
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
