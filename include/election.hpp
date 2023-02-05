#if !defined(ELECTION_H)
#define ELECTION_H
#define MAN 2
#define WOMAN 4

using namespace std;

#include <list>
#include <map>
#include <list>
#include <ctime>
#include <string>
#include "./candidate.hpp"
#include "./political-party.hpp"
#include "./date.hpp"

class Election
{

private:
    map<int, Candidate*> candidates;
    map<int, PoliticalParty*> parties;
    map<int, PoliticalParty*> legends_candidates_parties;
    int nominal_votes = 0;
    int legend_votes = 0;
    int type;
    Date current_date;

public:
    Election(int type, string date);

    // ==============Getters======================//
    int get_nominal_votes();
    int get_legend_votes();
    int get_type();
    map<int, Candidate*> get_candidates_map();
    map<int, PoliticalParty*> get_parties_map();
    map<int, PoliticalParty*> get_legends_candidates_parties();
    Date get_current_date();

    // ==============Setters======================//
    void set_nominal_votes(int nominalVotes);
    void set_legend_votes(int legendVotes);
    void set_parties(map<int, PoliticalParty> parties);
    // ================factory methods====================================//

    /**
     * Função factory. Adiciona um candidato à eleição
     * 
     * @param nrCandidato        Numero do candidato na urna
     * @param nmUrnaCandidato    nome do candidato na urna
     * @param nmTipoDestinoVotos nome de destino de voto - nominal ou legenda
     * @param dtNascimento       data de nascimento do candidato
     * @param cdSitTotTurno      resultado da votação no turno
     * @param cdGenero           código indicador de gênero
     * @param party              partido do candidato
     */
    void add_candidate(int nr_candidato, string nm_urna_candidato, string nm_tipo_destino_votos, Date dt_nascimento,
            bool cd_sit_tot_turno, int cd_genero, PoliticalParty * party);

    /**
     * Função factory. Adiciona um partido político à eleição
     * 
     * @param number     numero do partido
     * @param sg         sigla do partido
     * @param federation federação do partido
     * @return Retorna o partido político criado
     */
    PoliticalParty* add_partie(int number, string sg, int federation);

    /**
     * Função factory. Adiciona um candidato inválido, porém com voto de legenda
     * válido À eleição
     * 
     * @param key   chave para alocação no hashmap, utilizado numero do partido
     * @param value o partido
     */
    void add_legends_candidates_parties(int key, PoliticalParty * value);

    // ==============other get methods==========//

    /**
     * @return número de candidatos eleitos
     */
    int elected_amount();
    
    /**
     * @return lista com os candidatos eleitos
     */
    list<Candidate> elected_candidates();

    /**
     * @return lista de candidatos ordenada em termos de votos
     */
    list<Candidate> get_all_candidates();

    /**
     * @return retorna os candidatos mais votados dentro do número de vagas
     *         disponíveis
     */
    list<Candidate> get_best_candidates();

    /**
     * @return candidatos que seriam eleitos em caso de regra majoritária
     */
    list<Candidate> elected_if_major_election();

    /**
     * @return lista com os candidatos que foram beneficiados pela regra
     *         proporcional
     */
    list<Candidate> elected_by_proportional();

    /**
     * @return lista de partidos ordenados a partir da quantidade de votos
     */
    list<PoliticalParty> get_parties();

    /**
     * @return Partidos ordenados a partir dos atributos de seus candidatos
     */
    list<PoliticalParty> get_parties_ordered_by_candidates();
    
    /**
     * @param start início do intervalo de interesse de idades
     * @param end   fim do intervalo de interesse de idades
     * @return quantidade de deputados eleitos neste intervalo de idade
     */
    int elected_amount_by_age(int start, int end);
    /**
     * @return Quantidade de homens eleitos
     */
    int elected_men();
    /**
     * @return Quantidade de mulheres eleitas
     */
    int elected_women();
};

#endif // ELECTION_H
