# Lexical-Analizer
# Lexical Analyzer in C++

This project implements a lexical analyzer in C++. It consists of three main files:

- `State.hpp`
- `Automaton.hpp`
- `lexer.cpp`

## Explanation of the Code

### `State.hpp`

This file defines the `State` class, which represents a state in a finite automaton. The class has the following members:

- `name`: The name of the state.
- `isFinal`: A boolean indicating if the state is a final state.
- `isDeathState`: A boolean indicating if the state is a death state.
- `transitions`: An unordered map that maps input symbols to the next state.

The class provides the following methods:

- `State(const std::string &name, bool isFinal, bool isDeathState)`: Constructor to initialize the state.
- `void addTransition(const std::string &symbol, State* state)`: Adds a transition from the current state to another state on a given symbol.
- `State* getNextState(const std::string &symbol)`: Returns the next state for a given symbol.
- `std::string getName()`: Returns the name of the state.
- `std::string toString() const`: Returns a string representation of the state.

### `Automaton.hpp`

This file defines the `Automaton` class, which represents a finite automaton. The class has the following members:

- `State* S`: A pointer to the initial state.

The class provides the following methods:

- `Automaton(State* S)`: Constructor to initialize the automaton with the initial state.
- `State* validate(const std::string &word)`: Validates a given word against the automaton. If the word is valid, it returns the final state; otherwise, it throws an exception.

### `lexer.cpp`

This file contains the main logic for the lexical analyzer. It includes the following functions:

- `void processToken(const std::string& input)`: Processes a given input string and prints the tokens and their types.
- `void lexer(const std::string& filepath)`: Reads a file line by line and processes each line using `processToken`.
- `int main()`: The entry point of the program. It calls the `lexer` function with the path to the input file.

## How to Run the Program

### 1. Compile the Program
Open a terminal and navigate to the folder where the code is located. Run the following command to compile the program:

```bash
g++ -o lexer lexer.cpp
```

### 2. Run the Program
Once the program is compiled, run it with the following command:

```bash
./lexer
```

Ensure that there is a file named expressions.txt in the same directory, as the program reads input from this file.

### `Programming Language`
The program is written in C++.


