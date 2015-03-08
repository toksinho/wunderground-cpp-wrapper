
#include "hourly.hpp"
#include "curl_data.h"

using namespace std;
namespace wunderground
{


Hourly::Hourly(string key):Weather(key)
{
}

void Hourly::loadData(string city,string state)
{
   MyCurl::get_file(city,state,APIkey,(char *)"hourly",(char *)"hourly.xml");

    TiXmlDocument doc;
    string value;
    string text;
    string date;
    if(!doc.LoadFile("hourly.xml"))
	{
		std::cerr << "Could't open file! Is it downloaded?";
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
for( TiXmlElement* child = root->FirstChildElement("hourly_forecast")->FirstChildElement("forecast"); child!=NULL; child = child->NextSiblingElement() )
    {

        for( TiXmlElement* elem = child->FirstChildElement(); elem!=NULL; elem = elem->NextSiblingElement() )
        {

            if(elem&& elem->Value())
            {
            value = elem->Value();

            if(value=="FCTTIME")
            {
                date = elem->FirstChildElement("month_name")->GetText();
                text = elem->FirstChildElement("mday")->GetText();
                date = date + ' ' + text;

                lista.push_back(make_pair("day",date));

                text = elem->FirstChildElement("weekday_name")->GetText();
                lista.push_back(make_pair("day name",text));
                text = elem->FirstChildElement("pretty")->GetText();
                lista.push_back(make_pair("date",text));
                text = elem->FirstChildElement("hour")->GetText();
                lista.push_back(make_pair("hour",text));

            }
            if(value=="temp")
            {
                text = elem->FirstChildElement("metric")->GetText();
                lista.push_back(make_pair("temperature",text));
            }
            if(value=="condition")
            {
                lista.push_back(make_pair(value,elem->GetText()));
            }
             if(value=="wspd")
            {
                text = elem->FirstChildElement("metric")->GetText();
                lista.push_back(make_pair("wind speed",text));
            }
            if(value=="wdir")
            {
                text = elem->FirstChildElement("dir")->GetText();
                lista.push_back(make_pair("wind direction",text));
            }
            if(value=="humidity")
            {

                lista.push_back(make_pair(value,elem->GetText()));

            }
            if(value=="qpf")
            {
                text = elem->FirstChildElement("metric")->GetText();
                lista.push_back(make_pair("precipitation",text));
            }
            if(value=="mslp")
            {
                text = elem->FirstChildElement("metric")->GetText();
                lista.push_back(make_pair("pressure",text));
            }
            }



}




    }








    }

}

string Hourly::getCondition(string condition,string day, string hour) const//PROBLEM KOJI DAN ILI KOJI DATUM?
{
    day[0] = toupper(day[0]);

    auto first = find_if(lista.begin(),lista.end(),
                    [&day](pair<string,string> const& elem)
                    {
                        return elem.second == day;
                    });
    auto pos = find_if(first,lista.end(),
                    [&hour](pair<string,string> const& elem)
                    {
                        return elem.second == hour;
                    });
                    if(pos!=lista.end())
                    {
                        auto newpos = find_if(pos,lista.end(),
                                           [&condition](pair<string,string> const &elem)
                                           {
                                               return elem.first == condition;
                                           });
                        return (*newpos).second;
                    }
                    else
                        return "Not found that day or that hour!";
}

}


