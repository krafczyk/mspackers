#include <iostream>
#include <string>
#include "ArgParseStandalone.h"

int main(int argc [[maybe_unused]], char** argv [[maybe_unused]]) {
    std::string input_filepath = "";
    ArgParse::ArgParser Parse("kwaj_unpack");
    Parse.AddArgument("-i", "Input file", &input_filepath);
    if(Parse.ParseArgs(argc, argv) < 0) {
        std::cerr << "Problem parsing arguments" << std::endl;
        return 1;
    }
    std::cout << "Input file: " << input_filepath << std::endl;
    return 0;
}
