#include "kpool.h"


int main(int argc, char* argv[]) {


    /* Kpool is a class that controls the entire programme
     * This class creates one object for each type of analysis.
     * Each analysis object will has its own parser to handle its specific arguments.
     * During initialization, the main parser is first run to check the type of analysis selected,
     * then the analysis-specific parser is run to parser the analysis-specific arguments.
     */

    Kpool kpool(argc, argv);

    // If everything went well, the analysis is run
    kpool.run();

    return 0;
}
