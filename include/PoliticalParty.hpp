#if !defined(POLITICALPARTY_H)
#define POLITICALPARTY_H

using namespace std;
#include <iostream>
#include <list>
#include "./Candidate.hpp"


class PoliticalParty
{
private:
    string sg;
    int legendVotes;
    int federation;
    int number;
    list<Candidate> candidatesList;
    int position;
public:
    //constructor
    PoliticalParty(int number, string sg, int federation);
     // ======================Getters==================================//

   string getSg();
   int getLegendVotes();
   int getFederation();
   int getNumber();
   int getPosition();
   int getTotalVotes();
  // ======================Setters==================================//

   void setLegendVotes(int legendVotes);
   void setCandidatesList(Candidate* candidate);
   void setPosition(int position);
  // ======================other get methods======================//

  /**
   * @return Lista de candidatos do partido, ordenados
   */
   list<Candidate> getCandidatesList();

  /**
   * @return número de votos nominais
   */
   int getNominalVotes();

  /**
   * @return a quantidade de candidatos do partido que foram eleitos
   */
   int getElectedAmount();

  /**
   * @return o candidato mais votado do partido
   */
   Candidate mostVotedCandidate();

  /**
   * @return o candidato menos votado do partido
   */
   Candidate leastVotedCandidate();

  // ================Override=======================//
  //@Override
   int compareTo(PoliticalParty arg0);
};


#endif // POLITICALPARTY_H