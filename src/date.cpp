#include <string>
#include <iostream>
#include "../include/date.hpp"
#include "../include/input-services.hpp"

Date::Date(string date){
  vector<string> formatted_date = in_service::split(date, '/');

  this->day = stoi(formatted_date[0]);
  this->month = stoi(formatted_date[1]);
  this->year = stoi(formatted_date[2]);
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
int Date::until(const Date& date) const{
  int age = this->year - date.year;
  if(this->month < date.month){
    age--;
  }
  else if(this->month == date.month){
    if(this->day < date.day){
      age--;
    }
  }
  return age;
}

string Date::toString() const
{
  string a = to_string(this->day) + '/' + to_string(this->month) + '/' + to_string(this->year);
  return a;
}
