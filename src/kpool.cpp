#include "kpool.h"

Kpool::Kpool(int& argc, char** argv) {

    /* The Kpool constructor checks the first two command-line arguments to detect the type of analysis
     */

    if (argc < 2) {
        this->usage();
        exit(0);
    }

    if (this->analyses.find(argv[1]) == this->analyses.end()) {
        std::cout << std::endl << "** Error: \"" << argv[1] << "\" is not a valid command." << std::endl;
        this->usage();
        exit(0);
    }

    // Command-line arguments are stored to be used by the analysis-specific parser
    this->argc = argc;
    this->argv = argv;

    // The analysis to run is stored
    this->analysis = this->analyses[argv[1]];

    // Command-line arguments are parsed
    this->parse();
}



void Kpool::usage() {

    /* Simply prints the general usage of radsex
     */

    std::cout << std::endl << "Usage: kpool <command> [options]" << std::endl;
    std::cout << std::endl << "Commands:" << std::endl;
    for (auto analysis: this->analyses) std::cout << "\t" << analysis.first << "\t" << analysis.second.description << std::endl;
    std::cout << std::endl;
}



void Kpool::usage(Analysis analysis) {

    /* Prints usage for the specified analysis
     */

    Parameter temp;
    std::cout << std::endl << "Usage: kpool " << analysis.name << " ";
    for (auto p: this->analysis.options) {
        temp = this->parameters.get_from_name(p);
        if (temp.required) std::cout << temp.flag << " " << temp.name << " ";
    }
    std::cout << " [ ";
    for (auto p: this->analysis.options) {
        temp = this->parameters.get_from_name(p);
        if (!temp.required) std::cout << temp.flag << " " << temp.name << " ";
    }
    std::cout << "]";
    std::cout << std::endl << std::endl << "Options:" << std::endl;
    for (auto p: this->analysis.options){
        temp = this->parameters.get_from_name(p);
        std::cout << "\t" << temp.flag << "\t" << temp.name << "\t<" << temp.type << ">\t" << temp.description << "\t[" << temp.default_value << "]" << std::endl;
    }
    std::cout << std::endl;
}



void Kpool::run() {

    /* Runs the function associated with the selected analysis
     */

    this->analysis.run(this->parameters);
}



void Kpool::parse() {

    // Command-line arguments are stored in a vector to facilitate processing later
    std::vector<std::string> fields;
    for (auto i=2; i < argc; ++i) fields.push_back(std::string(argv[i]));

    // Store user-defined parameter values in the appropriate parameters
    for (auto it=fields.begin(); it != fields.end(); ++it) {
        if ((*it)[0] == '-' and (*it) != "-h") {
            if (this->parameters.find_flag(*it)) {
                parameters.set_value_from_flag(*it, *(std::next(it)));
            } else {
                std::cout << "\n** Warning: parameter (" << (*it) << ") does not exist." << std::endl;
            }
        }
    }

    // Check that all required parameters for the selected analysis were set by the user
    Parameter option;
    for (auto option_name: this->analysis.options) {
        option = parameters.get_from_name(option_name);
        if (option.required and std::find(fields.begin(), fields.end(), option.flag) == fields.end()) {
            std::cout << "\n** Error: the parameter " << option.name << " (" << option.flag << ") is required." << std::endl;
            this->usage(this->analysis);
            exit(0);
        }
    }

    this->parameters.simple_print(this->analysis.options);

    // Test all parameter values and output an appropriate error message is the test fails
    bool success = true;
    for (auto p: this->analysis.options) {
        option = this->parameters.get_from_name(p);
        if (!option.test_value()) {
            std::cout << "**Error: incorrect value \"" << option.value << "\" for parameter \"" << option.name << "\", which should be";
            if (option.internal_type == "bool") std::cout << " a boolean (0/1).";
            else if (option.internal_type == "int") std::cout << " an integer.";
            else if (option.internal_type == "ifile") std::cout << " a path to an existing file.";
            else if (option.internal_type == "ofile") std::cout << " a valid path to an output file.";
            else if (option.internal_type == "dir") std::cout << " a path to an existing directory.";
            std::cout << std::endl;
            success = false;
        }
    }
    if (!success) {
        this->usage(this->analysis);
        exit(0);
    }
}
