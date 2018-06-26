#pragma once
#include "unordered_map"
#include "parameters.h"
#include "utils.h"

void merge(Parameters& parameters);

void index_file(std::ifstream& input_file, std::vector<std::string>& index_files_names, std::string suffix);

void process_batch(std::string& file_name, std::ofstream& output_file, uint& kmer_count);
