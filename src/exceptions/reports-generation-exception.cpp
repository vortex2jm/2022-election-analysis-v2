#include "reports-generation-exception.hpp"

const char *reports_generation_exception::what() const noexcept
{
    return "Erro no processamento de saída";
}