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

    
    /*
    Returns specified condition for specified day  e.g.  getCondition("temperature","monday");
    param condition: high temperature, low temperature, weather, precipitation, wind speed, wind direction, humidity
    param day: one of 7 weekdays
    */
    std::string getCondition(std::string condition,std::string day);


};
}
#endif // FORECAST_HPP



