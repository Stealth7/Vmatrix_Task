#include "interpreter.hpp"
#include <iostream>
#include <vector>

using namespace std;


//----------------------------------------------------------------------------------------------
//    void Interpreter buildBracketMap()
//
//    Purpose: Matches [ and ] positions to enable looping logic
//----------------------------------------------------------------------------------------------

void Interpreter::buildBracketMap() {
    vector<size_t> stack;                               // Keeps track of unmatched [ positions using a stack (LIFO structure).
    for (size_t i = 0; i < code.length(); ++i) {
        if (code[i] == '[') {                           // When you find a [, you push its index onto the stack
            stack.push_back(i);
        } else if (code[i] == ']') {
            if (stack.empty()) {
                throw runtime_error("Unmatched closing bracket at position " + to_string(i));
            }
            size_t open = stack.back();  // When you find a ], pop the most recent [ off the stack and record both directions of the match
            stack.pop_back();
            bracket_map[open] = i;
            bracket_map[i] = open;
        }
    }
    // If the stack isn't empty at the end, there's an unmatched [
    if (!stack.empty()) {
        throw runtime_error("Unmatched opening bracket at position " + to_string(stack.back()));
    }
}

//----------------------------------------------------------------------------------------------
//    Interpreter execute(const bit_stream& input)
//
//    Runs the program with the provided binary input, returning binary output
//----------------------------------------------------------------------------------------------
//      Instruction Set
//      ---------------
//  +	                Flip the current bit (0 -> 1) or (1 -> 0)
//  ,	                Read next bit from input (or 0 if exhausted)
//  ;	                Output the current bit
//  <	                Move pointer left (expand tape if needed)
//  >	                Move pointer right (expand tape if needed)
//  [	                If current bit is 0, jump to matching ]
//  ]	                If current bit is 1, jump back to matching [
//  Any other char	    Ignored (safe for comments or whitespace)
//----------------------------------------------------------------------------------------------


Interpreter::bit_stream Interpreter::execute(const bit_stream& input) {
    vector<bool> tape(1, 0);
    size_t pointer = 0;
    size_t code_ptr = 0;
    size_t input_ptr = 0;
    bit_stream output;

    while (code_ptr < code.length()) {
        char cmd = code[code_ptr];

        switch (cmd) {
            case '+':
                tape[pointer] = !tape[pointer];
                break;
            case ',':
                if (input_ptr < input.size()) {
                    tape[pointer] = input[input_ptr++];
                } else {
                    tape[pointer] = 0;
                }
                break;
            case ';':
                output.push_back(tape[pointer]);
                break;
            case '<':
                if (pointer == 0) {
                    tape.insert(tape.begin(), 0);
                } else {
                    --pointer;
                }
                break;
            case '>':
                ++pointer;
                if (pointer >= tape.size()) {
                    tape.push_back(0);
                }
                break;
            case '[':
                if (!tape[pointer]) {
                    code_ptr = bracket_map[code_ptr];
                }
                break;
            case ']':
                if (tape[pointer]) {
                    code_ptr = bracket_map[code_ptr];
                }
                break;
            default:
                break; // ignore any other characters
        }
        ++code_ptr;
    }

    return output;
}

