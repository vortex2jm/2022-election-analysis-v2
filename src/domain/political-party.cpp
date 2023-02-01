#include "../../include/domain/political-party.hpp"

//constructor
PoliticalParty::PoliticalParty(int number, string sg, int federation){

}
// ======================Getters==================================//

string PoliticalParty::get_sg(){
    return this->sg;
}
int PoliticalParty::get_legend_votes(){
    return this->legendVotes;
}
int PoliticalParty::get_federation(){
    return this->federation;
}
int PoliticalParty::get_number(){
    return this->number;
}
int PoliticalParty::get_position(){
    return this->position;
}
int PoliticalParty::get_total_votes(){
    //TODO
}
// ======================Setters==================================//

void PoliticalParty::set_legend_votes(int legendVotes){
    this->legendVotes += legendVotes;
}
void PoliticalParty::add_candidate(Candidate* candidate){
    this->candidatesList.push_back(candidate);
    return;
}
//TODO
void PoliticalParty::set_position(int position){
    this->position = position;
}
// ======================other get methods======================//

/**
 * @return Lista de candidatos do partido, ordenados
 */
list<Candidate*> PoliticalParty::get_candidates_list(){
    //TODO
}

/**
 * @return número de votos nominais
 */
int PoliticalParty::get_nominal_votes(){
    int total=0;
    for(Candidate* c : this->candidatesList){
        total += c->get_qt_votos();
    }
    return total;
}

/**
 * @return a quantidade de candidatos do partido que foram eleitos
 */
int PoliticalParty::get_elected_amount(){
    int amount=0;
    for(Candidate* c : this->candidatesList){
        if(c->get_cd_sit_tot_turno()){
            amount++;
        }
    }
    return amount;
}

/**
 * @return o candidato mais votado do partido
 */
Candidate PoliticalParty::most_voted_candidate(){
    //TODO
}

/**
 * @return o candidato menos votado do partido
 */
Candidate PoliticalParty::least_voted_candidate(){
    //TODO
}
