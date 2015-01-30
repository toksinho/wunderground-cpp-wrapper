/*
Astronomy class provides astronomy data for today
*/

#ifndef ASTRONOMY_HPP
#define ASTRONOMY_HPP

#include "weather.hpp"
namespace wunderground
{


class Astronomy:public Weather
{
public:

    Astronomy()=default;
    Astronomy(std::string);
    /*
    load and parse xml file with all weather data
    param city: city name for which you want weather data
    param state: state name
    */
    virtual void loadData(std::string city,std::string state);

     /*conditions() returns whole list of string pairs*/
    std::list<std::pair<std::string,std::string>> conditions();
    /*
    Returns sunset or sunrise time for today e.g.  getCondition("sunset");
    param condition: sunset, sunrise

    */
    std::string getCondition(std::string);
    /*
    prints all data for 10 days in pairs. e.g. sunset 16:21
    */
    void printConditions();

    /*
    all data is saved in this list
    */
    std::list<std::pair<std::string,std::string>> lista;

};
}
#endif // ASTRONOMY_HPP

