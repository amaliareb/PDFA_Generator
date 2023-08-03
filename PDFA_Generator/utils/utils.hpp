#ifndef utils_hpp
#define utils_hpp

#include "pdfa.hpp"

#include <stdio.h>


PDFA Pdfa_generator(int pdfa_size, int alphabet_size, int min_transitions, int max_transitions);

PDFA Pdfa_reader(ifstream &istream);

stringstream output_strings(PDFA pdfa, int string_count);

#endif /* utils_hpp */
