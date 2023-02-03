#include "candidates-file-process-exception.hpp"

const char *candidates_file_process_exception::what() const noexcept
{
    return "Falha ao processar arquivo de candidatos (candidatos.csv)";
}