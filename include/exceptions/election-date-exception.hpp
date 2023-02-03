#include <exception>
#include <iostream>


class election_date_exception : public std::exception{
    
    const char *what() const noexcept override;

};