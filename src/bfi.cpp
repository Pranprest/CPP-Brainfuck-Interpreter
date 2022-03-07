/**
    Interpreter for the Brainfuck esoteric programming language
    @file bfi.cpp bfi.hpp
    @author Pranprest
*/
#include "bfi.hpp"
#include <sys/stat.h>
#include <fstream>

// #define DEBUG


bool check_file_exists(const std::string& filename) {
    // Make a buffer
    struct stat buffer;
    // If there isn't any file info in (filename), return false   
    return (stat(filename.c_str(), &buffer) == 0); 
}

// Read file and output every single character to a vector
std::string get_bf_str(const std::string& filename) {
    std::fstream coolfile(filename);
    std::string allowed_instructions = "+-.,><[]";
    std::string main_str;

    char c;
    if (coolfile.is_open()) {
        while(coolfile.get(c)) {
            // Only get allowed characters!!
            if(allowed_instructions.find(c) != std::string::npos) {
                main_str.push_back(c);
            }
        }
        coolfile.close();
    }
    return main_str;
}

int main(int argc, const char** argv) {
    #ifdef DEBUG
        argc = 2;
        argv[1] = "../sample/echo.bf";
    #endif

    if (argc <= 1) {
        std::cout << "Usage: " << argv[0] << " [filename]" << std::endl << '\n';
        std::cout << "[filename] must be a brainfuck file!" << std::endl;
        return EXIT_SUCCESS;
    } else {
        if (check_file_exists(argv[1]) == true) {
            // std::cout << "file exists" << '\n';
            // filter_bf_chars(coolstr);
            bfi::parse_string(get_bf_str(argv[1]));
            std::cout << std::endl;
            return EXIT_SUCCESS;
        } else {
            std::cout << "File does not exist (or is not valid)" << '\n';
            return EXIT_FAILURE;
        }
    }
}


