#ifndef POLITICALPARTY_H
#define POLITICALPARTY_H

using namespace std;
#include <iostream>
#include <list>
#include "./candidate.hpp"

class PoliticalParty
{

private:
    string sg;
    int legendVotes;
    int federation;
    int number;
    list<Candidate*> candidatesList;
    int position;

public:
    //constructor
    PoliticalParty(int number, string sg, int federation);
     // ======================Getters==================================//

   string get_sg();
   int get_legend_votes();
   int get_federation();
   int get_number();
   int get_position();
   int get_total_votes();
  // ======================Setters==================================//

   void set_legend_votes(int legendVotes);
   void add_candidate(Candidate* candidate);
   void set_position(int position);
  // ======================other get methods======================//

  /**
   * @return Lista de candidatos do partido, ordenados
   */
   list<Candidate*> get_candidates_list();

  /**
   * @return número de votos nominais
   */
   int get_nominal_votes();

  /**
   * @return a quantidade de candidatos do partido que foram eleitos
   */
   int get_elected_amount();

  /**
   * @return o candidato mais votado do partido
   */
   Candidate most_voted_candidate();

  /**
   * @return o candidato menos votado do partido
   */
   Candidate least_voted_candidate();
};

#endif // POLITICALPARTY_H
