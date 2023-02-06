#ifndef POLITICALPARTY_H
#define POLITICALPARTY_H

using namespace std;
#include <iostream>
#include <list>
#include "./candidate.hpp"

class Candidate;

class PoliticalParty
{

private:
    int number;
    int position;
    int federation;
    int legend_votes;
    
    string sg;

    list<Candidate*> candidatesList;

public:
    PoliticalParty(int number, string sg, int federation);
    
    int get_number() const;
    int get_position() const;
    int get_federation() const;
    int get_total_votes() const;
    int get_legend_votes() const;
    int get_elected_amount() const;
    int get_nominal_votes() const;
    
    void set_legend_votes(int legendVotes);
    void add_candidate(Candidate* candidate);
    void set_position(int position);

    bool operator>(const PoliticalParty party2) const;
    static bool party_comparator_by_candidate(const PoliticalParty &p1, const PoliticalParty &p2);
    
    string get_sg() const;
    
    list<Candidate*> get_candidates_list() const;
    
    Candidate most_voted_candidate() const;
    Candidate least_voted_candidate() const;
};

#endif // POLITICALPARTY_H
