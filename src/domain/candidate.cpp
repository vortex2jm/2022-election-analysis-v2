#include "../../include/domain/candidate.hpp"

//=========================================//
Candidate::Candidate(int nr_candidato, string nm_urna_candidato, string nm_tipo_destino_votos, Date dt_nascimento,
            bool cd_sit_tot_turno, int cd_genero, PoliticalParty * party) : dt_nascimento(dt_nascimento){
    
    this->nr_candidato = nr_candidato;
    this->nm_urna_candidato = nm_urna_candidato;
    this->nm_tipo_destino_votos = nm_tipo_destino_votos;
    this->cd_sit_tot_turno = cd_sit_tot_turno;
    this->cd_genero = cd_genero;
    this->party = party;
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
int Candidate::get_nr_candidato(){
    return this->nr_candidato;
}

//=========================================//
bool Candidate::get_cd_sit_tot_turno(){
    return this->cd_sit_tot_turno;
}

//=========================================//
int Candidate::get_qt_votos(){
    return this->qt_votos;
}

//=========================================//
Date Candidate::get_dt_nascimento(){
    return this->dt_nascimento;
}

//=========================================//
int Candidate::get_cd_genero(){
    return this->cd_genero;
}

//=========================================//
int Candidate::get_elected_position(){
    this->elected_position;
}

//=========================================//
PoliticalParty* Candidate::get_party(){
    return this->party;
}

//=========================================//
string Candidate::get_nm_urna_candidato(){
    return this->nm_urna_candidato;
}

//=========================================//
string Candidate::get_nm_tipo_destino_votos(){
    return this->nm_tipo_destino_votos;
}

//=========================================//
int Candidate::get_geral_position(){
    return this->geral_position;
}
