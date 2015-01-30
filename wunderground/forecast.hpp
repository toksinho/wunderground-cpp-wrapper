/*
 Forecast class provides weather conditions for 3 next days
*/

#ifndef FORECAST_HPP
#define FORECAST_HPP

#include "weather.hpp"
namespace wunderground
{

class Forecast:public Weather
{
public:
    Forecast()=default;
    Forecast(std::string);

    /*
    load and parse xml file with all weather data
    param city: city name for which you want weather data
    param state: state name
    */
    virtual void loadData(std::string city,std::string state);

    std::list<std::pair<std::string ,std::string>> conditions();
    /*
    Returns specified condition for specified day  e.g.  getCondition("temperature","monday");
    param condition: high temperature, low temperature, weather, precipitation, wind speed, wind direction, humidity
    param day: one of 7 weekdays
    */
    std::string getCondition(std::string condition,std::string day);

    /*
    prints all data for 3 days in pairs. e.g. weather clear
    */
    void printConditions();

    /*
    all data is saved in this list
    */
    std::list<std::pair<std::string,std::string>> lista;


};
}
#endif // FORECAST_HPP



