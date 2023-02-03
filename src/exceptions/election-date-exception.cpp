#include "election-date-exception.hpp"

const char *election_date_exception::what() const noexcept
{
    return "Falha ao gerar data da eleição";
}