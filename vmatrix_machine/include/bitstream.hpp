#pragma once
#include <string>
#include <vector>

class BitStream {
public:

    using bit_stream = std::vector<bool>;

    static bit_stream fromString(const std::string& input);
    static std::string toString(const bit_stream& bits);

};


