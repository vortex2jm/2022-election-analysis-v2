#ifndef input_services
#define input_services

#include <fstream>
#include <string>
#include "../domain/election.hpp"

using namespace std;

ifstream create_reading_buffer(string file);

void process_candidates_file(ifstream buffer, Election election);

void process_votes_file(ifstream buffer, Election election);

#endif