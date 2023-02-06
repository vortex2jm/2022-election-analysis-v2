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
  int until(const Date &date) const;
  std::string toString() const;
  bool operator==(const Date& date2) const;
  bool operator>(const Date& date2) const;
};

#endif
