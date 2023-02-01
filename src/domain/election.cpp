#include "../../include/domain/election.hpp"
#include "../../include/date/date.hpp"

Election::Election(int type, string date) : current_date(date){
    this->type = type;
}

int Election::get_nominal_votes(){
    return this->nominal_votes;
}

int Election::get_legend_votes(){
    return this->legend_votes;
}

int Election::get_type(){
    return this->type;
}

Date Election::get_current_date(){
    return this->current_date;
}

//==================================================//
void Election::set_nominal_votes(int nominal_votes){
    this->nominal_votes += nominal_votes;
}

void Election::set_legend_votes(int legend_votes){
    this->legend_votes += legend_votes;
}

void Election::set_parties(map<int, PoliticalParty> parties){
    // TODO
}

void Election::add_candidate(int nr_candidato, string nm_urna_candidato, string nm_tipo_destino_votos, Date dt_nascimento,
            bool cd_sit_tot_turno, int cd_genero, PoliticalParty * party){

    Candidate * cand = new Candidate(nr_candidato, nm_urna_candidato, nm_tipo_destino_votos, dt_nascimento, cd_sit_tot_turno, cd_genero, party);
    this->candidates.insert(make_pair(nr_candidato, cand));
    party->add_candidate(cand);
}

PoliticalParty* Election::add_partie(int number, string sg, int federation){
    PoliticalParty * p = new PoliticalParty(number, sg, federation);
    this->parties.insert(make_pair(number, p));
    return p;    
}

void Election::add_legends_candidates_parties(int key, PoliticalParty * value){
    this->legends_candidates_parties.insert(make_pair(key, value));
}

//==============================================================================//
int Election::elected_amount(){
    int result = 0;
    for(const auto &item : this->candidates){
        if(item.second->get_cd_sit_tot_turno())
            result++;
    }
    return result;
}
