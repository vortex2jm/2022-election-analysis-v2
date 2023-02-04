#include "../../include/io/output-services.hpp"

#include "../../include/exceptions/reports-generation-exception.hpp"
#include <iostream>
#include <string>

//VERIFICAR SE PRECISA SETTAR O LOCALE PARA C
namespace output_service{

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
    void output_service::generate_reports(Election election) 
    {
        // Formatando os números no padrão brasileiro
        Locale localeBr = Locale.forLanguageTag("pt-BR");
        NumberFormat nf = NumberFormat.getInstance(localeBr);
        NumberFormat nfDec = NumberFormat.getInstance(localeBr);
        nfDec.setMinimumFractionDigits(2);
        nfDec.setMaximumFractionDigits(2);

        try {
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
        } catch (exception& e) {
            throw new reports_generation_exception();
        }
    }

    //====================================================================//
    void output_service::vacancies_number(Election election)
    {
        cout.imbue(std::locale("pt_BR.utf8"));
        cout << "Número de vagas: " << election.elected_amount() << endl;
        cout.imbue(std::locale("C"));
    }

    //====================================================================//
    void output_service::elected_candidates(Election election)
    {
        std::string category = "";
        if(election.get_type() == 6)
            category = "federais";
        else if(election.get_type() == 7)
            category = "estaduais";

        cout << "Deputados " << category <<" eleitos:" << endl;
        std::string vot;

        for(Candidate c : election.elected_candidates()){
            cout << c.get_elected_position() << " - ";
            if(c.get_party()->get_federation() != -1)
                cout << "*";
            
            vot = "voto";
            vot = plural_singular_filter(vot, c.get_qt_votos());
            cout << c.get_nm_urna_candidato() << " (" << c.get_party()->get_sg() << ", ";

            cout.imbue(std::locale("pt_BR.utf8"));
            cout << c.get_qt_votos() << " " << vot << ")" << endl;
            cout.imbue(std::locale("C"));
        }
        cout << endl;
    }

    //====================================================================//
    void output_service::most_voted_candidates(Election election)
    {
        cout << "Candidatos mais votados (em ordem decrescente de votação e respeitando número de vagas):" << endl;

        std::string vot;
        for(Candidate c : election.get_best_candidates()){
             cout << c.get_geral_position() << " - ";
             if(c.get_party()->get_federation() != -1)
                cout << "*";

            vot = "voto";
            vot = plural_singular_filter(vot, c.get_qt_votos());
            cout << c.get_nm_urna_candidato() << " (" << c.get_party()->get_sg() << ", ";
            
            cout.imbue(std::locale("pt_BR.utf8"));
            cout << c.get_qt_votos() << " " << vot << ")" << endl;
            cout.imbue(std::locale("C"));
        }
        cout << endl;
    }

    //====================================================================//
    void output_service::harmed_candidates(Election election)
    {
        cout << "Teriam sido eleitos se a votação fosse majoritária, e não foram eleitos:" << endl;
        cout << "(com sua posição no ranking de mais votados)" << endl;

        std::string vot;
        for(Candidate c : election.elected_if_major_election()){
            cout << c.get_geral_position() << " - ";
            if(c.get_party()->get_federation() != -1)
                cout << "*";

            vot = "voto";
            vot = plural_singular_filter(vot, c.get_qt_votos());
            cout << c.get_nm_urna_candidato() << " (" << c.get_party()->get_sg() << ", ";
            
            cout.imbue(std::locale("pt_BR.utf8"));
            cout << c.get_qt_votos() << " " << vot << ")" << endl;
            cout.imbue(std::locale("C"));
        }
        cout << endl;
    }

    //====================================================================//
    void output_service::benefited_candidates(Election election)
    {
        cout << "Eleitos, que se beneficiaram do sistema proporcional:" << endl;
        cout << "(com sua posição no ranking de mais votados)" << endl;

        std::string vot;

        for(Candidate c : election.elected_by_proportional()){
            cout << c.get_geral_position() << " - ";
            if(c.get_party()->get_federation() != -1)
                cout << "*";

            vot = "voto";
            vot = plural_singular_filter(vot, c.get_qt_votos());
            cout << c.get_nm_urna_candidato() << " (" << c.get_party()->get_sg() << ", ";
            
            cout.imbue(std::locale("pt_BR.utf8"));
            cout << c.get_qt_votos() << " " << vot << ")" << endl;
            cout.imbue(std::locale("C"));
        }
        cout << endl;
    }

