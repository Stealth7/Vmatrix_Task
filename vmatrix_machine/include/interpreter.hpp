#pragma once
#include <string>
#include <vector>
#include <unordered_map>

class Interpreter {
public:
    using bit_stream = std::vector<bool>;

    Interpreter(const std::string& code) : code(code) {
    buildBracketMap();
}
    bit_stream execute(const bit_stream& input);

private:
    std::string code;
    std::unordered_map<size_t, size_t> bracket_map;

    void buildBracketMap();
};

