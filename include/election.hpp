#if !defined(ELECTION_H)
#define ELECTION_H
#define MAN 2
#define WOMAN 4

#include <list>
#include <map>
#include <list>
#include <string>
#include "./candidate.hpp"
#include "./political-party.hpp"
#include "./date.hpp"

using std::string;

class Election
{

private:
    int type;
    int legend_votes = 0;
    int nominal_votes = 0;
    map<int, Candidate*> candidates;
    map<int, PoliticalParty*> parties;
    map<int, PoliticalParty*> legends_candidates_parties;
    
    Date current_date;

public:
    Election(int type, string date);

    int get_type() const;
    int elected_men() const;
    int elected_women() const;
    int elected_amount() const;
    int get_legend_votes() const;
    int get_nominal_votes() const;
    int elected_amount_by_age(int start, int end) const;

    void set_legend_votes(int legendVotes);
    void set_nominal_votes(int nominalVotes);
    void set_parties(map<int, PoliticalParty> parties);
    void add_legends_candidates_parties(int key, PoliticalParty * value);
    void add_candidate(int nr_candidato, string nm_urna_candidato, string nm_tipo_destino_votos, Date dt_nascimento,
                        bool cd_sit_tot_turno, int cd_genero, PoliticalParty * party);
    
    map<int, Candidate*> get_candidates_map();
    map<int, PoliticalParty*> get_parties_map();
    map<int, PoliticalParty*> get_legends_candidates_parties();
    
    list<Candidate> elected_candidates() const;
    list<Candidate> get_all_candidates();
    list<Candidate> get_best_candidates() const;
    list<Candidate> elected_if_major_election() const;
    list<Candidate> elected_by_proportional() const;
    list<PoliticalParty> get_parties() const;
    list<PoliticalParty> get_parties_ordered_by_candidates() const;
    
    Date get_current_date();
    PoliticalParty* add_partie(int number, string sg, int federation);
};

#endif // ELECTION_H
