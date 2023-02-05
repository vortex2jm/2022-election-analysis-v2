#include "../include/political-party.hpp"

//constructor
PoliticalParty::PoliticalParty(int number, string sg, int federation){

}

bool PoliticalParty::operator>(const PoliticalParty party2) const
{
    int own_total = this->legendVotes + this->get_nominal_votes();
    int other_total = party2.legendVotes + party2.get_nominal_votes();

    if (own_total > other_total)
      return true;
    if (own_total < other_total)
      return false;
    if (this->number < party2.number)
      return true;
    if (this->number > party2.number)
      return false;
    return false;
}

bool PoliticalParty::party_comparator_by_candidate(PoliticalParty &p1, PoliticalParty &p2) {
    if(p1.most_voted_candidate().get_qt_votos() > p2.most_voted_candidate().get_qt_votos())
        return true;

    if(p1.most_voted_candidate().get_qt_votos() == p2.most_voted_candidate().get_qt_votos()){
        if(p1.most_voted_candidate().get_dt_nascimento() > p2.most_voted_candidate().get_dt_nascimento())
            return true;
        
        if(p1.most_voted_candidate().get_party()->get_number() < p2.most_voted_candidate().get_party()->get_number())
            return true;
    }
    return false;
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
    return this->legendVotes + get_nominal_votes();
}
// ======================Setters==================================//

void PoliticalParty::set_legend_votes(int legendVotes){
    this->legendVotes += legendVotes;
}
void PoliticalParty::add_candidate(Candidate* candidate){
    this->candidatesList.push_back(candidate);
}
//TODO
void PoliticalParty::set_position(int position){
    this->position = position;
}
// ======================other get methods======================//

/**
 * @return Lista de candidatos do partido, ordenados
 */
//ISTO FUNCIONA?
list<Candidate*> PoliticalParty::get_candidates_list(){
    list<Candidate*> result = this->candidatesList;
    result.sort(Candidate::candidate_pointer_comparator);
    return result;
}

/**
 * @return número de votos nominais
 */
int PoliticalParty::get_nominal_votes() const{
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
    list<Candidate*> ordered_list = this->candidatesList;
    ordered_list.sort(Candidate::candidate_pointer_comparator);
    return *ordered_list.front();
}

/**
 * @return o candidato menos votado do partido
 */
Candidate PoliticalParty::least_voted_candidate(){
    list<Candidate*> ordered_list = this->candidatesList;
    ordered_list.sort(Candidate::candidate_pointer_comparator);
    return *ordered_list.back();
}