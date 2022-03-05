#include <iostream>
#include <vector>
#include <memory>
#include <stack>
#include <stdexcept>

// This whole namespace is basically just solutions to things that I didn't find in the C++ STL
namespace bfi {
    int find_matching_brackets(const std::string base_string, unsigned int reference_index) {
        // call this function when trying to interpret a [ instruction (get the reference ['s index!)
        // finds matching closing bracket relative to first bracket found 
        if (reference_index < 0) {
            reference_index = base_string.find_first_of('[');
        }
        if (!base_string.find_last_not_of(']')) {
            throw std::invalid_argument("No closing bracket was found.");
        }

        int brackets = 1; 
        for (int index = reference_index; index <= base_string.length(); index++) {
            if(base_string[index] == '[') { brackets++; };
            if(base_string[index] == ']') { brackets--; };
            if(brackets == 0) {return index; };
        }
        return reference_index;
    }

    int find_matching_brackets(std::stack<char> base_stack) {
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

    std::stack<char> str_to_stack(std::string &base_string) {
        std::stack<char> char_stack;

        // Reverse base_string for making it be the right order when in stack
        std::string reversed = std::string(base_string.rbegin(), base_string.rend());

        for(char str_char : reversed) {
            char_stack.push(str_char);
        }

        return char_stack;
    }

    std::string stack_to_str(std::stack<char> sample_stack) {
        std::string end_str;
        while(!sample_stack.empty()) {
            end_str.push_back(sample_stack.top());
            sample_stack.pop();
        }
        return end_str;
    }

    void print_stack(std::stack<char> sample_stack) {
        // prints every value on a stack
        while(!sample_stack.empty()) {
            std::cout << sample_stack.top();
            sample_stack.pop();
        }
        std::cout << '\n';
    }
}
