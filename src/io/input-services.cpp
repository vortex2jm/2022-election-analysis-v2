#include "../../include/io/input-services.hpp"
#include "../../include/domain/political-party.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

namespace input_service {
    //public methods=============//
    ifstream create_reading_stream(string file);
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
ifstream create_reading_stream(string file){
    ifstream buffer(file);
    return buffer;
}

void process_candidates_file(ifstream stream, Election election){
    string current_line;
    vector<string> current_data;
    PoliticalParty* party;

    try {
        getline(stream, current_line); // elimina a linha de legenda

        while (stream.good()) {

            // Removendo aspas e separando por ";"
            getline(stream,current_line);
            current_data = input_formatter(current_line);

            // Atualizando mapa de partidos
            party = update_parties(election, current_data);

            // caso candidatura válida
            if (candidate_is_valid(current_data[13], current_data[68], election.get_type())) {
                update_candidates(election, *party, current_data);
                continue;
            }
            // caso candidatura inválida mas candidato de interesse(importante para
            // processamento de potenciais votos de legenda)
            //@todo
            if (election.get_type() == stoi(current_data[13])
                    && current_data[67].compareTo("Válido (legenda)") == 0) {
                update_invalid_candidates(election, *party, current_data);
            }
        }
    } catch (exception& e) {
        cout << "Erro ao ler uma linha do arquivo de candidatos" << endl;
        throw new CandidatesFileProcessException();
    } catch (exception& e) {
        cout << "A string não pode ser convertida em um tipo numérico" << endl;
        throw new CandidatesFileProcessException();
    }
}
void process_votes_file(ifstream buffer, Election election){
    
}

//=========private methods============//
bool candidate_is_valid(string cd_cargo, string cd_detalhe_situacao_cand, int type){
    int cdC, cdD;

    try {
        cdC = stoi(cd_cargo); 
        cdD = stoi(cd_detalhe_situacao_cand);
    } catch(exception& e) {
        cout << "A string não pode ser convertida em um tipo numérico" << endl;
        throw e;
    }

    if ((cdC == type) && (cdD == 2 || cdD == 16))
        return true;
    return false;
}
bool vote_is_valid(string cd_cargo, string nr_votavel, int type){
    int candidate_code, nrV;

    try {
        candidate_code = stoi(cd_cargo);
        nrV = stoi(nr_votavel);

    } catch (exception& e) {
        cout << "A string não pode ser convertida em um tipo numérico"<< endl;
        throw e;
    }

    if (candidate_code == type && nrV != 95 && nrV != 96 && nrV != 97 && nrV != 98)
        return true;
    return false;
}
PoliticalParty* update_parties(Election election, vector<string> data){
    int nr_partido, nr_federacao;
    string sg_partido = data[28];


    try {
        nr_partido = stoi(data[27]);
        nr_federacao = stoi(data[30]);
    } catch (exception& e) {
       cout << "A string não pode ser convertida em um tipo numérico" << endl;
        throw e;
    }

    // Se o mapa já possui o partido, ele apenas retorna o partido sem criar um novo
    if (election.get_parties_map().count(nr_partido)) {
        return election.get_parties_map().at(nr_partido);
    }
    return election.add_partie(nr_partido, sg_partido, nr_federacao);
}
vector<string> input_formatter(string line){
    vector<string> current_data = split(line, ';');
        for (int i = 0; i <  current_data.size(); i++) {
            current_data[i] = removeChar(current_data[i], '\"');
        }
        return current_data;
}
void update_candidates(Election election, PoliticalParty party, vector<string> data){
    int day;
    int month;
    int year;
    int nr_candidato;
    int cd_genero;
    vector<string> date = split(data[42],'/');
    string nm_urna_candidato = data[18];
    string nm_tipo_destino_votos = data[67];
    Date data_nasc;
    bool situation;

    try {
        day = stoi(date[0]);
        month = stoi(date[1]);
        year = stoi(date[2]);
        data_nasc = LocalDate.of(year, month, day);
        situation = is_elected_candidate(data[56]);
        nr_candidato = stoi(data[16]);
        cd_genero = stoi(data[45]);
        election.add_candidate(nr_candidato, nm_urna_candidato, nm_tipo_destino_votos, data_nasc, situation, cd_genero, &party);
        
    } catch (exception& e) {
        cout << "A string não pode ser convertida em um tipo numérico" << endl;
        throw e;
    }
}
void update_invalid_candidates(Election election, PoliticalParty party, vector<string> data){
    
}
bool is_elected_candidate(string sit){
    
}
void process_valid_candidates_votes(Election election, vector<string> data){
    
}
void process_invalid_candidates_votes(Election election, vector<string> data){
    
}

vector<std::string> split(const string &input, char delimiter) {
    vector<std::string> result;
    string token;
    istringstream stream(input);

    while (std::getline(stream, token, delimiter)) {
        result.push_back(token);
    }
    return result;
}

string removeChar(string input, char character) {
    string result;

    for (char c : input) {
        if (c != character) {
            result += character;
        }
    }
    return result;
}