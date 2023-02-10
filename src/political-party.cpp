#include "../include/political-party.hpp"

PoliticalParty::PoliticalParty(int number, string sg, int federation){
    this->number = number;
    this->sg = sg;
    this->federation = federation;
    this->legend_votes = 0;
}

//=====================================================================//
bool PoliticalParty::operator>(const PoliticalParty &party2) const
{
    int own_total = this->legend_votes + this->get_nominal_votes();
    int other_total = party2.legend_votes + party2.get_nominal_votes();

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

//=====================================================================//
bool PoliticalParty::party_comparator_by_candidate(const PoliticalParty &p1, const PoliticalParty &p2) {
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

//=====================================================================//
string PoliticalParty::get_sg() const{
    return this->sg;
}

//=====================================================================//
int PoliticalParty::get_legend_votes() const{
    return this->legend_votes;
}

//=====================================================================//
int PoliticalParty::get_federation() const{
    return this->federation;
}

//=====================================================================//
int PoliticalParty::get_number() const{
    return this->number;
}

//=====================================================================//
int PoliticalParty::get_position() const{
    return this->position;
}

//=====================================================================//
int PoliticalParty::get_total_votes() const{
    return this->legend_votes + get_nominal_votes();
}

//=====================================================================//
void PoliticalParty::set_legend_votes(int legend_votes){
    this->legend_votes += legend_votes;
}

//=====================================================================//
void PoliticalParty::add_candidate(Candidate* candidate){
    this->candidates_list.push_back(candidate);
}

//=====================================================================//
void PoliticalParty::set_position(int position){
    this->position = position;
}

//=====================================================================//
list<Candidate*> PoliticalParty::get_candidates_list() const{
    list<Candidate*> result = this->candidates_list;
    result.sort(Candidate::candidate_comparator);
    return result;
}

//=====================================================================//
int PoliticalParty::get_nominal_votes() const{
    int total=0;
    for(Candidate* c : this->candidates_list){
        total += c->get_qt_votos();
    }
    return total;
}

//=====================================================================//
int PoliticalParty::get_elected_amount() const{
    int amount=0;
    for(Candidate* c : this->candidates_list){
        if(c->get_cd_sit_tot_turno()){
            amount++;
        }
    }
    return amount;
}

//=====================================================================//
Candidate PoliticalParty::most_voted_candidate() const{
    list<Candidate*> ordered_list = this->candidates_list;
    ordered_list.sort(Candidate::candidate_comparator);
    return *ordered_list.front();
}

//=====================================================================//
Candidate PoliticalParty::least_voted_candidate() const{
    list<Candidate*> ordered_list = this->candidates_list;
    ordered_list.sort(Candidate::candidate_comparator);
    return *ordered_list.back();
}
