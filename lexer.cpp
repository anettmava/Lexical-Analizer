#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include "Automaton.hpp"
#include "State.hpp"

void processToken(const std::string& input) {
    State* start = new State("START", false, false);
    State* integer = new State("INTEGER", true, false);  
    State* real = new State("FLOAT", true, false);     
    State* variable = new State("VARIABLE", true, false);  
    State* assignment = new State("ASSIGNMENT", true, false);
    State* sum = new State("SUM", true, false);
    State* subtract = new State("SUBTRACT", true, false);
    State* product = new State("PRODUCT", true, false);
    State* division = new State("DIVISION", true, false);
    State* leftParenthesis = new State("LEFT_PARENTHESIS", true, false);
    State* rightParenthesis = new State("RIGHT_PARENTHESIS", true, false);
    State* decimalPoint = new State("DECIMAL_POINT", false, false);

    start->addTransition("=", assignment);
    start->addTransition("+", sum);
    start->addTransition("-", subtract);
    start->addTransition("*", product);
    start->addTransition("/", division);
    start->addTransition("(", leftParenthesis);
    start->addTransition(")", rightParenthesis);

    for (char digit = '0'; digit <= '9'; ++digit) {
        start->addTransition(std::string(1, digit), integer);
        integer->addTransition(std::string(1, digit), integer);
        decimalPoint->addTransition(std::string(1, digit), real);
        real->addTransition(std::string(1, digit), real);
    }

    // decimal point valid after an integer
    integer->addTransition(".", decimalPoint);

    for (char letter = 'a'; letter <= 'z'; ++letter) {
        start->addTransition(std::string(1, letter), variable); 
        variable->addTransition(std::string(1, letter), variable);
    }

    Automaton automaton(start);

    std::string token = "";
    State* currentState = start;

    for (size_t i = 0; i < input.length(); ++i) {
        char c = input[i];

        // Ignore spaces
        if (c == ' ') {
            if (!token.empty()) {
                automaton.validate(token);  // Validate accumulated token
                std::cout << "Token: " << token << " Type: " << currentState->getName() << std::endl;
            }
            token = "";
            currentState = start;
            continue;
        }

        token += c;
        State* nextState = currentState->getNextState(std::string(1, c));

        if (!nextState) {
            automaton.validate(token.substr(0, token.size() - 1));
            std::cout << "Token: " << token.substr(0, token.size() - 1) << " Type: " << currentState->getName() << std::endl;

            // Procesar el nuevo token
            token = std::string(1, c);
            currentState = start->getNextState(token);

            if (!currentState) {
                throw std::runtime_error("Error: Invalid token '" + token + "'");
            }
        } else {
            currentState = nextState;
        }
    }

    if (!token.empty()) {
        automaton.validate(token);
        std::cout << "Token: " << token << " Type: " << currentState->getName() << std::endl;
    }
}

int main() {
    std::string input;
    std::cout << "Ingrese la expresión: ";
    std::getline(std::cin, input);

    try {
        processToken(input);
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1; //end execution if an invalid token is detected
    }

    return 0;
}
