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
#include <iomanip>
#include <cstdlib>
#include <algorithm>
#include <random>
#include <sstream>
#include <fstream>


#define DELTA 1e-6

using namespace std;


char get_character(int x) {
    return (char)x + 'a';
}


class PDFA {

    public:
    
        const int start_state, end_state;
        int N_states, N_alphabet;
        vector<vector<pair<int, double>>> transitions;
    
        // constructor for empty PDFA
        PDFA(int N_states, int N_alphabet): N_states(N_states), N_alphabet(N_alphabet) ,start_state(0), end_state(N_states) {
            // initialize transition function with sizes N_states and N_alphabet
            transitions.resize(N_states, vector<pair<int, double>> (N_alphabet, {-1, 0.0}));
        }
        
        // constructor when reading a PDFA
        PDFA(int N_states, int N_alphabet, vector<vector<pair<int, double>>> transitions): N_states(N_states), N_alphabet(N_alphabet), start_state(0), end_state(N_states), transitions(transitions) {
        }
    
        bool has_transition(int source, int target) {
            if (target <= start_state || target > end_state) return false;
            if (source < start_state || source >= end_state) return false;
            for (int letter = 0; letter < N_alphabet; ++letter) if (transitions[source][letter].first == target) return true;
            return false;
        }
    
        bool has_letter(int source, int letter) {
            if (source < start_state || source >= end_state) return false;
            if (letter < 0 || letter >= N_alphabet) return false;
            return transitions[source][letter].first >= start_state;
        }
    
        string output_string() {
            stringstream output;
            int current = start_state;
            while (current != end_state) {
                double probability = (double)(rand() % 100) / 100;
                for (int letter = 0; letter < N_alphabet; ++letter) {
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
    
        string output_pdfa(int precision) {
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
    
    
    private:
    
};



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


int main(int argc, const char * argv[]) {
    PDFA pdfa = Pdfa_generator(10, 4, 2, 3);
    
    cout << pdfa.output_pdfa(4);
    
    // test string generator function
    cout << output_strings(pdfa, 10).str();
    
    // test i/o file function
    ifstream pdfa_in;
    ofstream pdfa_out, strings_out;
    pdfa_in.open("pdfa1.in");
    pdfa_out.open("pdfa1.out");
    strings_out.open("strings1.out");
    PDFA copy = Pdfa_reader(pdfa_in);
    pdfa_out << copy.output_pdfa(4);
    strings_out << output_strings(copy, 50).str();
    pdfa_in.close();
    pdfa_out.close();
    strings_out.close();
    return 0;
}
