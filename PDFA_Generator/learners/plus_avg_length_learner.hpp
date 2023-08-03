#ifndef plus_avg_length_learner_hpp
#define plus_avg_length_learner_hpp

#include "pdfa_learner.hpp"

#define MAX_ALPHABET_SIZE 50

#include <stdio.h>

// average length, narrowed down using most common first letter and string acceptance
class Plus_Average_Length_Learner : public PDFA_Learner {
public:
    Plus_Average_Length_Learner( vector<string> samples, vector<PDFA> pdfas, int strings_to_generate): PDFA_Learner(samples, pdfas), strings_to_generate(strings_to_generate) {
    }
    
    void run_learner();
    
private:
    // store the average lengths of outputted strings of the set of pdfas
    vector<int> avg_lengths = vector<int>(pdfas.size());
    int strings_to_generate = 1;
};
#endif /* plus_avg_length_learner_hpp */
