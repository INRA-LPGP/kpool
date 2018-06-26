#include "merge.h"


void merge(Parameters& parameters) {

    // Open input files
    std::ifstream male_table_file, female_table_file;
    std::string par = "male_table";
    male_table_file.open(parameters.get_value_from_name<std::string>(par));
    par = "female_table";
    female_table_file.open(parameters.get_value_from_name<std::string>(par));

    std::ofstream output_file;
    par = "output_file";
    output_file.open(parameters.get_value_from_name<std::string>(par));

    std::vector<std::string> index_files_names {"AA", "AT", "AG", "AC",
                                                "TA", "TT", "TG", "TC",
                                                "CA", "CT", "CG", "CC",
                                                "GA", "GT", "GG", "GC"};

    std::cout << "# Indexing kmer tables ..." << std::endl;
    std::thread male_thread(index_file, std::ref(male_table_file), std::ref(index_files_names), "_m");
    std::thread female_thread(index_file, std::ref(female_table_file), std::ref(index_files_names), "_f");
    male_thread.join();
    female_thread.join();

    uint kmer_count = 0;

    std::cout << "# Merging indexed files ..." << std::endl;
    for (auto file_name: index_files_names) {
        process_batch(file_name, output_file, kmer_count);
        remove((file_name + "_m" + ".kpool.tmp").c_str());
        remove((file_name + "_f" + ".kpool.tmp").c_str());
    }

    std::cout << "# Final kmers count : " << kmer_count << std::endl;
}



void index_file(std::ifstream& input_file, std::vector<std::string>& index_files_names, std::string suffix) {

    std::unordered_map<std::string, std::ofstream> index_files;
    std::map<std::string, std::string> sex_corr {{"_m", "Males"}, {"_f", "Females"}};

    for (auto file_name: index_files_names) index_files[file_name].open(file_name + suffix + ".kpool.tmp");

    std::string line;
    uint lines = 0;

    while (std::getline(input_file, line)) {

        if (lines % 25000000 == 0) std::cout << " - " << sex_corr[suffix] << " file : processed " << lines / 1000000 << " M. lines." << std::endl;
        ++lines;
        index_files[line.substr(0, 2)] << line << "\n";
    }

    for (auto file_name: index_files_names) index_files[file_name].close();
}



void process_batch(std::string& file_name, std::ofstream& output_file, uint& kmer_count) {

    std::unordered_map<std::string, std::pair<uint32_t, uint32_t>> table;

    std::ifstream male_file, female_file;
    male_file.open(file_name + "_m" + ".kpool.tmp");
    female_file.open(file_name + "_f" + ".kpool.tmp");

    std::string line;
    std::vector<std::string> fields;

    std::cout << " - Processing batch \"" << file_name << "\" ..." << std::endl;
    std::cout << "    -> Processing male file ..." << std::endl;

    while(std::getline(male_file, line)) {
        fields = split(line, " ");
        table[fields[0]].first = std::stoi(fields[1]);
    }

    std::cout << "    -> Processing female file ..." << std::endl;

    while(std::getline(female_file, line)) {
        fields = split(line, " ");
        table[fields[0]].second = std::stoi(fields[1]);
    }

    std::cout << "    -> Found " << table.size() << " total kmers in this batch." << std::endl;

    kmer_count += table.size();

    std::cout << "    -> Writing to output file ... " << std::endl;

    for (auto kmer: table) {
        output_file << kmer.first << "\t" << kmer.second.first << "\t" << kmer.second.second << "\n";
    }
}
