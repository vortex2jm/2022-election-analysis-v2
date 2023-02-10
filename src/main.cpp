#include "../include/candidate.hpp"
#include "../include/political-party.hpp"
#include "../include/election.hpp"
#include "../include/input-services.hpp"
#include "../include/output-services.hpp"
#include "../include/date.hpp"
#include "../include/file-input-exception.hpp"

using std::cout;

int main(int argc, char const *argv[])
{
    int type;
    string estadual_check = "--estadual";
    string federal_check = "--federal";

    if (argv[1] == estadual_check)
        type = 7;
    else if (argv[1] == federal_check)
        type = 6;
    else
        exit(1);

    // Instanciando a eleição
    Election election = Election(type, argv[4]);

    // Processando os dados de entrada
    in_service::process_candidates_file(argv[2], election);

    // cout << "PROCESSANDO ARQUIVO DE VOTOS" << endl;
    in_service::process_votes_file(argv[3], election);
    
    // Gerando a saída
    out_services::generate_reports(election);

    return 0;
}
