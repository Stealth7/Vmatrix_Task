Design Notes and Assumptions
Tape pointer starts in the middle of a dynamically resizable tape.

Bracket matching logic with validation.

I/O: ASCII-to-bits and bits-to-ASCII conversion.

Valid operations: + , ; < > [ ].

Efficient loop jumping using precomputed matching bracket pairs.

Handles EOF as 0 for input stream exhaustion.

Output padded to full bytes if not multiple of 8.

--

Design
BitStream class – For converting between strings and bit streams.

Interpreter class – Contains the logic for interpreting the code.

main.cpp – Entry point that uses the above classes.

program.txt (5 text files each containing the test cases program code correlating to the test case examples provided in the exercise description).

Explanation of Program Code:
, – Read input bit

; – Write current bit to output

[ – Begin loop

, – Read next input bit

; – Write it

] – Loop back if current bit is 1

--

In summary it works this way:
1: Convert a string into bits using BitStream::fromString.

2: Execute the program with Interpreter.

3: Convert the output bits back to a string using BitStream::toString.

--

The Code::Blocks structure is:

bit_interpreter/

├── headers/ │ ├── bitStream.hpp │ └── interpreter.hpp ├── sources/ │ ├── bitStream.cpp │ ├── interpreter.cpp │ └── main.cpp │├── others/ │ └── program1.txt │ └── program2.txt │ └── program3.txt │ └── program4.txt │ └── program5.txt │ └── README.md

--

Build Instructions
Built using Code::Blocks 25.03 on Windows and GNU GCC Compiler

The tests that are run are based on the example provided with the input string and program data, the user just selects test 1 to 5.

--

TEST RESULTS
hello olleh

3 *

3 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

hello world 2 2 12

11 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89
