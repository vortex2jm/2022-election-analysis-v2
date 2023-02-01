#ifndef date_h
#define date_h
#include <vector>

class Date {

  int day;
  int month;
  int year;

  public:

  Date(std::string date);
  int compare_to(Date);
  int until(Date);
  bool operator==(const Date& date2) const;
};

namespace date{
  std::vector<int> separate_by_slash(std::string date); 
}
// Adicionar este método no arquivo de inputservices

#endif
