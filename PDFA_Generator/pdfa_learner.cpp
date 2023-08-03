#include "pdfa_learner.hpp"
#include <vector>

PDFA_Learner::PDFA_Learner(vector<string> samples, vector<PDFA> pdfas): samples(samples), pdfas(pdfas) {};

PDFA_Learner::~PDFA_Learner() {};
    
// returns result directly if initialized, runs learner otherwise
const PDFA PDFA_Learner::get_result() {
    if (result == nullptr) {
        run_learner();
    }
    return *result;
}

int PDFA_Learner::get_result_index() {
    if (result == nullptr) {
        run_learner();
    }
    return result_index;
}
