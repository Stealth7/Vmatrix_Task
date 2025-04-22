
#include <iostream>
#include "bitstream.hpp"
#include <bitset>
#include <stdint.h>
//#define DEBUGBYTES

using namespace std;

//----------------------------------------------------------------------------------------------
//    static bit_stream fromString(const string& input)
//
//    Purpose: Converts a string into a stream of bits (vector<bool>).
//----------------------------------------------------------------------------------------------

BitStream::bit_stream BitStream::fromString(const string& input) {
    bit_stream bits;
    for (unsigned char c : input) {
        bitset<8> b(c);                     // Convert character to 8-bit binary
        for (size_t i = 0; i < 8; ++i) {
            bits.push_back(b[i]);           // Add each bit (LSB first - little-endian)
        }
    }
    return bits;
}

//----------------------------------------------------------------------------------------------
//    static string toString(const bit_stream& bits)
//
//    Purpose: Converts a stream of bits back into a human-readable string.
//----------------------------------------------------------------------------------------------

string BitStream::toString(const bit_stream& bits) {
    string output;
    for (size_t i = 0; i < bits.size(); i += 8) {                   // Processes 8 bits at a time
        uint8_t byte = 0;
        for (size_t j = 0; j < 8 && i + j < bits.size(); ++j) {
            if (bits[i + j]) {
                byte |= (1 << j);                                   // Reconstructs each byte (little-endian):
            }
        }
        output += static_cast<char>(byte);                          // Append the decoded character to output

#ifdef DEBUGBYTES                                                   // When DEBUGBYTES is defined, it prints a formatted view of each byte
        // Improved debug output
        string char_repr;
        if (byte == '\n') char_repr = "\\n";
        else if (byte == '\t') char_repr = "\\t";
        else if (byte == '\r') char_repr = "\\r";
        else if (byte == ' ') char_repr = "' '";
        else if (byte >= 32 && byte <= 126) char_repr = string(1, static_cast<char>(byte));
        else char_repr = ".";

        cout << "Byte: " << setw(3) << (int)byte
                  << " (" << bitset<8>(byte) << ")"
                  << " = " << char_repr << "\n";
#endif
    }
    return output;
}



