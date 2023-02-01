#include "../../include/domain/election.hpp"
#include "../../include/date/date.hpp"

Election::Election(int type, string date) : current_date(date){
    this->type = type;
}

//==============================================================================//
int Election::get_nominal_votes(){
    return this->nominal_votes;
}

//==============================================================================//
int Election::get_legend_votes(){
    return this->legend_votes;
}

//==============================================================================//
int Election::get_type(){
    return this->type;
}

//==============================================================================//
Date Election::get_current_date(){
    return this->current_date;
}

//==================================================//
void Election::set_nominal_votes(int nominal_votes){
    this->nominal_votes += nominal_votes;
}

//==============================================================================//
void Election::set_legend_votes(int legend_votes){
    this->legend_votes += legend_votes;
}

//==============================================================================//
void Election::add_candidate(int nr_candidato, string nm_urna_candidato, string nm_tipo_destino_votos, Date dt_nascimento,
            bool cd_sit_tot_turno, int cd_genero, PoliticalParty * party){

    Candidate * cand = new Candidate(nr_candidato, nm_urna_candidato, nm_tipo_destino_votos, dt_nascimento, cd_sit_tot_turno, cd_genero, party);
    this->candidates.insert(make_pair(nr_candidato, cand));
    party->add_candidate(cand);
}

//==============================================================================//
PoliticalParty* Election::add_partie(int number, string sg, int federation){
    PoliticalParty * p = new PoliticalParty(number, sg, federation);
    this->parties.insert(make_pair(number, p));
    return p;    
}

//==============================================================================//
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

//==============================================================================//
list<Candidate> Election::elected_candidates(){
    list<Candidate> cands;
    for(const auto &item : this->candidates){
        if(item.second->get_cd_sit_tot_turno())
            cands.push_back(*item.second);
    }
    // ORDENAR E SETTAR ELECTED POSITION
    return cands;
}

//==============================================================================//
list<Candidate> Election::get_all_candidates(){
    list<Candidate> cands;
    for(const auto &item : this->candidates){
        cands.push_back(*item.second);
    }
    //ORDENAR E SETTAR GERAL POSITION
    return cands;
}

//==============================================================================//
list<Candidate> Election::get_best_candidates(){
    list<Candidate> cands;
    int x=0;
    for(const auto &item : this->candidates){
        if(x==this->elected_amount() - 1)
            break;
        cands.push_back(*item.second);
        x++;
    }
    //ORDENAR
    return cands;
}

//==============================================================================//
list<Candidate> Election::elected_if_major_election(){
    list<Candidate> cands;
    bool flag;
    for(Candidate c: this->get_best_candidates()){
        flag = true;
        for(Candidate c2: this->elected_candidates()){
            if(c == c2)
                flag = false;
        }
        if(flag){
            cands.push_back(c);
        }
    }
    //ORDENAR
    return cands;
}

//==============================================================================//
list<Candidate> Election::elected_by_proportional(){
    list<Candidate> cands;
    bool flag;
    for(Candidate c: this->elected_candidates()){
        flag = true;
        for(Candidate c2: this->get_best_candidates()){
            if(c == c2)
                flag = false;
        }
        if(flag){
            cands.push_back(c);
        }
    }
    //ORDENAR
    return cands;
}

//==============================================================================//
list<PoliticalParty> Election::get_parties(){
    list<PoliticalParty> parts;
    for(const auto &item : this->parties){
        parts.push_back(*item.second);
    }
    //ORDENAR E SETTAR POSITION
    return parts;
}

//==============================================================================//
list<PoliticalParty> Election::get_parties_ordered_by_candidates(){
    list<PoliticalParty> parts;
    for(PoliticalParty p : this->get_parties()){
        if(p.get_total_votes() > 0 && p.get_candidates_list().size() != 0)
            parts.push_back(p);
    }

    //ORDEAR E SETTAR POSITION
    return parts;
}

//==============================================================================//
int Election::elected_amount_by_age(int start, int end){
    int total = 0;
    int diff = 0;
    for(Candidate c : this->elected_candidates()){
        diff = c.get_dt_nascimento().until(this->current_date);
        if(diff >= start && diff < end){
            total++;
        }
    }
    return total;
}

//==============================================================================//
int Election::elected_men(){
    int total = 0;
    for(Candidate c : this->elected_candidates()){
        if(c.get_cd_genero() == MAN)
            total++;
    }
    return total;
}

//==============================================================================//
int Election::elected_women(){
    int total = 0;
    for(Candidate c : this->elected_candidates()){
        if(c.get_cd_genero() == WOMAN)
            total++;
    }
    return total;
}
