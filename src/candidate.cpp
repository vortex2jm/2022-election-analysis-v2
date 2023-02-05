#include "../include/candidate.hpp"

//=========================================//
Candidate::Candidate(int nr_candidato, string nm_urna_candidato, string nm_tipo_destino_votos, Date dt_nascimento,
            bool cd_sit_tot_turno, int cd_genero, PoliticalParty * party) : dt_nascimento(dt_nascimento){
    
    this->nr_candidato = nr_candidato;
    this->nm_urna_candidato = nm_urna_candidato;
    this->nm_tipo_destino_votos = nm_tipo_destino_votos;
    this->cd_sit_tot_turno = cd_sit_tot_turno;
    this->cd_genero = cd_genero;
    this->party = party;
    this->qt_votos = 0;
}

//=========================================//
void Candidate::set_qt_votos(int qtVotos){
    this->qt_votos += qtVotos;
}

//=========================================//
void Candidate::set_elected_position(int position){
    this->elected_position = position;
}

//=========================================//
void Candidate::set_geral_position(int geralPosition){
    this->geral_position = geralPosition;
}

//=========================================//
int Candidate::get_nr_candidato() const{
    return this->nr_candidato;
}

//=========================================//
bool Candidate::get_cd_sit_tot_turno() const{
    return this->cd_sit_tot_turno;
}

//=========================================//
int Candidate::get_qt_votos() const{
    return this->qt_votos;
}

//=========================================//
Date Candidate::get_dt_nascimento() const{
    return this->dt_nascimento;
}

//=========================================//
int Candidate::get_cd_genero() const{
    return this->cd_genero;
}

//=========================================//
int Candidate::get_elected_position() const{
    return this->elected_position;
}

//=========================================//
PoliticalParty* Candidate::get_party() const{
    return this->party;
}

//=========================================//
string Candidate::get_nm_urna_candidato() const{
    return this->nm_urna_candidato;
}

//=========================================//
string Candidate::get_nm_tipo_destino_votos() const{
    return this->nm_tipo_destino_votos;
}

//=========================================//
int Candidate::get_geral_position() const{
    return this->geral_position;
}

bool Candidate::operator==(const Candidate& cand2) const{
    return this->nr_candidato == cand2.nr_candidato and 
            this->nm_urna_candidato == cand2.nm_urna_candidato and
            this->nm_tipo_destino_votos == cand2.nm_tipo_destino_votos and
            this->dt_nascimento == cand2.dt_nascimento and
            this->cd_sit_tot_turno == cand2.cd_sit_tot_turno and
            this->cd_genero == cand2.cd_genero and
            this->party == cand2.party and
            this->qt_votos == cand2.qt_votos and
            this->elected_position == cand2.elected_position and
            this->geral_position == cand2.geral_position;
}

bool Candidate::operator>(const Candidate& cand2) const{
    if(this->qt_votos == cand2.qt_votos){
        return this->dt_nascimento > cand2.dt_nascimento;
    }
    return this->qt_votos > cand2.qt_votos; 
}
bool Candidate::candidate_pointer_comparator(const Candidate * const a, const Candidate * const b)
{
    return *a > *b;
}
