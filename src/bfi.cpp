/**
    Interpreter for the Brainfuck esoteric programming language
    @file bfi.cpp bfi.hpp
    @author Pranprest
*/
#include "bfi.hpp"
#include <fstream>
#include <algorithm>

#define BASE_FILE argv[1]

// #define DEBUG

// Self explanatory. Returns TRUE or FALSE
inline bool check_file_exists(const std::string& filename) {
    std::ifstream infile(filename);
    return infile.good();
}

// Check if character is a valid brainfuck operation
bool is_valid_bf(char coolchar) {
    switch (coolchar)
    {
        case '>':
        case '<':
        case '+':
        case '-':
        case '[':
        case ']':
        case ',':
        case '.':
            return true;
            break;
        default:
            return false;
            break;
    }
}

// Read file and output every single character to a vector
std::string get_bf_str(const std::string& filename) {
    std::fstream coolfile(filename);
    std::string main_str;

    if (coolfile.is_open()) { 
        std::string line;
        while(getline(coolfile, line)){ 
            line.erase(
                std::remove_if (
                    line.begin(), 
                    line.end(), 
                    [](const char& c) { return !is_valid_bf(c); } 
                    ), line.end());
            main_str.append(line);
        }
        coolfile.close();
    } else {
        std::cerr << "Runtime exception ocourred when opening/reading/closing file\n";
        exit(1);
    }

    return main_str;
}

int main(int argc, const char** argv) {
    #ifdef DEBUG
        argc = 2;
        BASE_FILE = "../sample/hi.bf";
    #endif

    if (argc <= 1) {
        std::cout << "Usage: cbfi [filename]" << "\n\n";
        std::cout << "  [filename] must be a brainfuck file!" << std::endl;
        return EXIT_SUCCESS;
    } else {
        if (check_file_exists(BASE_FILE)) {
            bfi::interpret_bf_str(get_bf_str(BASE_FILE));
            std::cout << std::endl;
            return EXIT_SUCCESS;
        } else {
            std::cerr << "File does not exist (or is not valid)" << std::endl;
            return EXIT_FAILURE;
        }
    }
}


