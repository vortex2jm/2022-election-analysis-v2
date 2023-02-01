#include "../../include/io/input-services.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include "../../include/domain/political-party.hpp"

namespace input_service {
    //public methods=============//
    ifstream create_reading_buffer(string file);
    void process_candidates_file(ifstream buffer, Election election);
    void process_votes_file(ifstream buffer, Election election);

    //private methods============//
    bool candidate_is_valid(string cd_cargo, string cd_detalhe_situacao_cand, int type);
    bool vote_is_valid(string cd_cargo, string nr_votavel, int type);
    PoliticalParty update_parties(Election election, vector<string> data);
    vector<string> input_formatter(string line);
    void update_candidates(Election election, PoliticalParty party, vector<string> data);
    void update_invalid_candidates(Election election, PoliticalParty party, vector<string> data);
    bool is_elected_candidate(string sit);
    void process_valid_candidates_votes(Election election, vector<string> data);
    void process_invalid_candidates_votes(Election election, vector<string> data);
}
//===========================================================================================//
ifstream create_reading_buffer(string file){
    ifstream buffer(file);
    return buffer;
}

void process_candidates_file(ifstream stream, Election election){
    string currentLine;
    vector<string> currentData;
    PoliticalParty party;

    try {
        getline(stream, currentLine); // elimina a linha de legenda
        //TODO null
        while ((currentLine = getline(stream, currentLine)) != null) {

            // Removendo aspas e separando por ";"
            currentData = inputFormatter(currentLine);

            // Atualizando mapa de partidos
            party = updateParties(election, currentData);

            // caso candidatura válida
            if (candidateIsValid(currentData[13], currentData[68], election.getType())) {
                updateCandidates(election, currentData, party);
                continue;
            }
            // caso candidatura inválida mas candidato de interesse(importante para
            // processamento de potenciais votos de legenda)
            if (election.getType() == Integer.parseInt(currentData[13])
                    && currentData[67].compareTo("Válido (legenda)") == 0) {
                updateInvalidCandidates(election, currentData, party);
            }
        }
    } catch (IOException e) {
        System.out.println("Erro ao ler uma linha do arquivo de candidatos");
        throw new CandidatesFileProcessException();
    } catch (NumberFormatException e) {
        System.out.println("A string não pode ser convertida em um tipo numérico");
        throw new CandidatesFileProcessException();
    }
}
void process_votes_file(ifstream buffer, Election election){
    
}

//private methods============//
bool candidate_is_valid(string cd_cargo, string cd_detalhe_situacao_cand, int type){
    
}
bool vote_is_valid(string cd_cargo, string nr_votavel, int type){
    
}
PoliticalParty update_parties(Election election, vector<string> data){
    
}
vector<string> input_formatter(string line){
    
}
void update_candidates(Election election, PoliticalParty party, vector<string> data){
    
}
void update_invalid_candidates(Election election, PoliticalParty party, vector<string> data){
    
}
bool is_elected_candidate(string sit){
    
}
void process_valid_candidates_votes(Election election, vector<string> data){
    
}
void process_invalid_candidates_votes(Election election, vector<string> data){
    
}
