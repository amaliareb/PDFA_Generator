//
//  main.cpp
//  PDFA_Generator
//
//
// 1 States
// 2 start state
// 3 end state
// 4 alphabet
// 5 transition function
// 6 probability on transitions

#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cstdlib>
#include <random>
#include <sstream>

using namespace std;

// TODO float comparison function

class PDFA {

    public:
    
        const int start_state, end_state;
        int N_states, N_alphabet;
        vector<vector<pair<int, double>>> transitions;
    
        PDFA(int N_states, int N_alphabet): start_state(0), end_state(N_states) {
            // initialize transition function with sizes N_states and N_alphabet
            transitions.resize(N_states, vector<pair<int, double>> (N_alphabet, {0, 0.0}));
        }
    
        bool has_transition(int source, int target) {
            if (target <= start_state || target > end_state) return false;
            if (source < start_state || source >= end_state) return false;
            for (int letter = 0; letter < N_alphabet; ++letter) if (transitions[source][letter].first == target) return true;
            return false;
        }
        
        string output_pdfa() {
            stringstream output;
            for (int i = 0; i < 10; ++i) {
                for (int j = 0; j < 4; ++j) output << transitions[i][j].first << ' ' << transitions[i][j].second << "  ";
                output << '\n';
            }
            return string(output);
        }
    
    bool has_letter(int source, int letter) {
        if (source < start_state || source >= end_state) return false;
        if (letter < 0 || letter >= N_alphabet) return false;
        return transitions[source][letter].first > 0;
}
    
    private:
    
};



PDFA Pdfa_generator(int pdfa_size, int alphabet_size, int min_transitions, int max_transitions) {
    // potential parameters: distinguishability?
    // initalize empty PDFA
    PDFA pdfa = PDFA(pdfa_size, alphabet_size);
    
    // define constraints
    
    // 1. connect PDFA in a random tree structure, with the root in the final state
    vector<int> in_tree(0), all_states(0);
    in_tree.push_back(pdfa.end_state);
    
    for (int i = 0; i < pdfa_size; ++i) all_states.push_back(i);
    shuffle(all_states.begin(), all_states.end(), default_random_engine(0));
    
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
        int transitions_to_add = rand() % (max_transitions - min_transitions) + min_transitions;
        while (transitions_to_add) {
            transitions_to_add--;
            // randomly generating target and probability of new transition
            int target = rand() % pdfa_size + 1;
            while (target == state || pdfa.has_transition(state, target)) {target = rand() % pdfa_size + 1;}
            
            int letter = rand() % alphabet_size;
            while (pdfa.has_letter(state, letter)) {letter = rand() % alphabet_size;}
            
            int new_proportion = rand() % 800 + 100;
            double new_probability = (double)new_proportion / 1000;
            cout << state << ' ' << target << ' ' << new_probability << '\n';
            
            // make all other transitions smaller
            for (int letter = 0; letter < alphabet_size; ++letter) {
                if (pdfa.has_letter(state, letter))
                    pdfa.transitions[state][letter].second *= (1.0 - new_probability);
            }
            
            // add transition
            pdfa.transitions[state][letter] = {target, new_probability};
        }
    }

    return pdfa;
}


char get_character(int x) {
    return (char)x + 'a';
}

string output_string(PDFA pdfa) {
    string output;
    int current = 0;
    while (current != pdfa.end_state) {
        // perform transition and add character to string
    }
    return output;
}


vector<string> output_strings(PDFA pdfa, int string_count) {
    vector<string> output;
    for (int i = 0; i < string_count; ++i) {
        output.push_back(output_string(pdfa));
    }
    return output;
}


int main(int argc, const char * argv[]) {
    PDFA pdfa = Pdfa_generator(10, 4, 2, 3);
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 4; ++j) cout << pdfa.transitions[i][j].first << ' ' << pdfa.transitions[i][j].second << "  ";
        cout << '\n';
    }
    return 0;
}
