/*
 Forecast10day class provides weather for 10 next days
*/
#ifndef FORECAST10DAY_HPP
#define FORECAST10DAY_HPP

#include "weather.hpp"

namespace wunderground
{

class Forecast10day:public Weather
{
public:

    Forecast10day()=default;
    Forecast10day(std::string);

    /*
    load and parse xml file with all weather data
    param city: city name for which you want weather data
    param state: state name
    */
    virtual void loadData(std::string city,std::string state);


    /*
    Returns specific condition for specified day of month, e.g. wind direction for 8th day of the month getCondition("wind direction","8");
    @param condition: high, low, humidity, wind speed, wind direction, precipitation, snow
    @param date: day in week, if today is 14th january then some number between 14 and 23.
    */

    std::string getCondition(std::string condition,std::string date)const;

};
}
#endif // FORECAST10DAY_HPP

