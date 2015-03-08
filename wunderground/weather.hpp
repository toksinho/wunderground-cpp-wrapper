/*
 Weather class is abstract base class.
*/

#ifndef WEATHER_HPP
#define WEATHER_HPP
#include "tinystr.h"
#include "tinyxml.h"
#include <string>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;
class Weather
{
public:
    Weather(std::string key):APIkey(key){}

 /*prints all data in pairs*/

    virtual void printConditions()
    {
        list<pair<string,string>>::iterator it=lista.begin();
        for(it;it!=lista.end();it++)
            cout<<(*it).first<<":  "<<(*it).second<<endl;
    }

/*returns const reference to list with all weather data*/
   virtual  const list<pair<string,string>>& conditions() const
    {
        return lista;
    }

    virtual ~Weather(){}
protected:
        std::string APIkey="";
        std::list<std::pair<std::string,std::string>> lista;
        virtual void loadData(std::string,std::string)=0;
};

#endif // WEATHER_HPP

