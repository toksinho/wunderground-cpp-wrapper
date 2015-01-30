#C++ wrapper for Weather Underground API


This is a C++ wrapper for [Weather Underground](http://www.wunderground.com) API.
Compiler: GCC 4.6.4 on Ubuntu and tested with MinGW 4.7.2 on Windows


##Requirements
You need API key to use it. You can get it for free [http://www.wunderground.com/weather/api/](http://www.wunderground.com/weather/api)

libcurl library:[curl.haxx.se/libcurl/](http://curl.haxx.se/libcurl/)

For testing you need [Boost libraries](http://www.boost.org/) Boost.Test and Boost.Date_Time 

##Usage

Wrapper has 6 classes named same as  wunderground api [data features](http://www.wunderground.com/weather/api/d/docs?d=data/index):
All of them inherit from same abstract base class named Weather and all of them are in wunderground namespace.


* Conditions for today weather data 
* Forecast for 3 day weather data
* Forecast10day for 10 day weather
* Hourly for 3 day hourly data
* Hourly10day for 10 day hourly data
* Astronomy  for today astronomy data

###Examples of use
```C++
//only  this one header is what you need for using a wrapper
#include "wunderground.hpp"
#include <iostream>

int main()
{
  string ApiKey="put your api key here";
  
  //Condition class provides weather data for today
  wunderground::Conditions weather(ApiKey);
  
  //method loadData(), as it name says, loads data for specified city and state
  weather.loadData("zagreb","croatia");
  
  //method printConditions prints all weather data 
  weather.printConditions();
  
  //you can get specified weather data with getCondition() method
  std::cout<<"Current temperature in Zagreb is: "<<weather.getCondition("temperature");
  
  //Forecast10day class provides data for next 10 days
  wunderground::Forecast10day weather10day(ApiKey);
  
  weather10day.loadData("paris","france");
  
  /*getCondition() method now needs two parametars: condition and a day, if today is Thursday 15th january and
    you need weather data for Sunday 18th than you do: */
  std::cout<<"Highest temperature for Paris on Sunday: "<<weather10day.getCondition("high","18");
  //...and on Tuesday:
  std::cout<<"Humidity for Paris on Tuesday: "<<weather10day.getCondition("humidity","20");
  
  
  //Astronomy class is for sunrise and sunset time
  wunderground::Astronomy astronomy(ApiKey);
  
  astronomy.loadData("munich","germany");
  
  std::cout<<"Sunset time in Munich today is: "<<astronomy.getCondition("sunset");
  
  
  return 0;
  
}
```
  
##Terms of service

[Weather Underground Terms of Service](http://www.wunderground.com/weather/api/d/terms.html)



  
  
  





