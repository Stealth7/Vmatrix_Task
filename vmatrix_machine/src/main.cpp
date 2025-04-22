#include <iostream>
#include <string>
#include <fstream>
#include "bitstream.hpp"
#include "interpreter.hpp"

using namespace std;


int main() {

    string input;
    int number;

    // Test Case program options
    cout << "1: Character reversal " << endl;
    cout << "2: ASCII-art tree " << endl;
    cout << "3: ASCII-art Sierpiński triangle" << endl;
    cout << "4: # of words & # of characters " << endl;
    cout << "5: Fibonacci sequence " << endl;
    cout << "Please select 1 to 5 " << endl;

    cin >> number;
    string filename;

    switch (number) {
    case 1:
        cout << "Case 1 character reversal." << endl;
        input = "Hello";
        filename = "program1.txt";
        break;
    case 2:
        cout << "Case 2 ASCII-art tree." << endl;
        input = "3";
        filename = "program2.txt";
        break;
    case 3:
        cout << "Case 3 ASCII-art Sierpiński triangle." << endl;
        input = "4";
        filename = "program3.txt";
        break;
    case 4:
        cout << "Case 4 # of words & # of characters." << endl;
        input = "Hello\nWorld\n";
        filename = "program4.txt";
        break;
    case 5:
        cout << "Case 5 fibonacci sequence." << endl;
        input = "13";
        filename = "program5.txt";
        break;

    default:
        cout << "Default." << endl;;
        filename = "program1.txt";
        break;
    }

    ifstream file(filename);
    if (!file) {
        cerr << "Error: Could not open program " << endl;
        return 1;
    }

    string program((istreambuf_iterator<char>(file)),
                         istreambuf_iterator<char>());

    cout << input << endl;
    cout << "Program loaded:\n" << program << endl;

    try {
        auto bits = BitStream::fromString(input);
        Interpreter interpreter(program);
        auto result = interpreter.execute(bits);
        cout << BitStream::toString(result) << endl;
    } catch (const exception& ex) {
        cerr << "Error: " << ex.what() << "\n";
        return 2;
    }

    return 0;
}
