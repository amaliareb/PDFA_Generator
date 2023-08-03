#include "avg_length_learner.hpp"

#include <string>

void Average_Length_Learner::run_learner() {
    
    unsigned long samples_qty = samples.size();
    double avg_sample_length = 0;
    
    for (auto &sample: samples) avg_sample_length += 1.0 * sample.size() / samples_qty;
    
    double min_difference = 1e6;
    
    for (int ind = 0; ind < pdfas.size(); ind++) {
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
