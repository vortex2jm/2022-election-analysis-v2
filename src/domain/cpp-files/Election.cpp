#include "../headers/Election.hpp"


    // Constructor================================//
    Election::Election(int type, LocalDate date) {
        this->type = type;
        this->currentDate = date;
    }

    // ==============Getters======================//
    int Election::getNominalVotes() {
        return nominalVotes;
    }

    int Election::getLegendVotes() {
        return legendVotes;
    }

    int Election::getType() {
        return type;
    }

    map<int, Candidate> Election::getCandidatesmap() {
        return candidates;
    }

    map<int, PoliticalParty> Election::getPartiesmap() {
        return parties;
    }

    map<int, PoliticalParty> Election::getLegendsCandidatesParties() {
        return legendsCandidatesParties;
    }

    LocalDate Election::getCurrentDate() {
        return currentDate;
    }

    // ==============Setters======================//
    void Election::setNominalVotes(int nominalVotes) {
        this->nominalVotes += nominalVotes;
    }

    void Election::setLegendVotes(int legendVotes) {
        this->legendVotes += legendVotes;
    }

    void Election::setParties(map<int, PoliticalParty> parties) {
        this->parties = parties;
    }

    // ================factory
    // methods========================================================================================================//

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
    void Election::addCandidate(int nrCandidato, string nmUrnaCandidato, string nmTipoDestinoVotos, LocalDate dtNascimento,
            bool cdSitTotTurno, int cdGenero, PoliticalParty party) {

        Candidate* cand = new Candidate(nrCandidato, nmUrnaCandidato, nmTipoDestinoVotos, dtNascimento, cdSitTotTurno,
                cdGenero, party);
        this->candidates.put(nrCandidato, cand);
        party.setCandidatesList(cand);
    }

    /**
     * Função factory. Adiciona um partido político à eleição
     * 
     * @param number     numero do partido
     * @param sg         sigla do partido
     * @param federation federação do partido
     * @return Retorna o partido político criado
     */
    PoliticalParty* Election::addPartie(int number, string sg, int federation) {
        PoliticalParty* p = new PoliticalParty(number, sg, federation);
        this->parties.put(number, p);
        return p;
    }

    /**
     * Função factory. Adiciona um candidato inválido, porém com voto de legenda
     * válido À eleição
     * 
     * @param key   chave para alocação no hashmap, utilizado numero do partido
     * @param value o partido
     */
    void Election::addLegendsCandidatesParties(int key, PoliticalParty value) {
        this->legendsCandidatesParties.put(key, value);
    }

    // ===========================another get
    // methods===============================//

    /**
     * @return número de candidatos eleitos
     */
    int Election::electedAmount() {
        int result = 0;
        list<Candidate> c = new list<Candidate>(candidates.values());
        for (Candidate cand : c) {
            if (cand.getCdSitTotTurno())
                result++;
        }
        return result;
    }

    // =========================================================//
    /**
     * @return lista com os candidatos eleitos
     */
    list<Candidate> Election::electedCandidates() {
        list<Candidate> c = new Arraylist<Candidate>(candidates.values());
        list<Candidate> result = new Arraylist<Candidate>();
        for (Candidate cand : c) {
            if (cand.getCdSitTotTurno()) {
                result.add(cand);
            }
        }
        result.sort(null);
        for (int i = 0; i < result.size(); i++) {
            result.get(i).setElectedPosition(i + 1);
        }
        return result;
    }

    // =========================================================//
    /**
     * @return lista de candidatos ordenada em termos de votos
     */
    list<Candidate> Election::getAllCandidates() {
        list<Candidate> c = new Arraylist<Candidate>(candidates.values());
        c.sort(null);
        for (int i = 0; i < c.size(); i++) {
            c.get(i).setGeralPosition(i + 1);
        }
        return c;
    }

    // =========================================================//
    /**
     * @return retorna os candidatos mais votados dentro do número de vagas
     *         disponíveis
     */
    list<Candidate> Election::getBestCandidates() {
        list<Candidate> c = new Arraylist<Candidate>();
        int electedAmount = this->electedAmount();
        list<Candidate> allCandidates = getAllCandidates();

        for (int i = 0; i < electedAmount; i++) {
            c.add(allCandidates.get(i));
        }
        c.sort(null);
        return c;
    }

    // =========================================================//
    /**
     * @return candidatos que seriam eleitos em caso de regra majoritária
     */
    list<Candidate> Election::electedIfMajorElection() {
        list<Candidate> mjEl = new Arraylist<Candidate>();
        list<Candidate> electedCandidates = electedCandidates();

        for (Candidate c : getBestCandidates()) {
            if (!electedCandidates.contains(c))
                mjEl.add(c);
        }
        mjEl.sort(null);
        return mjEl;
    }

    // =========================================================//
    /**
     * @return lista com os candidatos que foram beneficiados pela regra
     *         proporcional
     */
    list<Candidate> Election::electedByProportional() {
        list<Candidate> elctdProp = new Arraylist<Candidate>();
        list<Candidate> mostVoted = getBestCandidates();

        for (Candidate c : electedCandidates()) {
            if (!mostVoted.contains(c))
                elctdProp.add(c);
        }
        elctdProp.sort(null);
        return elctdProp;
    }

    // =========================================================//
    /**
     * @return lista de partidos ordenados a partir da quantidade de votos
     */
    list<PoliticalParty> Election::getParties() {
        list<PoliticalParty> p = new Arraylist<PoliticalParty>(parties.values());
        p.sort(null);
        for (int i = 0; i < p.size(); i++) {
            p.get(i).setPosition(i + 1);
        }
        return p;
    }

    // =========================================================//
    /**
     * @return Partidos ordenados a partir dos atributos de seus candidatos
     */
    list<PoliticalParty> Election::getPartiesOrderedByCandidates() {
        list<PoliticalParty> plist = new Arraylist<PoliticalParty>();

        for (PoliticalParty p : getParties()) {
            if (p.getTotalVotes() > 0 && p.getCandidatesList().size() != 0)
                plist.add(p);
        }
        PartyComparatorByCandidate comparator = new PartyComparatorByCandidate();

        plist.sort(comparator);
        for (int i = 0; i < plist.size(); i++) {
            plist.get(i).setPosition(i + 1);
        }
        return plist;
    }

    // =========================================================//

    /**
     * @param start início do intervalo de interesse de idades
     * @param end   fim do intervalo de interesse de idades
     * @return quantidade de deputados eleitos neste intervalo de idade
     */
    int Election::electedAmountByAge(int start, int end) {
        int total = 0;
        long diff = 0;
        for (Candidate c : electedCandidates()) {
            diff = c.getDtNascimento().until(this->currentDate, ChronoUnit.YEARS);
            if (diff >= start && diff < end)
                total++;
        }
        return total;
    }

    // =========================================================//
    /**
     * @return Quantidade de homens eleitos
     */
    int Election::electedMen() {
        int total = 0;
        for (Candidate c : electedCandidates()) {
            if (c.getCdGenero() == 2)
                total++;
        }
        return total;
    }

    // =========================================================//
    /**
     * @return Quantidade de mulheres eleitas
     */
    int Election::electedWomen() {
        int total = 0;
        for (Candidate c : electedCandidates()) {
            if (c.getCdGenero() == 4)
                total++;
        }
        return total;
    }
