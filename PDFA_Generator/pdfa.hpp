//
//  pdfa.hpp
//  PDFA_Generator
//
//  Created by Amalia on 19/07/2023.
//

#ifndef pdfa_hpp
#define pdfa_hpp

#include <stdio.h>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

class PDFA {

    public:
    
    const int start_state, end_state;
    int N_states, N_alphabet;
    vector<vector<pair<int, double>>> transitions;
    
    // constructor for empty PDFA
    PDFA(int N_states, int N_alphabet);
        
    // constructor when reading a PDFA
    PDFA(int N_states, int N_alphabet, vector<vector<pair<int, double>>> transitions);
    
    bool has_transition(int source, int target);
    
    bool has_letter(int source, int letter);
    
    string output_string();
    
    string output_pdfa(int precision);
    
};

#endif /* pdfa_hpp */
