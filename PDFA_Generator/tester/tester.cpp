//
//  tester.cpp
//  PDFA_Generator
//
//  Created by Amalia on 20/07/2023.
//

#include "tester.hpp"
#include "utils.hpp"
#include "avg_length_learner.hpp"
#include "plus_avg_length_learner.hpp"

// test constants

Tester::Tester(int pdfas_qty, int ans_index, int samples_qty, string learner_type, int pdfas_size, int alphabet_size, int max_trans, int min_trans): pdfas_qty(pdfas_qty), ans_index(ans_index), samples_qty(samples_qty), pdfas_size(pdfas_size), alphabet_size(alphabet_size), max_trans(max_trans), min_trans(min_trans) {
    // generate the pdfas
    for (int i = 0; i < pdfas_qty; ++i)
        pdfas.push_back(Pdfa_generator(pdfas_size, alphabet_size, min_trans, max_trans));
    
    // generate the output samples
    for (int i = 0; i < samples_qty; ++i) samples.push_back(pdfas[ans_index].output_string());
    
    
    // switch learner type
    if (learner_type == "AVGLEN") {
//        Average_Length_Learner new_learner(samples, pdfas, 10);
//        learner = &new_learner;
        learner.reset(new Average_Length_Learner(samples, pdfas, samples_qty));
    }
    else if ( learner_type == "PLUSAVGLEN" ) {
        learner.reset(new Plus_Average_Length_Learner(samples, pdfas, samples_qty));

    }
}

bool Tester::run_test() {
    
    int learner_result_index = learner->get_result_index();
    
    return ( learner_result_index == ans_index );
}
