#include "../../include/date/date.hpp"
#include "date.hpp"

Date::Date(int day, int month, int year){
  this->day = day;
  this->month = month;
  this->year = year;
}

int Date::compare_to(Date date)
{
  if(this->year < date.year)
    return 1;
  if(this->year > date.year)
    return -1;
  if(this->month < date.month)
    return 1;
  if(this->month > date.month)
    return -1;  
  if(this->day < date. day)
    return 1;
  if(this->day > date.day)
    return -1;
  return 0;
}
