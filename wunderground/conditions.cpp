
#include "conditions.hpp"
#include "curl_data.h"

using namespace std;
namespace wunderground
{

Conditions::Conditions(string key):Weather(key)
{
}

void Conditions::loadData(string city,string state)
{
   MyCurl::get_file(city,state,APIkey,(char *)"conditions",(char *) "conditions.xml");

    TiXmlDocument doc;
    string value;
    string text;
    if(!doc.LoadFile("conditions.xml"))
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
	for( TiXmlElement* child = root->FirstChildElement("current_observation")->FirstChildElement("station_id"); child!=NULL; child = child->NextSiblingElement() )
    {

            if(child && child->GetText())
            {

                value = child->Value();

            if(value=="local_time_rfc822")
            {
                text = child->GetText();
                lista.push_back(make_pair("local time",text));


            }
            if(value=="weather")
            {
                text = child->GetText();
                lista.push_back(make_pair("weather",text));
            }
            if(value=="temp_c")
            {
                text = child->GetText();
                lista.push_back(make_pair("temperature",text));
            }
             if(value=="relative_humidity")
            {
                text = child->GetText();
                lista.push_back(make_pair("humidity",text));
            }
            if(value=="wind_dir")
            {
                text = child->GetText();
                lista.push_back(make_pair("wind direction",text));
            }
            if(value=="wind_kph")
            {
                text = child->GetText();
                lista.push_back(make_pair("wind speed",text));

            }
            if(value=="pressure_mb")
            {
                text = child->GetText();
                lista.push_back(make_pair("pressure",text));
            }



            if(value=="precip_today_metric")
            {
                text = child->GetText();
                lista.push_back(make_pair("precipitation",text));
            }



            }






    }

}
}
string Conditions::getCondition(string condition)
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

void Conditions::printConditions()
{
    list<pair<string,string>>::iterator it=lista.begin();
    for(it=lista.begin();it!=lista.end();it++)
        cout<<(*it).first<<":  "<<(*it).second<<endl;
}

list<pair<string,string>> Conditions:: conditions()
{
    return lista;
}
}

