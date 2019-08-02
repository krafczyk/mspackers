#include <iostream>
#include <string>
#include "ArgParseStandalone.h"
#include <unistd.h>
#include "mspack.h"

int main(int argc, char** argv) {
    // Argument handling
    std::string input_filepath = "";
    std::string output_filepath = "";
    ArgParse::ArgParser Parser("kwaj_pack");
    Parser.AddArgument("-i", "Input file", &input_filepath);
    Parser.AddArgument("-o", "Output file", &output_filepath);
    if(Parser.ParseArgs(argc, argv) < 0) {
        std::cerr << "Problem parsing arguments" << std::endl;
        return 1;
    }
    if(Parser.HelpPrinted()) {
        return 0;
    }

    // Check if input file exists
    if(access(input_filepath.c_str(), F_OK) == -1) {
        std::cerr << "Input file doesn't exist!" << std::endl;
        return 1;
    }

    // Check that we can use libmspack
    int selftest_result = 0;
    MSPACK_SYS_SELFTEST(selftest_result);
    if(selftest_result != MSPACK_ERR_OK) {
        std::cerr << "Incompatible with this build of libmspack\n" << std::endl;
        return 1;
    }
    
    // Create a compressor
    struct mskwaj_compressor* compressor = mspack_create_kwaj_compressor(NULL);
    if(compressor == NULL) {
        std::cerr << "There was a problem creating the compressor" << std::endl;
        return 1;
    }

    // Compress
    int result = compressor->compress(compressor, input_filepath.c_str(), output_filepath.c_str(), -1);
    if(result != MSPACK_ERR_OK) {
        std::cerr << "There was an error compressing!" << std::endl;
        mspack_destroy_kwaj_compressor(compressor);
        return 1;
    }

    // clean up the compressor
    mspack_destroy_kwaj_compressor(compressor);
    return 0;
}
