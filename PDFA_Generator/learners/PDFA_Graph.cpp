//
//  PDFA_Graph.cpp
//  PDFA_Generator
//
//  Created by Amalia on 29/06/2023.
//

#include "PDFA_Graph.hpp"

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <algorithm>
#include <random>
#include <sstream>
#include <fstream>
#include <set>

using namespace std;

class PDFA_Graph {
    bool finished;
    vector< vector<int> > transitions, transitions_to_candidates;
    int N_states, N_cands, alphabet_size;
    vector< multiset<string> > cand_sets, node_sets;
    vector<string> D;
    
    // construct graph with only initial state and string sample
    PDFA_Graph(vector<string> D, int alphabet_size): finished(false), alphabet_size(alphabet_size), N_states(1), N_cands(0), transitions(1, vector<int> (alphabet_size, -1)), transitions_to_candidates(1, vector<int> (alphabet_size, -1)) {
        
        node_sets.push_back( multiset<string>(D.begin(), D.end()) ); // the multiset of the start node is composed of all the strings
    }
    
    
public:
    void Construct_graph(vector<string> D, int alphabet_size) {
        vector< vector<int> > transitions, transitions_to_candidates;
        // add start state
        int N_states = 1;
        transitions.resize(N_states, vector<int> (alphabet_size, -1));
        transitions_to_candidates.resize(N_states, vector<int> (alphabet_size, -1));
        bool added = true;
        // construct graph
        while (added) {
            // create candidate nodes
            int current_cand = 0;
            for (int state = 0; state < N_states; ++state)
                for (int letter = 0; letter < alphabet_size; ++letter)
                    if (transitions[state][letter] == -1) {
                        transitions_to_candidates[state][letter] = current_cand;
                        current_cand++;
                    }
            
            // add strings to the multisets of candidate nodes
            int N_cands = current_cand;
            initialize_multisets();
            
            for (auto &sample: D) {
                add_to_multiset(sample);
            }
            
            // take the node with the largest multiset
            int largest_candidate = find_largest_candidate();
            // check that multiset is large enough
            if (check_multiset(largest_candidate) == false) {
                added = false;
                continue;
            }
            
            pair<int, int> edge = find_edge(largest_candidate);
            int lookalike_node = find_lookalike_node(largest_candidate);
            if (lookalike_node == -1) {
                // add candidate node as a state in pdfa
                int new_node = add_node();
                // draw edge to new node
                draw_edge(edge.first, edge.second, new_node);
            }
            else {
                // don't add any new nodes, draw edge to the lookalike node
                draw_edge(edge.first, edge.second, lookalike_node);
            }
            clear_loop_data();
            added = true;
        }
    }
    
    void initialize_multisets() {
        // initializes empty multisets for each of the candidate nodes
        cand_sets.resize(N_cands);
    }
    
    void add_to_multiset(string S) {
        // adds a suffix of S to the multiset of a candidate node if S passes through that candidate node
        int curr_node = 0, S_index = 0;
        while ( transitions[curr_node][S[S_index]] >= 0 ) {
            curr_node = transitions[curr_node][S[S_index]];
            S_index++;
        }
        int cand = transitions_to_candidates[curr_node][S[S_index]];
        S_index++;
        if (cand >= 0) cand_sets[cand].insert(S.substr(S_index, S.length() - S_index));
        // !!!!! this possibly inserts empty strings into multisets - seems like it works though, with the empty string being smaller than any other string
    }
    
    int find_largest_candidate() {
        // returns the index of the candidate node with the largest multiset
        int result = 0;
        for (int i = 0; i < N_cands; ++i) if ( cand_sets[i].size() > cand_sets[result].size() ) result = i;
        return result;
    }
    
    int find_lookalike_node(int candidate) {
        // return node that "looks like" a candidate node
        return -1;
    }
    
    pair<int, int> find_edge(int candidate) {
        // returns {state, letter} pair that connects a candidate node to the graph
        return {0, 0};
    }
    
    void draw_edge(int source, int letter, int target) {
        
    }
    
    int add_node() {
        // returns index of added node
        return -1;
    }
    
    bool check_multiset(int candidate) {
        // returns true if multiset has large enough size, false otherwise
        return false;
    }
    
    void clear_loop_data() {
        // clear intermediate data structures used in the while loop, such as edges to candidate nodes etc.
    }
    
//    PDFA add_probabilities() {
//        return PDFA(0,0);
//    }
    
};
