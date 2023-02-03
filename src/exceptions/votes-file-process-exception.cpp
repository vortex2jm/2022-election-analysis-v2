#include "votes-file-process-exception.hpp"

const char *votes_file_process_exception::what() const noexcept
{
    return "Falha ao processar arquivo de votação (votacao.csv)";
}