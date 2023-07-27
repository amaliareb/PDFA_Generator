//
//  tester.hpp
//  PDFA_Generator
//
//  Created by Amalia on 20/07/2023.
//

#ifndef tester_hpp
#define tester_hpp

#include "pdfa_learner.hpp"
#include "pdfa.hpp"

#include <stdio.h>
#include <vector>
#include <string>

#define PDFA_SIZE 20
#define ALPHABET_SIZE 10
#define MIN_TRANSITIONS 2
#define MAX_TRANSITIONS 8

class Tester {
public:
    // constructor that generates random pdfas and random samples from the answer pdfa
    Tester(int pdfas_qty, int ans_index, int samples_qty, string learner_type, int pdfas_size = PDFA_SIZE, int alphabet_size = ALPHABET_SIZE, int max_trans = MAX_TRANSITIONS, int min_trans = MIN_TRANSITIONS);
    
    // returns true if learner guesses correctly
    bool run_test();
    
private:
    std::unique_ptr<PDFA_Learner> learner;
    const int pdfas_qty, ans_index, samples_qty, pdfas_size, alphabet_size, max_trans, min_trans;
    vector<PDFA> pdfas;
    vector<string> samples;
    
};

#endif /* tester_hpp */
