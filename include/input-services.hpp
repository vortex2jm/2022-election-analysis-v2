#ifndef input_services
#define input_services

#include <fstream>
#include <string>
#include "./election.hpp"

namespace in_service{
    ifstream create_reading_stream(string file);
    void process_candidates_file(ifstream& stream, Election& election);
    void process_votes_file(ifstream& stream, Election& election);
    vector<string> split(string input, char delimiter);
}

#endif
