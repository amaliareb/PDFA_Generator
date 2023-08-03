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

#define NUM_TESTS 100
#define SET_SIZE 100

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
    ofstream out_pdfa_size;
    out_pdfa_size.open("Pdata_pdfa_size.csv");
    // test with 4 different sample sizes
    out_pdfa_size << "PDFA_size,accuracy\n";
    for (int size = 25; size <= 300; size += 25) {
        out_pdfa_size << size;
        int num_samples = 200;
        double accuracy = 0.0;
        for (int tests = 0; tests < NUM_TESTS; ++tests) {
            Tester test(SET_SIZE, 5, num_samples, "PLUSAVGLEN", size);
            accuracy += test.run_test();
        }
        accuracy /= 1.0 * NUM_TESTS;
        out_pdfa_size << ',' << accuracy;
        out_pdfa_size << '\n';
    }
    out_pdfa_size.close();
    
    /** Second test case: variable alphabet size  */
//    ofstream out_alph_size;
//    out_alph_size.open("Pdata_alph_size.csv");
//    // test with 4 different sample sizes
//    out_alph_size << "alphabet_size,accuracy\n";
//    for (int size = 1; size <= 30; size++) {
//        out_alph_size << size;
//        int num_samples = 500;
//        double accuracy = 0.0;
//        for (int tests = 0; tests < NUM_TESTS; ++tests) {
//            Tester test(SET_SIZE, 5, num_samples, "PLUSAVGLEN", 50, size, max(3 * size / 4, 1) , max(size / 4, 1) );
//            accuracy += test.run_test();
//        }
//        accuracy /= 1.0 * NUM_TESTS;
//        out_alph_size << ',' << accuracy;
//        out_alph_size << '\n';
//    }
//    out_alph_size.close();
    
    /** Third test case: variable transition density  */
//    ofstream out_trans_dens;
//    out_trans_dens.open("data_trans_density.csv");
//    out_trans_dens << "transitions,labels,accuracy\n";
//    for (int min_trans = 1; min_trans <= 28; min_trans++) {
//        out_trans_dens << min_trans << ',';
//        out_trans_dens << min_trans << '-' << min_trans + 2;
//        int num_samples = 500;
//        double accuracy = 0.0;
//        for (int tests = 0; tests < NUM_TESTS; ++tests) {
//            Tester test(SET_SIZE, 5, num_samples, "AVGLEN", 50, 30, min_trans + 2 , min_trans );
//            accuracy += test.run_test();
//        }
//        accuracy /= 1.0 * NUM_TESTS;
//        out_trans_dens << ',' << accuracy;
//        out_trans_dens << '\n';
//    }
//    out_trans_dens.close();
    
    /** Fourth test case: variable transition variance  */
//    ofstream out_trans_var;
//    out_trans_var.open("data_trans_variance.csv");
//    out_trans_var << "transitions,labels,accuracy\n";
//    for (int min_trans = 1; min_trans <= 15; min_trans++) {
//        out_trans_var << min_trans << ',';
//        out_trans_var << min_trans << '-' << 30 - min_trans;
//        int num_samples = 500;
//        double accuracy = 0.0;
//        for (int tests = 0; tests < NUM_TESTS; ++tests) {
//            Tester test(SET_SIZE, 5, num_samples, "AVGLEN", 50, 30, 30 - min_trans , min_trans );
//            accuracy += test.run_test();
//        }
//        accuracy /= 1.0 * NUM_TESTS;
//        out_trans_var << ',' << accuracy;
//        out_trans_var << '\n';
//    }
//    out_trans_var.close();
    
    
    /** Fifth test case: variable set size  */
//    ofstream out_set_size;
//    out_set_size.open("Pdata_set_size_big.csv");
//    // test with 4 different sample sizes
//    out_set_size << "set_size,accuracy\n";
//    for (int size = 100; size <= 1000; size += 100) {
//        out_set_size << size;
//        int num_samples = 500;
//        double accuracy = 0.0;
//        for (int tests = 0; tests < NUM_TESTS; ++tests) {
//            Tester test(size, 5, num_samples, "PLUSAVGLEN", 50, 20, 15, 5);
//            accuracy += test.run_test();
//        }
//        accuracy /= 1.0 * NUM_TESTS;
//        out_set_size << ',' << accuracy;
//        out_set_size << '\n';
//    }
//    out_set_size.close();
    
    
    
    return 0;
}
