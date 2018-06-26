#include "arg_parser.h"


ArgParser::ArgParser(int &argc, char **argv) {

    for (auto i=1; i < argc; ++i) this->fields.push_back(std::string(argv[i]));

    if (this->contains("-h")) {
        this->usage();
        exit(0);
    }

    if (!this->contains("-m")) {
        std::cout << std::endl << "** Error: no male kmers file specified" << std::endl;
        this->usage();
        exit(0);
    }

    if (!this->contains("-f")) {
        std::cout << std::endl << "** Error: no female kmers file specified" << std::endl;
        this->usage();
        exit(0);
    }

    if (!this->contains("-o")) {
        std::cout << std::endl << "** Error: no output file specified" << std::endl;
        this->usage();
        exit(0);
    }

    if (!this->contains("-i")) {
        std::cout << std::endl << "** Error: no minimum coverage specified" << std::endl;
        this->usage();
        exit(0);
    }

    if (!this->contains("-a")) {
        std::cout << std::endl << "** Error: no maximum coverage specified" << std::endl;
        this->usage();
        exit(0);
    }
}



void ArgParser::set_parameters(Parameters& parameters) {

    parameters.males_file_path = this->set_value("-m");
    parameters.females_file_path = this->set_value("-f");
    parameters.output_file_path = this->set_value("-o");
    parameters.min_cov = std::stoi(this->get_value("-i")) - 1;
    parameters.max_cov = std::stoi(this->get_value("-a")) + 1;

    parameters.males_file.open(parameters.males_file_path);

    if (not parameters.males_file.is_open()) {
        std::cout << "Error: cannot open input file (" << parameters.males_file_path << ")." << std::endl;
        exit(0);
    }

    parameters.females_file.open(parameters.females_file_path);

    if (not parameters.females_file.is_open()) {
        std::cout << "Error: cannot open snps file (" << parameters.females_file_path << ")." << std::endl;
        exit(0);
    }

    parameters.output_file.open(parameters.output_file_path);

    if (not parameters.output_file.is_open()) {
        std::cout << "Error: cannot open output file (" << parameters.output_file_path << ")." << std::endl;
        exit(0);
    }
}



const std::string ArgParser::get_value(const std::string& setting) const {

    std::vector<std::string>::const_iterator itr = std::find(this->fields.begin(), this->fields.end(), setting);

    if (itr != this->fields.end() && ++itr != this->fields.end()) {

        return *itr;
    }

    return "";
}



bool ArgParser::contains(const std::string &option) const {

    return std::find(this->fields.begin(), this->fields.end(), option) != this->fields.end();
}



const std::string ArgParser::set_value(const std::string& field) {

    if (this->contains(field)) return this->get_value(field);
    else  return this->options.at(std::string(field))[0];
}



void ArgParser::usage() {

    std::cout << std::endl << "Usage: kmer_tables_merger -m male_kmers_table.tsv -f female_kmers_table.tsv -o output_file.tsv -i min_cov -a max_cov" << std::endl;
    std::cout << std::endl;
}



void ArgParser::print_parameters() {

    std::cout << "\n- Parameters:\n";
    for (auto o: this->options) {
        if (o.first != "-h") std::cout << "\t" << "- " << o.second[2] << " : " << this->set_value(o.first) << "\n";
    }

    std::cout << "\n";
}
