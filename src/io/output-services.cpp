#include "../../include/io/output-services.hpp"
#include <iostream>
#include <string>

//VERIFICAR SE PRECISA SETTAR O LOCALE PARA C
namespace output_service{

    void generate_reports(Election election);

    //private methods=============//
    void vacancies_number(Election election);
    void elected_candidates(Election election);
    void most_voted_candidates(Election election);
    void harmed_candidates(Election election);
    void benefited_candidates(Election election);
    void party_voting_and_elected_candidates(Election election);
    void first_and_last_candidates_from_parties(Election election);
    void elected_by_age(Election election);
    void elected_by_gender(Election election);
    void all_voting(Election election);
    string plural_singular_filter(string out, int value);

//public methods==============//

//====================================================================//

    void output_service::generate_reports(Election election) 
    {

    }

    //====================================================================//
    void output_service::vacancies_number(Election election)
    {
        std::cout.imbue(std::locale("pt_BR.utf8"));
        std::cout << "Número de vagas: " << election.elected_amount() << std::endl;
        std::cout.imbue(std::locale("C"));
    }

    //====================================================================//
    void output_service::elected_candidates(Election election)
    {
        std::string category = "";
        if(election.get_type() == 6)
            category = "federais";
        else if(election.get_type() == 7)
            category = "estaduais";

        std::cout << "Deputados " << category <<" eleitos:" << std::endl;
        std::string vot;

        for(Candidate c : election.elected_candidates()){
            std::cout << c.get_elected_position() << " - ";
            if(c.get_party()->get_federation() != -1)
                std::cout << "*";
            
            vot = "voto";
            vot = plural_singular_filter(vot, c.get_qt_votos());
            std::cout << c.get_nm_urna_candidato() << " (" << c.get_party()->get_sg() << ", ";

            std::cout.imbue(std::locale("pt_BR.utf8"));
            std::cout << c.get_qt_votos() << " " << vot << ")" << std::endl;
            std::cout.imbue(std::locale("C"));
        }
        std::cout << std::endl;
    }

    //====================================================================//
    void output_service::most_voted_candidates(Election election)
    {
        std::cout << "Candidatos mais votados (em ordem decrescente de votação e respeitando número de vagas):" << std::endl;

        std::string vot;
        for(Candidate c : election.get_best_candidates()){
             std::cout << c.get_geral_position() << " - ";
             if(c.get_party()->get_federation() != -1)
                std::cout << "*";

            vot = "voto";
            vot = plural_singular_filter(vot, c.get_qt_votos());
            std::cout << c.get_nm_urna_candidato() << " (" << c.get_party()->get_sg() << ", ";
            
            std::cout.imbue(std::locale("pt_BR.utf8"));
            std::cout << c.get_qt_votos() << " " << vot << ")" << std::endl;
            std::cout.imbue(std::locale("C"));
        }
        std::cout << std::endl;
    }

    //====================================================================//
    void output_service::harmed_candidates(Election election)
    {
        std::cout << "Teriam sido eleitos se a votação fosse majoritária, e não foram eleitos:" << std::endl;
        std::cout << "(com sua posição no ranking de mais votados)" << std::endl;

        std::string vot;
        for(Candidate c : election.elected_if_major_election()){
            std::cout << c.get_geral_position() << " - ";
            if(c.get_party()->get_federation() != -1)
                std::cout << "*";

            vot = "voto";
            vot = plural_singular_filter(vot, c.get_qt_votos());
            std::cout << c.get_nm_urna_candidato() << " (" << c.get_party()->get_sg() << ", ";
            
            std::cout.imbue(std::locale("pt_BR.utf8"));
            std::cout << c.get_qt_votos() << " " << vot << ")" << std::endl;
            std::cout.imbue(std::locale("C"));
        }
        std::cout << std::endl;
    }

    //====================================================================//
    void output_service::benefited_candidates(Election election)
    {
        std::cout << "Eleitos, que se beneficiaram do sistema proporcional:" << std::endl;
        std::cout << "(com sua posição no ranking de mais votados)" << std::endl;

        std::string vot;

        for(Candidate c : election.elected_by_proportional()){
            std::cout << c.get_geral_position() << " - ";
            if(c.get_party()->get_federation() != -1)
                std::cout << "*";

            vot = "voto";
            vot = plural_singular_filter(vot, c.get_qt_votos());
            std::cout << c.get_nm_urna_candidato() << " (" << c.get_party()->get_sg() << ", ";
            
            std::cout.imbue(std::locale("pt_BR.utf8"));
            std::cout << c.get_qt_votos() << " " << vot << ")" << std::endl;
            std::cout.imbue(std::locale("C"));
        }
        std::cout << std::endl;
    }

    //====================================================================//
    void output_service::party_voting_and_elected_candidates(Election election)
    {

    }

    void output_service::first_and_last_candidates_from_parties(Election election)
    {

    }

    void output_service::elected_by_age(Election election)
    {

    }

    void output_service::elected_by_gender(Election election)
    {

    }

    void output_service::all_voting(Election election)
    {

    }

    string output_service::plural_singular_filter(string out, int value)
    {
        return string();
    }
}
