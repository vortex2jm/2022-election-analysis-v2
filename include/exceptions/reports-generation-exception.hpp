#include <exception>
#include <iostream>


class reports_generation_exception : public std::exception{
    
    const char *what() const noexcept override;

};