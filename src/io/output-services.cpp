#include "../../include/io/output-services.hpp"
#include <iostream>
#include <string>

//PESQUISAR SOBRE O NUMBER FORMAT
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

    void output_service::vacancies_number(Election election)
    {

    }

    void output_service::elected_candidates(Election election)
    {

    }
    void output_service::most_voted_candidates(Election election)
    {

    }
    void output_service::harmed_candidates(Election election)
    {

    }

    void output_service::benefited_candidates(Election election)
    {

    }

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