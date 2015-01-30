#define BOOST_TEST_MODULE weatherTest
#include <boost/test/included/unit_test.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/gregorian/greg_weekday.hpp>
#include <iostream>
#include "wunderground.hpp"

BOOST_AUTO_TEST_SUITE ( test_wrapper )

std::string APIkey = "put your api key here";

BOOST_AUTO_TEST_CASE( test_conditions_day )
{
//check is it day from current conditions same as today
wunderground::Conditions curren(APIkey);
curren.loadData("zagreb","croatia");
boost::gregorian::date d = boost::gregorian::day_clock::universal_day();
boost::gregorian::greg_weekday wd(d.day_of_week());
std::string now = wd.as_short_string();
std::string time = curren.getCondition("local time");
std::string today = time.substr(0,3);


BOOST_CHECK_EQUAL(today,now);

}

boost::test_tools::predicate_result validate_list_conditions(std::list<std::pair<std::string,std::string>>& L1)
{
  std::list<std::pair<std::string,std::string>>::iterator it1 = L1.begin( );
  for (; it1 != L1.end( ); ++it1)
   {
     if ((*it1).first=="pressure") return true;
   }
  return false;
}
BOOST_AUTO_TEST_CASE( test_conditions_list)
{

//check does pressure is in list that has all data
wunderground::Conditions curren(APIkey);
curren.loadData("zagreb","croatia");
auto lista = curren.conditions();

BOOST_CHECK(validate_list_conditions(lista));

}

BOOST_AUTO_TEST_CASE( test_forecast_day )
{
//it will check does thursday exist in file, just change d, or thursday
wunderground::Forecast curren(APIkey);
curren.loadData("zagreb","croatia");
boost::gregorian::date d(2015, 1, 22);
boost::gregorian::greg_weekday wd(d.day_of_week());
std::string now = wd.as_long_string();
std::string today = curren.getCondition("day","Thursday");

BOOST_CHECK_MESSAGE(today==now,"day doesn't exist in downloaded data");

}


BOOST_AUTO_TEST_CASE( test_forecast_size )
{
//size should be 36, 4 days * 9 weather data(.g. day, temperature, humidity etc.)
wunderground::Forecast curren(APIkey);
curren.loadData("zagreb","croatia");
auto lista = curren.conditions();

BOOST_CHECK_MESSAGE(lista.size()==36,"Size is not 36! Check is file downloaded");

}





boost::test_tools::predicate_result validate_list_hourly(std::list<std::pair<std::string,std::string>>& L1)
{
  std::list<std::pair<std::string,std::string>>::iterator it1 = L1.begin( );
  for (; it1 != L1.end( ); ++it1)
   {
     if ((*it1).first=="temperature") return true;
   }
  return false;
}


BOOST_AUTO_TEST_CASE( test_hourly_list)
{

//check does temperature is in list that has all data
wunderground::Hourly curren(APIkey);
curren.loadData("zagreb","croatia");
auto lista = curren.conditions();

BOOST_CHECK(validate_list_hourly(lista));

}



BOOST_AUTO_TEST_SUITE_END( )

