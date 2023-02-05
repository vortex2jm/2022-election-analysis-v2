#ifndef input_services
#define input_services

#include <fstream>
#include <string>
#include "./election.hpp"

namespace input_services{
    
    ifstream create_reading_buffer(string file);

    void process_candidates_file(ifstream buffer, Election election);

    void process_votes_file(ifstream buffer, Election election);
}

#endif
