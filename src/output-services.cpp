#include "../include/output-services.hpp"

#include <iostream>
#include <string>

//VERIFICAR SE PRECISA SETTAR O LOCALE PARA C


    void generate_reports(Election election);

    //private methods=============//
    void vacancies_number(Election election);
    void elected_candidates(Election election);
    void most_voted_candidates(Election election);
    void harmed_candidates(Election election);
    void benefited_candidates(Election election);
    void party_voting_and_elected_candidates(Election election);
    void first_and_last_candidates_from_parties(Election election);
    void elected_by_age(Election election);
    void elected_by_gender(Election election);
    void all_voting(Election election);
    string plural_singular_filter(string out, int value);

//public methods==============//

//====================================================================//
    // FALTA FAZER COISA AQUI
    void generate_reports(Election election) 
    {
        // Gerando as saídas
        vacancies_number(election);
        elected_candidates(election);
        most_voted_candidates(election);
        harmed_candidates(election);
        benefited_candidates(election);
        party_voting_and_elected_candidates(election);
        first_and_last_candidates_from_parties(election);
        elected_by_age(election);
        elected_by_gender(election);
        all_voting(election);
    }

    //====================================================================//
    void vacancies_number(Election election)
    {
        cout.imbue(locale("pt_BR.utf8"));
        cout << "Número de vagas: " << election.elected_amount() << endl;
        cout.imbue(locale("C"));
    }

    //====================================================================//
    void elected_candidates(Election election)
    {
        string category = "";
        if(election.get_type() == 6)
            category = "federais";
        else if(election.get_type() == 7)
            category = "estaduais";

        cout << "Deputados " << category <<" eleitos:" << endl;
        string vot;

        for(Candidate c : election.elected_candidates()){
            cout << c.get_elected_position() << " - ";
            if(c.get_party()->get_federation() != -1)
                cout << "*";
            
            vot = "voto";
            vot = plural_singular_filter(vot, c.get_qt_votos());
            cout << c.get_nm_urna_candidato() << " (" << c.get_party()->get_sg() << ", ";

            cout.imbue(locale("pt_BR.utf8"));
            cout << c.get_qt_votos() << " " << vot << ")" << endl;
            cout.imbue(locale("C"));
        }
        cout << endl;
    }

    //====================================================================//
    void most_voted_candidates(Election election)
    {
        cout << "Candidatos mais votados (em ordem decrescente de votação e respeitando número de vagas):" << endl;

        string vot;
        for(Candidate c : election.get_best_candidates()){
             cout << c.get_geral_position() << " - ";
             if(c.get_party()->get_federation() != -1)
                cout << "*";

            vot = "voto";
            vot = plural_singular_filter(vot, c.get_qt_votos());
            cout << c.get_nm_urna_candidato() << " (" << c.get_party()->get_sg() << ", ";
            
            cout.imbue(locale("pt_BR.utf8"));
            cout << c.get_qt_votos() << " " << vot << ")" << endl;
            cout.imbue(locale("C"));
        }
        cout << endl;
    }

    //====================================================================//
    void harmed_candidates(Election election)
    {
        cout << "Teriam sido eleitos se a votação fosse majoritária, e não foram eleitos:" << endl;
        cout << "(com sua posição no ranking de mais votados)" << endl;

        string vot;
        for(Candidate c : election.elected_if_major_election()){
            cout << c.get_geral_position() << " - ";
            if(c.get_party()->get_federation() != -1)
                cout << "*";

            vot = "voto";
            vot = plural_singular_filter(vot, c.get_qt_votos());
            cout << c.get_nm_urna_candidato() << " (" << c.get_party()->get_sg() << ", ";
            
            cout.imbue(locale("pt_BR.utf8"));
            cout << c.get_qt_votos() << " " << vot << ")" << endl;
            cout.imbue(locale("C"));
        }
        cout << endl;
    }

    //====================================================================//
    void benefited_candidates(Election election)
    {
        cout << "Eleitos, que se beneficiaram do sistema proporcional:" << endl;
        cout << "(com sua posição no ranking de mais votados)" << endl;

        string vot;

        for(Candidate c : election.elected_by_proportional()){
            cout << c.get_geral_position() << " - ";
            if(c.get_party()->get_federation() != -1)
                cout << "*";

            vot = "voto";
            vot = plural_singular_filter(vot, c.get_qt_votos());
            cout << c.get_nm_urna_candidato() << " (" << c.get_party()->get_sg() << ", ";
            
            cout.imbue(locale("pt_BR.utf8"));
            cout << c.get_qt_votos() << " " << vot << ")" << endl;
            cout.imbue(locale("C"));
        }
        cout << endl;
    }

    //====================================================================//
    void party_voting_and_elected_candidates(Election election)
    {
        cout << "Votação dos partidos e número de candidatos eleitos:" << endl;

        string vot, nom, cand, ele;
        for(PoliticalParty p : election.get_parties()){
            vot = "voto";
            nom = "nominal";
            cand = "candidato";
            ele = "eleito";

            vot = plural_singular_filter(vot, p.get_total_votes());
            nom = plural_singular_filter(nom, p.get_nominal_votes());
            cand = plural_singular_filter(cand, p.get_elected_amount());
            ele = plural_singular_filter(ele, p.get_elected_amount());

            cout << p.get_position() << " - ";
            cout.imbue(locale("pt_BR.utf8"));
            cout << p.get_sg() << " - " << p.get_number() << ", " << p.get_total_votes() << " " << vot
            << " (" << p.get_nominal_votes() << " " << nom <<  " e " << p.get_legend_votes() << " de legenda), "
            << p.get_elected_amount() << " " << cand << " " << ele << endl;
 
            cout.imbue(locale("C"));
        }
    }

    //====================================================================//
    void first_and_last_candidates_from_parties(Election election)
    {
        cout << "Primeiro e último colocados de cada partido:" << endl;

        string most_vot, least_vot;

        for(PoliticalParty p : election.get_parties_ordered_by_candidates()){

            most_vot = "voto";
            least_vot = "voto";
            most_vot = plural_singular_filter(most_vot, p.most_voted_candidate().get_qt_votos());
            least_vot = plural_singular_filter(least_vot, p.least_voted_candidate().get_qt_votos());

            cout << p.get_position() << " - " << p.get_sg() << " - " << p.get_number() << ", " 
            << p.most_voted_candidate().get_nm_urna_candidato() << " (" << p.most_voted_candidate().get_nr_candidato();

            cout.imbue(locale("pt_BR.utf8"));
            cout << ", " << p.most_voted_candidate().get_qt_votos() << " " << most_vot << ") / ";
            cout.imbue(locale("C"));
            cout << p.least_voted_candidate().get_nm_urna_candidato() << " (" << p.least_voted_candidate().get_nr_candidato();
            cout.imbue(locale("pt_BR.utf8"));
            cout << ", " << p.least_voted_candidate().get_qt_votos() << " " << least_vot << ")" << endl;
            cout.imbue(locale("C"));
        }
        cout << endl;
    }

    //=============================FUNÇÕES QUE AINDA ESTÃO NO MODELO JAVA=======================================//
    void elected_by_age(Election election)
    {
        cout <<"Eleitos, por faixa etária (na data da eleição):" << endl;

        int totalElected = election.elected_amount();

        int f1 = election.elected_amount_by_age(0, 30);
        int f2 = election.elected_amount_by_age(30, 40);
        int f3 = election.elected_amount_by_age(40, 50);
        int f4 = election.elected_amount_by_age(50, 60);
        int f5 = election.elected_amount_by_age(60, 120);

        float p1 = ((float) f1 / (float) totalElected) * 100;
        float p2 = ((float) f2 / (float) totalElected) * 100;
        float p3 = ((float) f3 / (float) totalElected) * 100;
        float p4 = ((float) f4 / (float) totalElected) * 100;
        float p5 = ((float) f5 / (float) totalElected) * 100;

        cout.imbue(locale("pt_BR.utf8"));
        cout << "      Idade < 30: " << f1 << " (" << p1 << "%)" << endl;
        cout << "30 <= Idade < 40: " << f2 << " (" << p2 << "%)" << endl;
        cout << "40 <= Idade < 50: " << f3 << " (" << p3 << "%)" << endl;
        cout << "50 <= Idade < 60: " << f4 << " (" << p4 << "%)" << endl;
        cout << "60 <= Idade     : " << f5 << " (" << p5 << "%)" << endl;
        cout.imbue(locale("C"));
    }

    void elected_by_gender(Election election)
    {
        int total_elected = election.elected_amount();
        cout << "Eleitos, por gênero:" << endl;

        int men = election.elected_men();
        int women = election.elected_women();

        float pmen = ((float)men / (float)total_elected) * 100;
        float pwomen = ((float)women / (float)total_elected) * 100;

        cout.imbue(locale("pt_BR.utf8"));
        cout << "Feminino: " << women << " (" << pwomen << "%)" << endl;
        cout << "Masculino: " << men << " (" << pmen << "%)" << endl;
        cout.imbue(locale("C"));
    }

    void all_voting(Election election)
    {
        int valid_votes = election.get_legend_votes() + election.get_nominal_votes();
        int nominal = election.get_nominal_votes();
        int legend = election.get_legend_votes();

        float p_nominal = ((float)nominal / (float)valid_votes) * 100;
        int p_legend = ((float)legend / (float)valid_votes) * 100;
        
        cout.imbue(locale("pt_BR.utf8"));
        cout << "Total de votos válidos:    " << valid_votes << endl;
        cout << "Total de votos nominais:   " << nominal << " (" << p_nominal << "%)" << endl;
        cout << "Total de votos de legenda: " << legend << " (" << p_legend << "%)" << endl;
        cout.imbue(locale("C"));
    }

    //ESSA FUNÇÃO ESTÁ CORRETA 
    string plural_singular_filter(string out, int value)
    {
        if(value > 1){
            if(out == "nominal") {
                return "nominais";
            }
            return out + "s";
        }
        return out;
    }
