#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include "../include/input-services.hpp"
#include "../include/political-party.hpp"

    //public methods=============//
    ifstream in_service::create_reading_stream(string file);
    void in_service::process_candidates_file(ifstream stream, Election& election);
    void in_service::process_votes_file(ifstream stream, Election& election);

    //private methods============//
    bool candidate_is_valid(string cd_cargo, string cd_detalhe_situacao_cand, int type);
    bool vote_is_valid(string cd_cago, string nr_voavel, int type);
    PoliticalParty * update_parties(Election election, vector<string> data);
    vector<string> input_formatter(string line);
    void update_candidates(Election electin, PoliticalParty party, vector<string> data);
    void update_invalid_candidates(Election election, PoliticalParty party, vector<string> data);
    bool is_elected_candidate(string sit);
    void process_valid_candidates_votes(Election election, vector<string> data);
    void process_invalid_candidates_votes(Election election, vector<string> data);
    vector<std::string> split(const string &input, char delimiter);
    string removeChar(string input, char character);

   //===========================================================================================//
    ifstream in_service::create_reading_stream(string file){
        ifstream buffer(file);
       return buffer;
    }

    void in_service::process_candidates_file(ifstream stream, Election& election){
        string current_line;
        vector<string> current_data;
        PoliticalParty *party;

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
                        && current_data[67] == "Válido (legenda)") {
                    update_invalid_candidates(election, *party, current_data);
                }
            }
    }
    
    void in_service::process_votes_file(ifstream stream, Election& election){
        string current_line;
        vector<string> current_data;

            getline(stream, current_line); // Removendo linha de cabeçalho
            while (stream.good()) {

                // Removendo aspas e separando por ";"
                current_data = input_formatter(current_line);

                // Se o voto é válido, é processado
                if (vote_is_valid(current_data[17], current_data[19],  election.get_type())) {
                    process_valid_candidates_votes(election, current_data);
                    process_invalid_candidates_votes(election, current_data);
                }
            }
    }

    //=========private methods============//
    bool candidate_is_valid(string cd_cargo, string cd_detalhe_situacao_cand, int type){
        int cdC, cdD;
            cdC = stoi(cd_cargo); 
            cdD = stoi(cd_detalhe_situacao_cand);

        if ((cdC == type) && (cdD == 2 || cdD == 16))
            return true;
        return false;
    }

    bool vote_is_valid(string cd_cargo, string nr_votavel, int type){
        int candidate_code, nrV;
            candidate_code = stoi(cd_cargo);
            nrV = stoi(nr_votavel);


        if (candidate_code == type && nrV != 95 && nrV != 96 && nrV != 97 && nrV != 98)
            return true;
        return false;
    }

    PoliticalParty* update_parties(Election election, vector<string> data){
        int nr_partido, nr_federacao;
       string sg_partido = data[28];

            nr_partido = stoi(data[27]);
            nr_federacao = stoi(data[30]);

        // Se o mapa já possui o partido, ele apenas retorna o partido sem criar um novo
        if (election.get_parties_map().count(nr_partido)) {
            return election.get_parties_map().at(nr_partido);
        }
        return election.add_partie(nr_partido, sg_partido, nr_federacao);
    }

    vector<string> input_formatter(string line){
        vector<string> current_data = split(line, ';');
           for (int i= 0; i <  (int)current_data.size(); i++) {
                current_data[i] = removeChar(current_data[i], '\"');
            }
            return current_data;
    }
    void update_candidates(Election election, PoliticalParty party, vector<string> data){
        
        int nr_candidato;
        int cd_genero;
        string nm_urna_candidato = data[18];
        string nm_tipo_destino_votos = data[67];
        Date data_nasc(data[42]);
        bool situation;

            situation = is_elected_candidate(data[56]);
            nr_candidato = stoi(data[16]);
            cd_genero = stoi(data[45]);
            election.add_candidate(nr_candidato, nm_urna_candidato, nm_tipo_destino_votos, data_nasc, situation, cd_genero, &party);
            
    }
    void update_invalid_candidates(Election election, PoliticalParty party, vector<string> data){
        int nr_candidato;
            nr_candidato = stoi(data[16]);

        election.add_legends_candidates_parties(nr_candidato, &party);
    }
    bool is_elected_candidate(string sit){
        int situation;

            situation = stoi(sit);

        if (situation == 2 || situation == 3)
            return true;
        return false;
    }
    void process_valid_candidates_votes(Election election, vector<string> data){
        int nr_votavel, qt_votos;
            nr_votavel = stoi(data[19]);
            qt_votos = stoi(data[21]);

        // Se o número é de um candidato, conta como voto nominal
        if (election.get_candidates_map().count(nr_votavel)) {
            election.get_candidates_map().at(nr_votavel)->set_qt_votos(qt_votos);
            election.set_nominal_votes(qt_votos);
            return;
        }

        // Se o número é de um partido, conta como voto de legenda
        if (election.get_parties_map().count(nr_votavel)) {
            election.get_parties_map().at(nr_votavel)->set_legend_votes(qt_votos);
            election.set_legend_votes(qt_votos);
        }
    }
    void process_invalid_candidates_votes(Election election, vector<string> data){
        int nr_votavel, qt_votos;
            nr_votavel = stoi(data[19]);
            qt_votos= stoi(data[21]);

        // Se o número do candidato está no mapa de candidatos inválidos, conta como
        // voto de legenda
        if (election.get_legends_candidates_parties().count(nr_votavel)) {
            election.get_legends_candidates_parties().at(nr_votavel)->set_legend_votes(qt_votos);
            election.set_legend_votes(qt_votos);
        }
    }


    vector<std::string> split(const string &input, char delimiter) {
        vector<std::string> result;
       string token;
       stringstream stream(input);

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

std::vector<int> in_service::separate_by_slash(std::string date){

  int day = stoi(date.substr(0,1));
  int month = stoi(date.substr(3,4));
  int year = stoi(date.substr(6,7));

  std::vector<int> separated_date;
  separated_date.push_back(day);
  separated_date.push_back(month);
  separated_date.push_back(year);

  return separated_date;
} 