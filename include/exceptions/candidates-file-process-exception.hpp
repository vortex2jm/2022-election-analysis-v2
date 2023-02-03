#include <exception>
#include <iostream>


class candidates_file_process_exception : public std::exception{
    
    const char *what() const noexcept override;

};