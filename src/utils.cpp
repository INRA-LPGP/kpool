#include "utils.h"


std::unordered_map<char, char> revcomp_table {{'A', 'T'}, {'T', 'A'}, {'G', 'C'}, {'C', 'G'}};


uint32_t fast_stoi(const char* str){

    uint32_t val = 0;
    while( *str ) {
        val = val*10 + (*str++ - '0');
    }
    return val;
}



// Splits a std::string into a std::vector of std::strings according to a specified delimiter (default: \t)
std::vector<std::string> split(std::string str, const std::string delimiter){

    std::vector<std::string> output;
    size_t pos;

    while ((pos = str.find(delimiter)) != std::string::npos){

        output.push_back(str.substr(0, pos));
        str.erase(0, pos + delimiter.length());
    }

    output.push_back(str.substr(0, pos));

    return output;
}



std::string get_canonical_form(std::string& sequence) {

    std::string revcomp = sequence;
    uint l = revcomp.size() - 1;
    for (int i = l; i > -1; --i) {
        revcomp[l - i] = revcomp_table[sequence[i]];
    }

    if (sequence.compare(revcomp) > 0) std::cout << sequence << "\t" << revcomp << "\t" << sequence.compare(revcomp) << "\n";

    if (sequence.compare(revcomp) < 0) {
        return sequence;
    } else {
        return revcomp;
    }
}
