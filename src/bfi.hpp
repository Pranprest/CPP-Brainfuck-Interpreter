#include <iostream>
#include <stack>

#define curr_cell cells.at(cell_pointer)

// This whole namespace is basically just solutions to things that I didn't find in the C++ STL
namespace bfi {
    int find_matching_brackets(const std::string &base_string, size_t &reference_index) {
        // call this function when trying to interpret a [ instruction (get the reference ['s index!)
        // finds matching closing bracket relative to first bracket found 
        int balance = 1; 
        if (reference_index < 0) {
            reference_index = base_string.find_first_of('[');
        }
        if (!base_string.find_last_of(']')) {
            throw std::invalid_argument("No closing bracket was found.");
        }
        for (size_t index = reference_index; index <= base_string.length(); index++) {
            if(base_string.at(index) == '[') { balance++; };
            if(base_string.at(index) == ']') { balance--; };
            if(balance == 0) {return index; };
        }
        return reference_index;
    }

    int find_matching_brackets(std::stack<uint_least8_t> base_stack) {
        // when calling this function, make sure the top element is a "["
        int brackets = 1; 
        int index = 0;
        // if the first element isn't '[' find the first '[' possible.
        while(base_stack.top() != '[') {
            base_stack.pop();
        }
        // Ignore first [
        base_stack.pop();

        while(!base_stack.empty()) {
            if(base_stack.top() == '[') { brackets++; };
            if(base_stack.top() == ']') { brackets--; };
            if(brackets == 0) {return index; };
            base_stack.pop();
            index++;
        }
        return index;
    }

    std::stack<uint_least8_t> str_to_stack(const std::string &base_string) {
        std::stack<uint_least8_t> char_stack;
        // For each character in reversed base_string
        // Push it to char_stack
        std::string reversed (base_string.rbegin(), base_string.rend());
        for (char str_char : reversed) {
            char_stack.push(str_char);
        }
        return char_stack;
    }

    std::string stack_to_str(std::stack<uint_least8_t> &sample_stack) {
        std::string end_str;
        while(!sample_stack.empty()) {
            end_str.push_back(sample_stack.top());
            sample_stack.pop();
        }
        return end_str;
    }

    void print_stack(std::stack<uint_least8_t> sample_stack) {
        // prints every value on a stack
        while(!sample_stack.empty()) {
            std::cout << sample_stack.top();
            sample_stack.pop();
        }
        std::cout << '\n';
    }

    void interpret_bf_str(const std::string &bf_string) {
        static std::deque<uint_least8_t> cells = {0};
        static uint32_t cell_pointer = 0;
        static uint32_t recursion = 0;
        std::stack<uint_least8_t> instruction_stack = bfi::str_to_stack(bf_string);
        // used to identify the function's execution stack 
        recursion++;
        // declared here because switch cases don't like variable declarations.
        std::string nested_instructions = "";
        int matching_bracket; 

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
                    // Get every element between brackets (] - 1!)
                    matching_bracket = bfi::find_matching_brackets(instruction_stack);
                    instruction_stack.pop(); // DO NOT move this over "matching bracket" by any circumstance, or else everything will break!
                    for (size_t i = 0; i <= matching_bracket - 1; i++) {
                        nested_instructions.push_back(instruction_stack.top());
                        instruction_stack.pop();
                    }
                    if(curr_cell == 0) {
                        nested_instructions = "";
                        break;
                    }
                    while (curr_cell > 0) {
                        bfi::interpret_bf_str(nested_instructions);
                    }
                    nested_instructions = "";
                default:
                    break;
            }
            instruction_stack.pop();
        }
        recursion--;
    }
}
