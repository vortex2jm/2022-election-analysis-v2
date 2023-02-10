#ifndef date_h
#define date_h
#include <vector>
#include <string>

class Date {

private:

  int day;
  int month;
  int year;

public:

  Date(std::string date);
  std::string to_string() const;
  int until(const Date &date) const;
  bool operator>(const Date& date2) const;
  bool operator==(const Date& date2) const;
};

#endif
