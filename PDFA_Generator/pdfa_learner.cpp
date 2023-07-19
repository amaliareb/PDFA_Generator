//
//  pdfa_learner.cpp
//  PDFA_Generator
//
//  Created by Amalia on 19/07/2023.
//

#include "pdfa_learner.hpp"

PDFA_Learner::PDFA_Learner(vector<string> samples, vector<PDFA> pdfas): samples(samples), pdfas(pdfas);
    
// returns result directly if initialized, runs learner otherwise
PDFA PDFA_Learner::get_result() {
    if (result == nullptr) {
        run_learner();
    }
    return result;
}
