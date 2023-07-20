//
//  avg_length_learner.hpp
//  PDFA_Generator
//
//  Created by Amalia on 19/07/2023.
//

#ifndef avg_length_learner_hpp
#define avg_length_learner_hpp

#include "pdfa_learner.hpp"

#include <stdio.h>

class Average_Length_Learner : public PDFA_Learner {
public:
    Average_Length_Learner( vector<string> samples, vector<PDFA> pdfas, int strings_to_generate): PDFA_Learner(samples, pdfas), strings_to_generate(strings_to_generate) {
    }
    
    void run_learner();
    
private:
    // store the average lengths of outputted strings of the set of pdfas
    vector<int> avg_lengths = vector<int>(pdfas.size());
    int strings_to_generate = 1;
};

#endif /* avg_length_learner_hpp */
