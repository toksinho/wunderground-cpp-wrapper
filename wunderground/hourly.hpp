
/*
 Hourly class provides hourly weather conditions for 3 next days
*/


#ifndef HOURLY_HPP
#define HOURLY_HPP

#include "weather.hpp"
namespace wunderground
{

class Hourly:public Weather
{
public:
    Hourly()=default;
    Hourly(std::string);
    /*
    load and parse xml file with all weather data
    param city: city name for which you want weather data
    param state: state name
    */
    virtual void loadData(std::string,std::string);


    std::list<std::pair<std::string,std::string>> conditions() const;

    /*
    Returns condition value as string for given day in month and hour  e.g.  getCondition("temperature","January 5","14");
    param condition: temperature, condition, humidity, wind speed, wind direction, pressure, precipitation
    param day: month name + day e.g February 7, january 4 (capital letter not necessary)
    */
    std::string getCondition(std::string condition,std::string day,std::string hour)const;

    /*
    prints all data for every hour in next 3 days in pairs
    */
    void printConditions();

    /*
    all data is saved in this list
    */
    std::list<std::pair<std::string,std::string>> lista;


};
}
#endif // HOURLY_HPP
