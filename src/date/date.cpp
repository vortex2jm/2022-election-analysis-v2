#include "../../include/date/date.hpp"
#include <string>

Date::Date(std::string date){
  std::vector<int> formatted_date = date::separate_by_slash(date);
  this->day = formatted_date[0];
  this->month = formatted_date[1];
  this->year = formatted_date[2];
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

std::vector<int> date::separate_by_slash(std::string date){

  int day = stoi(date.substr(0,1));
  int month = stoi(date.substr(3,4));
  int year = stoi(date.substr(6,7));

  std::vector<int> separated_date;
  separated_date.push_back(day);
  separated_date.push_back(month);
  separated_date.push_back(year);

  return separated_date;
} 
// Adicionar funcao no input services
