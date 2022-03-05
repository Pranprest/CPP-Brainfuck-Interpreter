/**
    Interpreter for the Brainfuck esoteric programming language
    @file bfi.cpp bfi.hpp
    @author Pranprest
*/
#include <iostream>
#include <vector>
#include <memory>
#include <stack>
#include "bfi.hpp"

#define curr_cell cells[cell_pointer]
#define curr_watched_cell watched_cells[recursion - 1]
#define curr_nested_instructions nested_instructions[recursion - 1]

#define DEBUG


class BFEnvironment {
    private: 
        std::deque<unsigned char> cells = {0};
        std::vector<int> watched_cells = {0};
        unsigned short int cell_pointer = 0;
        unsigned short int recursion = 0;

    public: 

        void parse_string(std::string base_string) {
            // Treat string as instruction stack
            parse_stack(bfi::str_to_stack(base_string));
        }
        
        // Parses a brainfuck stack 
        void parse_stack(std::stack<char> instruction_stack) {
            // used to identify the function's execution stack 
            recursion++;
            std::string nested_instructions = "";
            int matching_bracket; // declared here because switch cases don't like variable declarations.

            // Parse every instruction in order and pop when done with it
            while(!instruction_stack.empty()) {
                switch(instruction_stack.top()) {
                    case '>':
                        if(cell_pointer == cells.size() - 1) {
                            cells.push_back(0);
                        } 
                        cell_pointer++;
                        break;
                    case '<':
                        if(cell_pointer == 0) {
                            cells.push_front(0);
                        } 
                        cell_pointer--;
                        break;
                    case '+':
                        curr_cell++;
                        break;
                    case '-':
                        curr_cell--;
                        break;
                    case '.':
                        std::cout << curr_cell << std::flush;
                        break;
                    case ',':
                        std::cin >> std::skipws >> curr_cell;
                        break;
                    case '[':
                        // Get every instruction between matching loops n loop them until curr_cell = 0
                        curr_watched_cell = cell_pointer;

                        // Get every instruction between brackets
                        // gets ([) then adds 1 -> (start of the nested instructions)
                        // Pop instructions between [] when done interpreting them
                        // +1 -> the actual bracket position.
                        matching_bracket = bfi::find_matching_brackets(instruction_stack) + 1;
                        // Ignore [
                        instruction_stack.pop();
                        for (int i = 0; i <= matching_bracket - 2; i++) {
                            nested_instructions.push_back(instruction_stack.top());
                            instruction_stack.pop();
                        }

                        while (cells[curr_watched_cell] > 0) {
                            parse_string(nested_instructions);
                        }
                        nested_instructions = "";
                    default:
                        break;
                }
                instruction_stack.pop();
            }
            recursion--;
        }
};


int main() {
    // Hi!
    BFEnvironment bfmain;
    bfmain.parse_string("++++++++[>+++++++++<-]>.>++++++++++[>++++++++++<-]>+++++.>+++[>+++++++++++<-]>.");
    return 0;
}


