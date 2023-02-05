#include <string>
#include <iostream>
#include "../include/date.hpp"
#include "../include/input-services.hpp"

Date::Date(std::string date){
  std::vector<int> formatted_date = in_service::separate_by_slash(date);
  this->day = formatted_date[0];
  this->month = formatted_date[1];
  this->year = formatted_date[2];
}

//=====================================================//
bool Date::operator>(const Date& date2) const{
  if(this->year < date2.year)
    return true;
  if(this->month < date2.month)
    return true;
  if(this->day < date2.day)
    return true;
  return false;
}

//=====================================================//
bool Date::operator==(const Date& date2) const{
  return this->day == date2.day and
          this->month == date2.month and
          this->year == date2.year;
}

//=====================================================//
int Date::until(const Date &date) const{
  int age = this->year - date.year;
  if(this->month < date.month){
    age--;
    return age;
  }
  if(this->month == date.month){
    if(this->day < date.day){
      age--;
      return age;
    }
  }
  return age;
}
