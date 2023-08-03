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
    
    bool has_transition(int source, int target) const;
    
    bool has_letter(int source, int letter) const;
    
    int max_probability_letter(int state) const;
    
    bool accepts_string(string s) const;
    
    string output_string() const;
    
    string output_pdfa(int precision) const;
    
};

#endif /* pdfa_hpp */
