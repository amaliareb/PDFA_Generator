//
//  plus_avg_length_learner.cpp
//  PDFA_Generator
//
//  Created by Amalia on 28/07/2023.
//

#include "plus_avg_length_learner.hpp"

void Plus_Average_Length_Learner::run_learner() {
    
    // most common first letter
    vector<int> first_letter_freq(MAX_ALPHABET_SIZE);
    for (auto &sample: samples) first_letter_freq[sample[0] - 'a']++;
    int max_letter = 0;
    for ( int letter = 1; letter < MAX_ALPHABET_SIZE; ++letter)
        if(first_letter_freq[letter] > first_letter_freq[max_letter]) max_letter = letter;
    
    vector<bool> deleted(pdfas.size());
    for (int i = 0; i < pdfas.size(); ++i)
        if ( pdfas[i].max_probability_letter(0) != max_letter ) deleted[i] = true;
    
    // ignore candidates that don't accept the string samples
    
    for (int i = 0; i < pdfas.size(); ++i) {
        for ( auto &sample : samples ) if ( !pdfas[i].accepts_string(sample) ) { deleted[i] = true; break; }
    }
    
    // avg len learner
    unsigned long samples_qty = samples.size();
    double avg_sample_length = 0;
    
    for (auto &sample: samples) avg_sample_length += 1.0 * sample.size() / samples_qty;
    
    double min_difference = 1e6;
    
    for (int ind = 0; ind < pdfas.size(); ind++) if ( !deleted[ind] ) {
        double avg_length = 0;
        for (int i = 0; i < strings_to_generate; ++i) {
            unsigned long length = pdfas[ind].output_string().size();
            avg_length += 1.0 * length / strings_to_generate;
        }
        double diff = abs(avg_sample_length - avg_length);
        if (diff < min_difference) {
            result = &pdfas[ind];
            result_index = ind;
            min_difference = diff;
        }
    }
}
