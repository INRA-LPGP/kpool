#pragma once
#include <string>
#include <fstream>

struct Parameters{

    std::string males_file_path;
    std::string females_file_path;
    std::string output_file_path;
    std::ifstream males_file;
    std::ifstream females_file;
    std::ofstream output_file;
    int min_cov;
    int max_cov;
};
