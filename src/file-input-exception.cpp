#include "../include/file-input-exception.hpp"


const char *fileInputException::what() const throw()
{
    return "Falha ao abrir ou encontrar arquivos de entrada";
}
