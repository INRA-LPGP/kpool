#include "arg_parser.h"
#include "merger.h"


int main(int argc, char *argv[]) {

    ArgParser cmd_options(argc, argv);

    Parameters parameters;

    cmd_options.set_parameters(parameters);

    cmd_options.print_parameters();

    merge_tables(parameters);

    return 0;
}
