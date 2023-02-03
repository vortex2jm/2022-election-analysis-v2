#include "votes-file-input-exception.hpp"

const char *votes_file_input_exception::what() const noexcept
{
    return "Falha ao abrir ou encontrar arquivo de votação (votacao.csv)";
}