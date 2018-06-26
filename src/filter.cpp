#include "filter.h"

void filter(Parameters& parameters) {

    std::vector<std::string> {"merged_table",
                              "output_file",
                              "heterogametic_sex",
                              "min_hetero_cov",
                              "max_hetero_cov",
                              "max_homo_cov"};

    std::ifstream input_file;
    std::string par = "merged_table";
    input_file.open(parameters.get_value_from_name<std::string>(par));

    std::ofstream output_file;
    par = "output_file";
    output_file.open(parameters.get_value_from_name<std::string>(par));

    par = "heterogametic_sex";
    std::string heterogametic_sex = parameters.get_value_from_name<std::string>(par);
    uint male_order = 0, female_order = 1;
    if (heterogametic_sex == "F" or heterogametic_sex == "f") {
        male_order = 1;
        female_order = 0;
     }

    par = "min_hetero_cov";
    uint min_hetero_cov = parameters.get_value_from_name<int>(par);

    par = "max_hetero_cov";
    uint max_hetero_cov = parameters.get_value_from_name<int>(par);

    par = "max_homo_cov";
    uint max_homo_cov = parameters.get_value_from_name<int>(par);

    std::string line;
    std::vector<std::string> fields;
    uint freq[2] {0, 0};
    uint lines = 0;

    std::cout << " - Filtering table ... " << std::endl;

    while (std::getline(input_file, line)) {

        fields = split(line, "\t");
        freq[male_order] = std::stoi(fields[1]);
        freq[female_order] = std::stoi(fields[2]);

        if (freq[0] >= min_hetero_cov and freq[0] <= max_hetero_cov and freq[1] <= max_homo_cov) output_file << line << "\n";

        if (lines % 10000000 == 0) std::cout << "    -> Processed " << lines % 1000000 << " M. lines." << std::endl;
        ++lines;
    }
}
