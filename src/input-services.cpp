#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include "../include/input-services.hpp"
#include "../include/political-party.hpp"
#include "../include/file-input-exception.hpp"


// ifstream in_service::create_reading_stream(string file);
vector<string> in_service::split(string input, char delimiter);
void in_service::process_votes_file(string file, Election& election);
void in_service::process_candidates_file(string file, Election& election);

//===========================================================================================//
bool process_valid_candidates_votes(Election &election, vector<string> &data);
void process_invalid_candidates_votes(Election &election, vector<string> &data);
void update_candidates(Election &electin, PoliticalParty * party, vector<string> &data);
void update_invalid_candidates(Election &election, PoliticalParty * party, vector<string> &data);

bool is_elected_candidate(string sit);
bool vote_is_valid(string cd_cargo, string nr_votavel, int type);
bool candidate_is_valid(string cd_cargo, string cd_detalhe_situacao_cand, int type);

string iso_8859_1_to_utf8(string str);
string removeChar(string input, char character);

vector<string> input_formatter(string &line);
PoliticalParty * update_parties(Election &election, vector<string> &data);

//===========================================================================================//
ifstream in_service::create_reading_stream(string file){
    ifstream buffer(file);
   return buffer;
}

//===========================================================================================//
void in_service::process_candidates_file(string file, Election& election){
    string current_line;
    vector<string> current_data;
    PoliticalParty *party;
    ifstream f_input;

    try{
        f_input.open(file);

        getline(f_input, current_line);
        while (getline(f_input, current_line)) {

            if(current_line.size() == 0)
                break;

            // Removendo aspas e separando por ";"
            current_data = input_formatter(current_line);
            // Atualizando mapa de partidos
            party = update_parties(election, current_data);              
            // caso candidatura válida
            if (candidate_is_valid(current_data[13], current_data[68], election.get_type())) {
                update_candidates(election, party, current_data);
                continue;
            }
            // caso candidatura inválida mas candidato de interesse(importante para
            // processamento de potenciais votos de legenda)
            //@todo
            if (election.get_type() == stoi(current_data[13])
                    && current_data[67] == "Válido (legenda)") {
                update_invalid_candidates(election, party, current_data);
            }
        }
    } catch(const fileInputException& e){
        std::cerr <<  e.what() << endl;
        cout << "Could not read file" << endl;
    }

    f_input.close();
}

//===========================================================================================//
void in_service::process_votes_file(string file, Election& election){
    string current_line;
    vector<string> current_data;
    ifstream f_input;

    f_input.open(file);

    getline(f_input, current_line); // Removendo linha de cabeçalho

    while (getline(f_input, current_line)) {

        current_data = input_formatter(current_line);
        
        if (vote_is_valid(current_data[17], current_data[19],  election.get_type())) {
            if(!process_valid_candidates_votes(election, current_data))
                process_invalid_candidates_votes(election, current_data);
        }
    }

    f_input.close();
}

//===========================================================================================//
bool candidate_is_valid(string cd_cargo, string cd_detalhe_situacao_cand, int type){
    int cdC, cdD;
        cdC = stoi(cd_cargo); 
        cdD = stoi(cd_detalhe_situacao_cand);
    if ((cdC == type) && (cdD == 2 || cdD == 16))
        return true;
    return false;
}

//===========================================================================================//
bool vote_is_valid(string cd_cargo, string nr_votavel, int type){
    int candidate_code, nrV;
        candidate_code = stoi(cd_cargo);
        nrV = stoi(nr_votavel);
    if (candidate_code == type && !(nrV > 94 && nrV < 99))
        return true;
    return false;
}

//===========================================================================================//
PoliticalParty* update_parties(Election &election, vector<string> &data){
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

//===========================================================================================//
vector<string> input_formatter(string &line){
    vector<string> current_data = in_service::split(line, ';');
    for(string &s : current_data){
        s = s.substr(1,s.length() - 2);
    }
    return current_data;
}

//===========================================================================================//
void update_candidates(Election &election, PoliticalParty * party, vector<string> &data){
    
    int nr_candidato;
    int cd_genero;
    string nm_urna_candidato = data[18];
    string nm_tipo_destino_votos = data[67];
    Date data_nasc(data[42]);

    // cout << data[42] << endl;

    bool situation;
    situation = is_elected_candidate(data[56]);
    nr_candidato = stoi(data[16]);
    cd_genero = stoi(data[45]);
    election.add_candidate(nr_candidato, nm_urna_candidato, nm_tipo_destino_votos, data_nasc, situation, cd_genero, party);
        
}

//===========================================================================================//
void update_invalid_candidates(Election &election, PoliticalParty * party, vector<string> &data){
    int nr_candidato;
        nr_candidato = stoi(data[16]);
    election.add_legends_candidates_parties(nr_candidato, party);
}

//===========================================================================================//
bool is_elected_candidate(string sit){
    int situation;
        situation = stoi(sit);
    if (situation == 2 || situation == 3)
        return true;
    return false;
}

//===========================================================================================//
bool process_valid_candidates_votes(Election &election, vector<string> &data){
    int nr_votavel, qt_votos;
        nr_votavel = stoi(data[19]);
        qt_votos = stoi(data[21]);
    // Se o número é de um candidato, conta como voto nominal
    if (election.get_candidates_map().count(nr_votavel) != 0) {
        election.get_candidates_map().at(nr_votavel)->set_qt_votos(qt_votos);
        election.set_nominal_votes(qt_votos);
        return true;
    }
    // Se o número é de um partido, conta como voto de legenda
    if (election.get_parties_map().count(nr_votavel)) {
        election.get_parties_map().at(nr_votavel)->set_legend_votes(qt_votos);
        election.set_legend_votes(qt_votos);
        return true;
    }
    return false;
}

//===========================================================================================//
void process_invalid_candidates_votes(Election &election, vector<string> &data){
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


//===========================================================================================//
string removeChar(string input, char character) {
    string result;
   for (char c : input) {
        if (c != character) {
            result += character;
        }
    }
    return result;
}

//===========================================================================================//
vector<string> in_service::split(string input, char delimiter)
{
    vector<string> result;
    string data;
    
    input = iso_8859_1_to_utf8(input);
    stringstream stream(input);

    while (std::getline(stream, data, delimiter)) {
            result.push_back(data);
        }
    return result;
}

//===========================================================================================//
string iso_8859_1_to_utf8(string str)
{
  // adaptado de: https://stackoverflow.com/a/39884120 :-)
  string strOut;
  for (string::iterator it = str.begin(); it != str.end(); ++it)
  {
    uint8_t ch = *it;
    if (ch < 0x80)
    {
      // já está na faixa ASCII (bit mais significativo 0), só copiar para a saída
      strOut.push_back(ch);
    }
    else
    {
      // está na faixa ASCII-estendido, escrever 2 bytes de acordo com UTF-8
      // o primeiro byte codifica os 2 bits mais significativos do byte original (ISO-8859-1)
      strOut.push_back(0b11000000 | (ch >> 6));
      // o segundo byte codifica os 6 bits menos significativos do byte original (ISO-8859-1)
      strOut.push_back(0b10000000 | (ch & 0b00111111));
    }
  }
  return strOut;
}
