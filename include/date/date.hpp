#ifndef date_h
#define date_h

class Date {

  int day;
  int month;
  int year;

  public:

  Date(int day, int month, int year);
  int compare_to(Date);
};

#endif
