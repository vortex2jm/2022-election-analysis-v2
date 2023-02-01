#ifndef CANDIDATE_H
#define CANDIDATE_H

#include <iostream>
#include <ctime>
#include "./political-party.hpp"
#include "../date/date.hpp"

using namespace std;

class Candidate
{

private:
    int nrCandidato;
    string nmUrnaCandidato;
    string nmTipoDestinoVotos;
    Date dtNascimento;
    bool cdSitTotTurno;
    int cdGenero;
    PoliticalParty party;
    int qtVotos;
    int electedPosition;
    int geralPosition;

public:
    Candidate(int nrCandidato, string nmUrnaCandidato, string nmTipoDestinoVotos, Date dtNascimento,
            bool cdSitTotTurno, int cdGenero, PoliticalParty party);
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
    PoliticalParty get_party();
    string get_nm_urna_candidato();
    string get_nm__tipo_destino_votos();
    int get_geral_position();

    // ==============Override================================================//
    //@Override
    // int compareTo(Candidate o);

    //@Override
    // string toString();
};

#endif
