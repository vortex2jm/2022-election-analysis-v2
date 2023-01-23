#include "../headers/Candidate.hpp"

    Candidate::Candidate(int nrCandidato, string nmUrnaCandidato, string nmTipoDestinoVotos, LocalDate dtNascimento,
            bool cdSitTotTurno, int cdGenero, PoliticalParty party) {
        this->nrCandidato = nrCandidato;
        this->dtNascimento = dtNascimento;
        this->cdSitTotTurno = cdSitTotTurno;
        this->cdGenero = cdGenero;
        this->party = party;
        this->qtVotos = 0;
        this->nmUrnaCandidato = nmUrnaCandidato;
        this->nmTipoDestinoVotos = nmTipoDestinoVotos;
    }

    // ===============Setters================================================//
     void Candidate::setQtVotos(int qtVotos) {
        this->qtVotos += qtVotos;
    }

     void Candidate::setElectedPosition(int position) {
        this->electedPosition = position;
    }

     void Candidate::setGeralPosition(int geralPosition) {
        this->geralPosition = geralPosition;
    }

    // ===============Getters================================================//
     int Candidate::getNrCandidato() {
        return nrCandidato;
    }

     bool Candidate::getCdSitTotTurno() {
        return cdSitTotTurno;
    }

     int Candidate::getQtVotos() {
        return qtVotos;
    }

     LocalDate Candidate::getDtNascimento() {
        return dtNascimento;
    }

     int Candidate::getCdGenero() {
        return cdGenero;
    }

     int Candidate::getElectedPosition() {
        return electedPosition;
    }

     PoliticalParty Candidate::getParty() {
        return party;
    }

     string Candidate::getNmUrnaCandidato() {
        return nmUrnaCandidato;
    }

     string Candidate::getNmTipoDestinoVotos() {
        return nmTipoDestinoVotos;
    }

     int Candidate::getGeralPosition() {
        return geralPosition;
    }

    // ==============Override================================================//
    //@override
     int Candidate::compareTo(Candidate o) {
        if (this->qtVotos < o.getQtVotos())
            return 1;
        if (this->qtVotos > o.getQtVotos())
            return -1;
        if (this->dtNascimento->compareTo(o.getDtNascimento()) < 0)
            return -1;
        if (this->dtNascimento->compareTo(o.getDtNascimento()) > 0) {
            return 1;
        }
        return 0;
    }

    // ==================================//
    //@Override
     string Candidate::toString() {
        return this->nmUrnaCandidato + " (" + this->party->getSg() + ", " + this->qtVotos + " votos)";
    }