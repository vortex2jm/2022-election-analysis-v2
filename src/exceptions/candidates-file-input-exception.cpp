#include "candidates-file-input-exception.hpp"

const char *candidates_file_input_exception::what() const noexcept
{
    return "Falha ao abrir ou encontrar arquivo de candidatos (candidatos.csv)";
}