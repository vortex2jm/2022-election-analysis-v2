#if !defined(ELECTION_H)
#define ELECTION_H

using namespace std;
#include <list>
#include <map>
#include <array>
#include "./Candidate.hpp"
#include "./PoliticalParty.hpp"

class Election
{
private:
    map<int, Candidate> candidates;
    map<int, PoliticalParty> parties;
    map<int, PoliticalParty> legendsCandidatesParties;
    int nominalVotes = 0;
    int legendVotes = 0;
    int type;
    LocalDate currentDate;

public:
    Election(int type, LocalDate date);

    // ==============Getters======================//
    int getNominalVotes();
    int getLegendVotes();
    int getType();
    map<int, Candidate> getCandidatesmap();
    map<int, PoliticalParty> getPartiesmap();
    map<int, PoliticalParty> getLegendsCandidatesParties();
    LocalDate getCurrentDate();

    // ==============Setters======================//
    void setNominalVotes(int nominalVotes);
    void setLegendVotes(int legendVotes);
    void setParties(map<int, PoliticalParty> parties);
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
    void addCandidate(int nrCandidato, string nmUrnaCandidato, string nmTipoDestinoVotos, LocalDate dtNascimento,
            bool cdSitTotTurno, int cdGenero, PoliticalParty party);

    /**
     * Função factory. Adiciona um partido político à eleição
     * 
     * @param number     numero do partido
     * @param sg         sigla do partido
     * @param federation federação do partido
     * @return Retorna o partido político criado
     */
    PoliticalParty* addPartie(int number, string sg, int federation);

    /**
     * Função factory. Adiciona um candidato inválido, porém com voto de legenda
     * válido À eleição
     * 
     * @param key   chave para alocação no hashmap, utilizado numero do partido
     * @param value o partido
     */
    void addLegendsCandidatesParties(int key, PoliticalParty value);

    // ==============other get methods==========//

    /**
     * @return número de candidatos eleitos
     */
    int electedAmount();
    
    /**
     * @return lista com os candidatos eleitos
     */
    list<Candidate> electedCandidates();

    /**
     * @return lista de candidatos ordenada em termos de votos
     */
    list<Candidate> getAllCandidates();

    /**
     * @return retorna os candidatos mais votados dentro do número de vagas
     *         disponíveis
     */
    list<Candidate> getBestCandidates();

    /**
     * @return candidatos que seriam eleitos em caso de regra majoritária
     */
    list<Candidate> electedIfMajorElection();

    /**
     * @return lista com os candidatos que foram beneficiados pela regra
     *         proporcional
     */
    list<Candidate> electedByProportional();

    /**
     * @return lista de partidos ordenados a partir da quantidade de votos
     */
    list<PoliticalParty> getParties();

    /**
     * @return Partidos ordenados a partir dos atributos de seus candidatos
     */
    list<PoliticalParty> getPartiesOrderedByCandidates();
    
    /**
     * @param start início do intervalo de interesse de idades
     * @param end   fim do intervalo de interesse de idades
     * @return quantidade de deputados eleitos neste intervalo de idade
     */
    int electedAmountByAge(int start, int end);
    /**
     * @return Quantidade de homens eleitos
     */
    int electedMen();
    /**
     * @return Quantidade de mulheres eleitas
     */
    int electedWomen();
};

#endif // ELECTION_H