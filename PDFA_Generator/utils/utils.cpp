//
//  utils.cpp
//  PDFA_Generator
//
//  Created by Amalia on 20/07/2023.
//

#include "utils.hpp"

#include "pdfa.hpp"

#include <random>
#include <sstream>
#include <fstream>



PDFA Pdfa_generator(int pdfa_size, int alphabet_size, int min_transitions, int max_transitions) {
    // potential parameters: distinguishability?
    // construct empty PDFA
    PDFA pdfa = PDFA(pdfa_size, alphabet_size);
    
    // define constraints
    
    // 1. connect PDFA in a random tree structure, with the root in the final state
    vector<int> in_tree(0), all_states(0);
    in_tree.push_back(pdfa.end_state);
    
    for (int i = 0; i < pdfa_size; ++i) all_states.push_back(i);
    auto rd = random_device {};
    auto rng = default_random_engine { rd() };
    shuffle(all_states.begin(), all_states.end(), rng);
    
    for (auto &state : all_states) {
        // randomly find a target already in the tree and the transition letter
        int target = in_tree[ rand() % in_tree.size() ];
        int letter = rand() % alphabet_size;
        
        // create transition from state to parent
        pdfa.transitions[state][letter] = {target, 1};
        in_tree.push_back(state);
    }
    
    // 2. from each node, add other transitions
    for (int state = 0; state < pdfa_size; ++state) {
        int transitions_to_add = rand() % (max_transitions - min_transitions + 1) + min_transitions - 1;
        while (transitions_to_add) {
            // randomly generate target, letter and probability of new transition
            int target = rand() % pdfa_size + 1;
            while (target == state || pdfa.has_transition(state, target)) {target = rand() % pdfa_size + 1;}
            
            int new_letter = rand() % alphabet_size;
            while (pdfa.has_letter(state, new_letter)) {new_letter = rand() % alphabet_size;}
            
            int new_proportion = rand() % 80 + 10;
            double new_probability = (double)new_proportion / 100;
            
            // make all other transitions smaller
            for (int letter = 0; letter < alphabet_size; ++letter) {
                if (pdfa.has_letter(state, letter)) {
                    pdfa.transitions[state][letter].second *= (1.0 - new_probability);
                }
            }
            
            // add the new transition; decrease counter
            pdfa.transitions[state][new_letter] = {target, new_probability};
            transitions_to_add--;
        }
    }

    return pdfa;
}

stringstream output_strings(PDFA pdfa, int string_count) {
    stringstream output;
    for (int i = 0; i < string_count; ++i) {
        output << pdfa.output_string() << '\n';
    }
    return output;
}

PDFA Pdfa_reader(ifstream &istream) {
    int pdfa_size, alphabet_size;
    istream >> pdfa_size >> alphabet_size;
    vector< vector < pair <int, double> > > transitions(pdfa_size, vector<pair<int, double>> (alphabet_size, {-1, 0.0}));
    for (int source = 0; source < pdfa_size; ++source)
        for (int letter = 0; letter < alphabet_size; ++letter) {
        int target;
        double probability;
        istream >> target >> probability;
        transitions[source][letter] = {target, probability};
    }
    PDFA pdfa = PDFA(pdfa_size, alphabet_size, transitions);
    return pdfa;
}
