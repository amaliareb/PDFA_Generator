//
//  pdfa_learner.hpp
//  PDFA_Generator
//
//  Created by Amalia on 19/07/2023.
//

#ifndef pdfa_learner_hpp
#define pdfa_learner_hpp

#include "pdfa.hpp"

#include <stdio.h>
#include <vector>
#include <string>

class PDFA_Learner {
public:
    // constructor
    PDFA_Learner(vector<string> samples, vector<PDFA> pdfas);
    
    virtual ~PDFA_Learner();
        
    // returns reference directly if result is initialized, runs learner otherwise; cannot return null
    const PDFA get_result();
    
    int get_result_index();
    
protected:
    // pointer to the result PDFA; is initialized after running the learner
    const PDFA* result;
    int result_index;
    const vector<string> samples;
    const vector<PDFA> pdfas;
    
    // learning algorithm, to be instantiated;
    // side-effect -> result is initialized
    void virtual run_learner() = 0;
};

#endif /* pdfa_learner_hpp */
