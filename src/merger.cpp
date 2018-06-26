#include "merger.h"

void merge_tables(Parameters& parameters) {

    std::unordered_map<std::string, std::pair<uint16_t, uint16_t>> table;

    std::string line;
    std::vector<std::string> fields;
    uint line_count = 0;

    std::cout << " - Processing male file" << std::endl;

    while(std::getline(parameters.males_file, line)) {

        if (line_count != 0 and line_count % 10000000 == 0) std::cout << "   -> Processed " << line_count / 1000000 << " M. lines" << std::endl;
        ++line_count;

        fields = split(line, " ");
//        fields[0] = get_canonical_form(fields[0]);
        if (std::stoi(fields[1]) > parameters.min_cov and std::stoi(fields[1]) < parameters.max_cov) table[fields[0]].first = std::stoi(fields[1]);
    }

    std::cout << " - Processing female file" << std::endl;

    line_count = 0;

    while(std::getline(parameters.females_file, line)) {

        if (line_count != 0 and line_count % 10000000 == 0) std::cout << "   -> Processed " << line_count / 1000000 << " M. lines" << std::endl;
        ++line_count;

        fields = split(line, " ");
//        fields[0] = get_canonical_form(fields[0]);
        if (std::stoi(fields[1]) > parameters.min_cov and std::stoi(fields[1]) < parameters.max_cov) table[fields[0]].second = std::stoi(fields[1]);
    }

    std::cout << " - The table contains " << table.size() << " kmers" << std::endl;

    std::cout << " - Writing output file" << std::endl;

    line_count = 0;

    for (auto kmer: table) {

        if (line_count != 0 and line_count % 1000000 == 0) std::cout << "   -> Wrote " << line_count / 1000000 << " kmers " << std::endl;
        ++line_count;

        parameters.output_file << kmer.first << "\t" << kmer.second.first << "\t" << kmer.second.second << "\n";
    }
}
