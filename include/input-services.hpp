#ifndef input_services
#define input_services

#include <fstream>
#include <string>
#include "./election.hpp"

namespace in_service{
    ifstream create_reading_stream(string file);
    void process_candidates_file(ifstream buffer, Election election);
    void process_votes_file(ifstream buffer, Election election);
    std::vector<int> separate_by_slash(std::string date);
}

#endif
