//
//  pdfa.cpp
//  PDFA_Generator
//
//  Created by Amalia on 19/07/2023.
//

#include <string>
#include <sstream>
#include <fstream>


#include "pdfa.hpp"

#define DELTA 1e-6

char get_character(int x) {
    return (char)x + 'a';
}

// constructor for empty PDFA
PDFA::PDFA(int N_states, int N_alphabet): N_states(N_states), N_alphabet(N_alphabet), start_state(0), end_state(N_states) {
    // initialize transition function with sizes N_states and N_alphabet
    transitions.resize(N_states, vector<pair<int, double>> (N_alphabet, {-1, 0.0}));
}

// constructor when reading a PDFA
PDFA::PDFA(int N_states, int N_alphabet, vector<vector<pair<int, double>>> transitions): N_states(N_states), N_alphabet(N_alphabet), start_state(0), end_state(N_states), transitions(transitions) {
}

bool PDFA::has_transition(int source, int target) const {
    if (target <= start_state || target > end_state) return false;
    if (source < start_state || source >= end_state) return false;
    for (int letter = 0; letter < N_alphabet; ++letter) if (transitions[source][letter].first == target) return true;
    return false;
}

bool PDFA::has_letter(int source, int letter) const {
    if (source < start_state || source >= end_state) return false;
    if (letter < 0 || letter >= N_alphabet) return false;
    return transitions[source][letter].first >= start_state;
}

int PDFA::max_probability_letter(int state) const {
    int ret = 0;
    for (int i = 1; i < N_alphabet; ++i)
        if ( transitions[state][i].second > transitions[state][ret].second ) ret = i;
    return ret;
}

bool PDFA::accepts_string(string s) const {
    int curr_state = 0;
    for (int ind = 0; ind < s.size(); ++ind) {
        if ( curr_state == -1 || curr_state == end_state) return false;
        curr_state = transitions[curr_state][s[ind] - 'a'].first;
    }
    if ( curr_state == end_state ) return true;
    return false;
}


string PDFA::output_string() const {
    stringstream output;
    int current = start_state;
    while (current != end_state) {
        double probability = (double)(rand() % 100) / 100;
        
        for (int letter = 0; letter < N_alphabet; ++letter) {
            if ( transitions[current][letter].first == -1 ) continue;
            probability -= transitions[current][letter].second;
            if ( probability < DELTA ) {
                output << get_character(letter);
                current = transitions[current][letter].first;
                break;
            }
        }
    }
    return output.str();
}

string PDFA::output_pdfa(int precision) const {
    stringstream output;
    output << fixed << showpoint;
    output << setprecision(precision);
    output << N_states << ' ' << N_alphabet << '\n';
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 4; ++j) output << transitions[i][j].first << ' ' << transitions[i][j].second << "  ";
        output << '\n';
    }
    return output.str();
}
