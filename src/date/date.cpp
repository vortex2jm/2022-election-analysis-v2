#include "../../include/date/date.hpp"
#include "date.hpp"
#include <string>

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


// std::vector<int> date::separate_by_slash(std::string date){

// } 
// Adicionar funcao no input services
