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
        std::cout << "Votação dos partidos e número de candidatos eleitos:" << std::endl;

        std::string vot, nom, cand, ele;
        for(PoliticalParty p : election.get_parties()){
            vot = "voto";
            nom = "nominal";
            cand = "candidato";
            ele = "eleito";

            vot = plural_singular_filter(vot, p.get_total_votes());
            nom = plural_singular_filter(nom, p.get_nominal_votes());
            cand = plural_singular_filter(cand, p.get_elected_amount());
            ele = plural_singular_filter(ele, p.get_elected_amount());

            std::cout << p.get_position() << " - ";
            std::cout.imbue(std::locale("pt_BR.utf8"));
            std::cout << p.get_sg() << " - " << p.get_number() << ", " << p.get_total_votes() << " " << vot
            << " (" << p.get_nominal_votes() << " " << nom <<  " e " << p.get_legend_votes() << " de legenda), "
            << p.get_elected_amount() << " " << cand << " " << ele << std::endl;
 
            std::cout.imbue(std::locale("C"));
        }
    }

    //====================================================================//
    void output_service::first_and_last_candidates_from_parties(Election election)
    {
        std::cout << "Primeiro e último colocados de cada partido:" << std::endl;

        std::string most_vot, least_vot;

        for(PoliticalParty p : election.get_parties_ordered_by_candidates()){

            most_vot = "voto";
            least_vot = "voto";
            most_vot = plural_singular_filter(most_vot, p.most_voted_candidate().get_qt_votos());
            least_vot = plural_singular_filter(least_vot, p.least_voted_candidate().get_qt_votos());

            std::cout << p.get_position() << " - " << p.get_sg() << " - " << p.get_number() << ", " 
            << p.most_voted_candidate().get_nm_urna_candidato() << " (" << p.most_voted_candidate().get_nr_candidato();

            std::cout.imbue(std::locale("pt_BR.utf8"));
            std::cout << ", " << p.most_voted_candidate().get_qt_votos() << " " << most_vot << ") / ";
            std::cout.imbue(std::locale("C"));
            std::cout << p.least_voted_candidate().get_nm_urna_candidato() << " (" << p.least_voted_candidate().get_nr_candidato();
            std::cout.imbue(std::locale("pt_BR.utf8"));
            std::cout << ", " << p.least_voted_candidate().get_qt_votos() << " " << least_vot << ")" << std::endl;
            std::cout.imbue(std::locale("C"));
        }
        std::cout << std::endl;
    }

    //====================================================================//
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
