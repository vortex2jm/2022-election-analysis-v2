#include "../include/election.hpp"
#include "../include/date.hpp"
#include <algorithm>

Election::Election(int type, string date) : current_date(date){
    this->type = type;
    this->legend_votes = 0;
    this->nominal_votes = 0;
}

//==============================================================================//
int Election::get_nominal_votes() const{
    return this->nominal_votes;
}

//==============================================================================//
int Election::get_legend_votes() const{
    return this->legend_votes;
}

//==============================================================================//
int Election::get_type() const{
    return this->type;
}

//==============================================================================//
Date Election::get_current_date() const{
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
void Election::add_candidate(int nr_candidato, string nm_urna_candidato, string nm_tipo_destino_votos, Date &dt_nascimento,
                        bool cd_sit_tot_turno, int cd_genero, PoliticalParty * party){

    Candidate * cand = new Candidate(nr_candidato, nm_urna_candidato, nm_tipo_destino_votos, dt_nascimento, cd_sit_tot_turno, cd_genero, party);
    this->candidates.insert(make_pair(nr_candidato, cand));
    party->add_candidate(cand);
}

//==============================================================================//
map<int, Candidate *> Election::get_candidates_map() const
{
    return this->candidates;
}

//==============================================================================//
map<int, PoliticalParty *> Election::get_parties_map() const
{
    return this->parties;
}

//==============================================================================//
map<int, PoliticalParty *> Election::get_legends_candidates_parties() const
{
    return this->legends_candidates_parties;
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
int Election::elected_amount() const{
    int result = 0;
    for(const auto &item : this->candidates){
        if(item.second->get_cd_sit_tot_turno())
            result++;
    }
    return result;
}

//==============================================================================//
list<Candidate> Election::get_all_candidates() const {
    list<Candidate> cands;
    for(const auto &item : this->candidates){
        cands.push_back(*item.second);
    }

    cands.sort(std::greater<Candidate>());

    int x=1;
    for(Candidate &c : cands){
        c.set_geral_position(x);
        x++;
    }
    return cands;
}

//==============================================================================//
list<Candidate> Election::elected_candidates() const{
    list<Candidate> cands;
    for(Candidate c : this->get_all_candidates()){
        if(c.get_cd_sit_tot_turno())
            cands.push_back(c);
    }

    cands.sort(std::greater<Candidate>());
    int x=1;
    for(Candidate &c : cands){
        c.set_elected_position(x);
        x++;
    }
    return cands;
}

//==============================================================================//
list<Candidate> Election::get_best_candidates() const{
    list<Candidate> cands;
    int x=0;
    for(Candidate c : this->get_all_candidates()){
        if(x == this->elected_amount())
            break;
        cands.push_back(c);
        x++;
    }
    cands.sort(std::greater<Candidate>());
    return cands;
}

//==============================================================================//
list<Candidate> Election::elected_if_major_election() const{
    list<Candidate> cands;
    list<Candidate> best_candidates = this->get_best_candidates();
    list<Candidate> elected_candidates = this->elected_candidates();

    //if candidate is one of the most voted...
    for(Candidate c: best_candidates){
        //AND is NOT elected...
        if(!count(elected_candidates.begin(), elected_candidates.end(), c)){
            //he/she would be elected in a major election
            cands.push_back(c);
        }
    }
    cands.sort(std::greater<Candidate>());
    return cands;
}

//==============================================================================//
list<Candidate> Election::elected_by_proportional() const{
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
    cands.sort(std::greater<Candidate>());
    return cands;
}

//==============================================================================//
list<PoliticalParty> Election::get_parties() const{
    list<PoliticalParty> parts;
    for(const auto &item : this->parties){
        parts.push_back(*item.second);
    }

    parts.sort(std::greater<PoliticalParty>());
    int x = 1;
    for(PoliticalParty &p : parts){
        p.set_position(x);
        x++;
    }
    return parts;
}

//==============================================================================//
list<PoliticalParty> Election::get_parties_ordered_by_candidates() const{
    list<PoliticalParty> parts;
    for(PoliticalParty p : this->get_parties()){
        if(p.get_total_votes() > 0 && p.get_candidates_list().size() != 0)
            parts.push_back(p);
    }

    parts.sort(PoliticalParty::party_comparator_by_candidate);
    int x = 1;
    for(PoliticalParty &p : parts){
        p.set_position(x);
        x++;
    }
    return parts;
}

//==============================================================================//
int Election::elected_amount_by_age(int start, int end) const{
    int total = 0;
    int diff = 0;
    list<Candidate> electeds = this->elected_candidates();

    for(Candidate c : electeds){
        diff = c.get_dt_nascimento().until(this->current_date);

        if(diff >= start && diff < end){
            total++;
        }
    }
    return total;
}

//==============================================================================//
int Election::elected_men() const{
    int total = 0;
    for(Candidate c : this->elected_candidates()){
        if(c.get_cd_genero() == MAN)
            total++;
    }
    return total;
}

//==============================================================================//
int Election::elected_women() const{
    int total = 0;
    for(Candidate c : this->elected_candidates()){
        if(c.get_cd_genero() == WOMAN)
            total++;
    }
    return total;
}

//==============================================================================//
Election::~Election(){
    for(auto &item : this->candidates){
        delete item.second;
    }
    for(auto &item : this->parties){
        delete item.second;
    }
}
