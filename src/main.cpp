#include "../include/candidate.hpp"
#include "../include/political-party.hpp"
#include "../include/election.hpp"
#include "../include/input-services.hpp"
#include "../include/output-services.hpp"
#include "../include/date.hpp"
#include "../include/file-input-exception.hpp"

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

    // Entrada de dados
    ifstream stream_candidates, stream_votes;

    try{
        stream_candidates = in_service::create_reading_stream(argv[2]);
        stream_votes = in_service::create_reading_stream(argv[3]);
    } catch(const fileInputException& e){
        std::cerr <<  e.what() << endl;
    }

    // Instanciando a eleição
    Election election = Election(type, argv[4]);

    // Processando os dados de entrada
    in_service::process_candidates_file(stream_candidates, election);
    in_service::process_votes_file(stream_votes, election);
    stream_candidates.close();
    stream_votes.close();
    
    // Gerando a saída
    out_services::generate_reports(election);

    return 0;
}
