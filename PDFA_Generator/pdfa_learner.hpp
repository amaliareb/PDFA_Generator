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

class PDFA_Learner {
public:
    // constructor
    PDFA_Learner(vector<string> samples, vector<PDFA> pdfas);
        
    // returns result directly if initialized, runs learner otherwise
    PDFA get_result();
    
protected:
    PDFA result;
    const vector<string> samples;
    const vector<PDFA> pdfas;
    
    // learning algorithm, to be instantiated;
    // side-effect -> result is initialized
    void virtual run_learner() = 0;
    

};

#endif /* pdfa_learner_hpp */
