#include "../headers/PoliticalParty.hpp"

  // ======================Getters==================================//
  string PoliticalParty::getSg() {
    return sg;
  }

  int PoliticalParty::getLegendVotes() {
    return legendVotes;
  }

  int PoliticalParty::getFederation() {
    return federation;
  }

  int PoliticalParty::getNumber() {
    return number;
  }

  int PoliticalParty::getPosition() {
    return position;
  }

  int PoliticalParty::getTotalVotes() {
    return this->legendVotes + getNominalVotes();
  }

  // ======================Setters==================================//
  void PoliticalParty::setLegendVotes(int legendVotes) {
    this->legendVotes += legendVotes;
  }

  void PoliticalParty::setCandidatesList(Candidate* candidate) {
    this->candidatesList.add(candidate);
  }

  void PoliticalParty::setPosition(int position) {
    this->position = position;
  }

  // ======================another get methods======================//
  /**
   * @return lista de candidatos do partido, ordenados
   */
  list<Candidate> PoliticalParty::getCandidateslist() {
    list<Candidate> lista = new Arraylist<>(this.candidateslist);
    lista.sort(null);
    return lista;
  }

  // ======================================//
  /**
   * @return número de votos nominais
   */
  int PoliticalParty::getNominalVotes() {
    int total = 0;
    for (Candidate c : candidatesList) {
      total += c.getQtVotos();
    }
    return total;
  }

  // ======================================//
  /**
   * @return a quantidade de candidatos do partido que foram eleitos
   */
  int PoliticalParty::getElectedAmount() {
    int total = 0;
    for (Candidate c : candidatesList) {
      if (c.getCdSitTotTurno())
        total++;
    }
    return total;
  }

  // ======================================//
  /**
   * @return o candidato mais votado do partido
   */
  Candidate PoliticalParty::mostVotedCandidate() {
    list<Candidate> lista = new Arraylist<Candidate>(this.candidateslist);
    lista.sort(null);
    return lista.get(0);
  }

  // ======================================//
  /**
   * @return o candidato menos votado do partido
   */
  Candidate PoliticalParty::leastVotedCandidate() {
    list<Candidate> lista = new Arraylist<Candidate>(this.candidateslist);
    lista.sort(null);
    return lista.get(lista.size() - 1);
  }

  // ================Override======================================//
  //@Override
  int PoliticalParty::compareTo(PoliticalParty arg0) {
    int ownTotal = legendVotes + getNominalVotes();
    int otherTotal = arg0.legendVotes + arg0.getNominalVotes();

    if (ownTotal > otherTotal)
      return -1;
    if (ownTotal < otherTotal)
      return 1;
    if (this->number < arg0.number)
      return -1;
    if (this->number > arg0.number)
      return 1;
    return 0;
  }