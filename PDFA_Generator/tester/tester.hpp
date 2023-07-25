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

#define PDFA_SIZE 10
#define ALPHABET_SIZE 20
#define MIN_TRANSITIONS 5
#define MAX_TRANSITIONS 15

class Tester {
public:
    // constructor that generates random pdfas and random samples from the answer pdfa
    Tester(int pdfas_qty, int ans_index, int samples_qty, string learner_type, int pdfas_size = PDFA_SIZE);
    
    // returns true if learner guesses correctly
    bool run_test();
    
private:
    std::unique_ptr<PDFA_Learner> learner;
    const int pdfas_qty, ans_index, samples_qty, pdfas_size;
    vector<PDFA> pdfas;
    vector<string> samples;
    
};

#endif /* tester_hpp */
