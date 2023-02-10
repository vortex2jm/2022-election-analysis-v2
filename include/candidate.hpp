#ifndef CANDIDATE_H
#define CANDIDATE_H

#include <iostream>
#include <string>
#include "./political-party.hpp"
#include "./date.hpp"

using std::string;

class PoliticalParty;
class Date;

class Candidate
{

private:
    int qt_votos;
    int cd_genero;
    int nr_candidato;
    int geral_position;
    int elected_position;
    bool cd_sit_tot_turno;
    string nm_urna_candidato;
    string nm_tipo_destino_votos;

    Date dt_nascimento;
    PoliticalParty* party;

public:
    Candidate(int nr_candidato, string nm_urna_candidato, string nm_tipo_destino_votos, Date &dt_nascimento,
            bool cd_sit_tot_turno, int cd_genero, PoliticalParty * party);

    int get_qt_votos() const;
    int get_cd_genero() const;
    int get_nr_candidato() const;
    int get_geral_position() const;
    int get_elected_position() const;

    void set_qt_votos(int qtVotos);
    void set_elected_position(int position);
    void set_geral_position(int geralPosition);

    bool get_cd_sit_tot_turno() const;
    bool operator>(const Candidate& cand2) const;
    bool operator==(const Candidate& cand2) const;
    static bool candidate_comparator(const Candidate * const a, const Candidate * const b);
    
    string get_nm_urna_candidato() const;
    string get_nm_tipo_destino_votos() const;

    Date get_dt_nascimento() const;
    PoliticalParty * get_party() const;
};

#endif
