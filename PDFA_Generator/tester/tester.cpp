//
//  tester.cpp
//  PDFA_Generator
//
//  Created by Amalia on 20/07/2023.
//

#include "tester.hpp"
#include "utils.hpp"
#include "avg_length_learner.hpp"

// test constants

Tester::Tester(int pdfas_qty, int ans_index, int samples_qty, string learner_type, int pdfas_size): pdfas_qty(pdfas_qty), ans_index(ans_index), samples_qty(samples_qty), pdfas_size(pdfas_size) {
    // generate the pdfas
    for (int i = 0; i < pdfas_qty; ++i)
        pdfas.push_back(Pdfa_generator(pdfas_size, ALPHABET_SIZE, MIN_TRANSITIONS, MAX_TRANSITIONS));
    
    // generate the output samples
    for (int i = 0; i < samples_qty; ++i) samples.push_back(pdfas[ans_index].output_string());
    
    
    // switch learner type
    if (learner_type == "AVGLEN") {
//        Average_Length_Learner new_learner(samples, pdfas, 10);
//        learner = &new_learner;
        learner.reset(new Average_Length_Learner(samples, pdfas, 10));
    }
//    else {}
}

bool Tester::run_test() {
    
    int learner_result_index = learner->get_result_index();
    
    return ( learner_result_index == ans_index );
}
