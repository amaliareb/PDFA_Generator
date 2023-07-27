//
//  main.cpp
//  PDFA_Generator
//
//
// 1 States
// 2 start state
// 3 end state
// 4 alphabet
// 5 transition function
// 6 probability on transitions

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <set>

#include "pdfa.hpp"
#include "utils.hpp"
#include "tester.hpp"
#include "avg_length_learner.hpp"

#define NUM_TESTS 10

using namespace std;


int main(int argc, const char * argv[]) {
    // testing pdfa generator
    PDFA pdfa = Pdfa_generator(10, 4, 2, 3);

    cout << pdfa.output_pdfa(4);

    // test string generator function
    cout << output_strings(pdfa, 10).str();

    // test i/o file function
//    ifstream pdfa_in;
//    ofstream pdfa_out, strings_out;
//    pdfa_in.open("pdfa1.in");
//    pdfa_out.open("pdfa1.out");
//    strings_out.open("strings1.out");
//    PDFA copy = Pdfa_reader(pdfa_in);
//    // pdfa_out << copy.output_pdfa(4);
//    cout << copy.output_pdfa(4);
//    // strings_out << output_strings(copy, 50).str();
//    cout << output_strings(copy, 50).str();
//    pdfa_in.close();
//    pdfa_out.close();
//    strings_out.close();
    
    // test tester
//    for (int i = 0; i < 10; ++i) {
//        Tester test(2, 0, 5, "AVGLEN");
//
//        cout << test.run_test() << '\n';
//    }
     
    cout << "got here\n";
    
    /** First test case: variable PDFA size  */
//    ofstream out_pdfa_size;
//    out_pdfa_size.open("data_pdfa_size.csv");
//    // test with 4 different sample sizes
//    out_pdfa_size << "PDFA_size,acc25,acc50,acc75,acc100\n";
//    for (int size = 50; size <= 200; size += 50) {
//        out_pdfa_size << size;
//        for (int num_samples = 25; num_samples <= 100; num_samples += 25) {
//            double accuracy = 0.0;
//            for (int tests = 0; tests < NUM_TESTS; ++tests) {
//                Tester test(10, 0, num_samples, "AVGLEN", size);
//                accuracy += test.run_test();
//            }
//            accuracy /= 1.0 * NUM_TESTS;
//            out_pdfa_size << ',' << accuracy;
//        }
//        out_pdfa_size << '\n';
//    }
//    out_pdfa_size.close();
    
    /** Second test case: variable alphabet size  */
//    ofstream out_alph_size;
//    out_alph_size.open("data_alph_size.csv");
//    // test with 4 different sample sizes
//    out_alph_size << "alphabet_size,acc25,acc50,acc75,acc100\n";
//    for (int size = 1; size <= 30; size++) {
//        out_alph_size << size;
//        for (int num_samples = 25; num_samples <= 100; num_samples += 25) {
//            double accuracy = 0.0;
//            for (int tests = 0; tests < NUM_TESTS; ++tests) {
//                Tester test(10, 0, num_samples, "AVGLEN", 50, size, max(3 * size / 4, 1) , max(size / 4, 1) );
//                accuracy += test.run_test();
//            }
//            accuracy /= 1.0 * NUM_TESTS;
//            out_alph_size << ',' << accuracy;
//        }
//        out_alph_size << '\n';
//    }
//    out_alph_size.close();
    
    /** Third test case: variable transition density  */
//    ofstream out_trans_dens;
//    out_trans_dens.open("data_trans_density.csv");
//    // test with 4 different sample sizes
//    out_trans_dens << "transitions,acc25,acc50,acc75,acc100\n";
//    for (int min_trans = 1; min_trans <= 28; min_trans++) {
//        out_trans_dens << min_trans;
//        for (int num_samples = 50; num_samples <= 200; num_samples += 50) {
//            double accuracy = 0.0;
//            for (int tests = 0; tests < NUM_TESTS; ++tests) {
//                Tester test(10, 0, 200, "AVGLEN", 50, 30, min_trans + 2 , min_trans );
//                accuracy += test.run_test();
//            }
//            accuracy /= 1.0 * NUM_TESTS;
//            out_trans_dens << ',' << accuracy;
//        }
//        out_trans_dens << '\n';
//    }
//    out_trans_dens.close();
    
    /** Fourth test case: variable transition variance  */
//    ofstream out_trans_var;
//    out_trans_var.open("data_trans_variance.csv");
//    // test with 4 different sample sizes
//    out_trans_var << "transitions,acc25,acc50,acc75,acc100\n";
//    for (int min_trans = 1; min_trans <= 15; min_trans++) {
//        out_trans_var << min_trans;
//        for (int num_samples = 25; num_samples <= 100; num_samples += 25) {
//            double accuracy = 0.0;
//            for (int tests = 0; tests < NUM_TESTS; ++tests) {
//                Tester test(10, 0, num_samples, "AVGLEN", 50, 30, 30 - min_trans , min_trans );
//                accuracy += test.run_test();
//            }
//            accuracy /= 1.0 * NUM_TESTS;
//            out_trans_var << ',' << accuracy;
//        }
//        out_trans_var << '\n';
//    }
//    out_trans_var.close();
    
    
    /** Fifth test case: variable set size  */
//    ofstream out_set_size;
//    out_set_size.open("data_set_size.csv");
//    // test with 4 different sample sizes
//    out_set_size << "set_size,acc25,acc50,acc75,acc100\n";
//    for (int size = 1; size <= 30; size++) {
//        out_set_size << size;
//        for (int num_samples = 25; num_samples <= 100; num_samples += 25) {
//            double accuracy = 0.0;
//            for (int tests = 0; tests < NUM_TESTS; ++tests) {
//                Tester test(size, 0, num_samples, "AVGLEN", 20);
//                accuracy += test.run_test();
//            }
//            accuracy /= 1.0 * NUM_TESTS;
//            out_set_size << ',' << accuracy;
//        }
//        out_set_size << '\n';
//    }
//    out_set_size.close();
    
    
    
    return 0;
}
