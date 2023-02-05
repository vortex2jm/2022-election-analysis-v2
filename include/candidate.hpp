#ifndef CANDIDATE_H
#define CANDIDATE_H

#include <iostream>
#include <string>
#include "./political-party.hpp"
#include "./date.hpp"

using namespace std;

class PoliticalParty;

class Candidate
{

private:
    int nr_candidato;
    string nm_urna_candidato;
    string nm_tipo_destino_votos;
    Date dt_nascimento;
    bool cd_sit_tot_turno;
    int cd_genero;
    PoliticalParty * party;
    int qt_votos;
    int elected_position;
    int geral_position;

public:
    Candidate(int nrCandidato, string nmUrnaCandidato, string nmTipoDestinoVotos, Date dtNascimento,
            bool cdSitTotTurno, int cdGenero, PoliticalParty * party);
    // ===============Setters================================================//
    void set_qt_votos(int qtVotos);
    void set_elected_position(int position);
    void set_geral_position(int geralPosition);

    // ===============Getters================================================//
    int get_nr_candidato();
    bool get_cd_sit_tot_turno();
    int get_qt_votos();
    Date get_dt_nascimento();
    int get_cd_genero();
    int get_elected_position();
    PoliticalParty * get_party();
    string get_nm_urna_candidato();
    string get_nm_tipo_destino_votos();
    int get_geral_position();
    bool operator==(const Candidate& cand2) const;
    bool operator>(const Candidate& cand2) const;
    static bool candidate_pointer_comparator(const Candidate *a, const Candidate *b);
};

#endif
