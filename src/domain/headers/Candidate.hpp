#ifndef CANDIDATE_H
#define CANDIDATE_H

using namespace std;
#include <iostream>
#include <ctime>
#include "./PoliticalParty.hpp"


class Candidate
{
private:
    int nrCandidato;
    string nmUrnaCandidato;
    string nmTipoDestinoVotos;
    LocalDate dtNascimento;
    bool cdSitTotTurno;
    int cdGenero;
    PoliticalParty party;
    int qtVotos;
    int electedPosition;
    int geralPosition;

public:
    Candidate(int nrCandidato, string nmUrnaCandidato, string nmTipoDestinoVotos, LocalDate dtNascimento,
            bool cdSitTotTurno, int cdGenero, PoliticalParty party);
        // ===============Setters================================================//
    void setQtVotos(int qtVotos);
    void setElectedPosition(int position);
    void setGeralPosition(int geralPosition);

    // ===============Getters================================================//
    int getNrCandidato();
    bool getCdSitTotTurno();
    int getQtVotos();
    LocalDate getDtNascimento();
    int getCdGenero();
    int getElectedPosition();
    PoliticalParty getParty();
    string getNmUrnaCandidato();
    string getNmTipoDestinoVotos();
    int getGeralPosition();

    // ==============Override================================================//
    //@Override
    int compareTo(Candidate o);

    //@Override
    string toString();
};

#endif