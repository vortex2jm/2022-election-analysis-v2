#include "../include/candidate.hpp"
#include "../include/political-party.hpp"
#include "../include/election.hpp"
#include "../include/input-services.hpp"
#include "../include/output-services.hpp"
#include "../include/date.hpp"

using std::exception;

int main(int argc, char const *argv[])
{
    int type;
    string estadual_check = "--estadual";
    string federal_check = "--federal";

    if (argv[0] == estadual_check)
        type = 7;
    else if (argv[0] == federal_check)
        type = 6;
    else
        throw exception();

    // Criando buffer de entrada dos arquivos
    ifstream stream_candidates, buffer_votes;
    try {
        stream_candidates = in_service::create_reading_stream(argv[1]);
    } catch (exception& e) {
        throw exception();
    }
    try {
        buffer_votes = in_service::create_reading_stream(argv[2]);
    } catch (exception& e) {
        throw exception();
    }

    // Instanciando a eleição
    Election* election = new Election(type, argv[3]);

    try {
        // Processando os dados de entrada
        in_service::process_candidates_file(stream_candidates, *election);
        in_service::process_votes_file(buffer_votes, *election);

        // Gerando a saída
        out_services::generate_reports(*election);
    } catch (exception& e) {
        throw e;
    }
    return 0;
}