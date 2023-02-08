#include <iostream>
#include <exception>


class fileInputException : public std::exception{
    public:
    const char* what() const throw();
};