    //====================================================================//
    void output_service::party_voting_and_elected_candidates(Election election)
    {
        cout << "Votação dos partidos e número de candidatos eleitos:" << endl;

        std::string vot, nom, cand, ele;
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
            cout.imbue(std::locale("pt_BR.utf8"));
            cout << p.get_sg() << " - " << p.get_number() << ", " << p.get_total_votes() << " " << vot
            << " (" << p.get_nominal_votes() << " " << nom <<  " e " << p.get_legend_votes() << " de legenda), "
            << p.get_elected_amount() << " " << cand << " " << ele << endl;
 
            cout.imbue(std::locale("C"));
        }
    }

    //====================================================================//
    void output_service::first_and_last_candidates_from_parties(Election election)
    {
        cout << "Primeiro e último colocados de cada partido:" << endl;

        std::string most_vot, least_vot;

        for(PoliticalParty p : election.get_parties_ordered_by_candidates()){

            most_vot = "voto";
            least_vot = "voto";
            most_vot = plural_singular_filter(most_vot, p.most_voted_candidate().get_qt_votos());
            least_vot = plural_singular_filter(least_vot, p.least_voted_candidate().get_qt_votos());

            cout << p.get_position() << " - " << p.get_sg() << " - " << p.get_number() << ", " 
            << p.most_voted_candidate().get_nm_urna_candidato() << " (" << p.most_voted_candidate().get_nr_candidato();

            cout.imbue(std::locale("pt_BR.utf8"));
            cout << ", " << p.most_voted_candidate().get_qt_votos() << " " << most_vot << ") / ";
            cout.imbue(std::locale("C"));
            cout << p.least_voted_candidate().get_nm_urna_candidato() << " (" << p.least_voted_candidate().get_nr_candidato();
            cout.imbue(std::locale("pt_BR.utf8"));
            cout << ", " << p.least_voted_candidate().get_qt_votos() << " " << least_vot << ")" << endl;
            cout.imbue(std::locale("C"));
        }
        cout << endl;
    }

    //=============================FUNÇÕES QUE AINDA ESTÃO NO MODELO JAVA=======================================//
    void output_service::elected_by_age(Election election)
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

        System.out.printf("      Idade < 30: %s (%s%%)\n", nf.format(f1), nfDec.format(p1));
        System.out.printf("30 <= Idade < 40: %s (%s%%)\n", nf.format(f2), nfDec.format(p2));
        System.out.printf("40 <= Idade < 50: %s (%s%%)\n", nf.format(f3), nfDec.format(p3));
        System.out.printf("50 <= Idade < 60: %s (%s%%)\n", nf.format(f4), nfDec.format(p4));
        System.out.printf("60 <= Idade     : %s (%s%%)\n\n", nf.format(f5), nfDec.format(p5));
    }

    void output_service::elected_by_gender(Election election)
    {
        int totalElected = election.elected_amount();
        System.out.println("Eleitos, por gênero:");

        int men = election.elected_men();
        int women = election.elected_women();

        float pmen = ((float) men / (float) totalElected) * 100;
        float pwomen = ((float) women / (float) totalElected) * 100;

        System.out.printf("Feminino:  %s (%s%%)\n", nf.format(women), nfDec.format(pwomen));
        System.out.printf("Masculino: %s (%s%%)\n\n", nf.format(men), nfDec.format(pmen));
    }

    void output_service::all_voting(Election election)
    {
        int validVotes = election.get_legend_votes() + election.get_nominal_votes();
        int nominal = election.get_nominal_votes();
        int legend = election.get_legend_votes();

        float pNominal = ((float) nominal / (float) validVotes) * 100;
        float pLegend = ((float) legend / (float) validVotes) * 100;

        System.out.printf("Total de votos válidos:    %s\n", nf.format(validVotes));
        System.out.printf("Total de votos nominais:   %s (%s%%)\n", nf.format(nominal), nfDec.format(pNominal));
        System.out.printf("Total de votos de legenda: %s (%s%%)\n", nf.format(legend), nfDec.format(pLegend));
    }

    //ESSA FUNÇÃO ESTÁ CORRETA 
    string output_service::plural_singular_filter(string out, int value)
    {
        if (value > 1) {
            if (out == "nominal") {
                return "nominais";
            }
            return out + "s";
        }
        return out;
    }
}