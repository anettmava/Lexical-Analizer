#include <string>
#include <stdexcept>
#include "State.hpp"

class Automaton {
    public:
        State* S;
    
        // Constructor: recibe un puntero al estado inicial
        Automaton(State* S) : S(S) { }
    
        // Método de validación. Si la validación falla, lanza una excepción.
        State* validate(const std::string &word) {
            if (word.empty()) {
                if (S->isFinal) {
                    return S;  
                } else {
                    throw std::runtime_error("Error: Empty string is not valid.");
                }
            }
        
            State* currentState = S;
            std::string token = "";
        
            for (size_t i = 0; i < word.length(); i++) {
                std::string symbol(1, word[i]);
                State* nextState = currentState->getNextState(symbol);
        
                if (nextState == nullptr) {
                    throw std::runtime_error("Error: Invalid symbol '" + symbol + "' encountered.");
                }
        
                token += word[i];  
                currentState = nextState;
            }
        
            if (!currentState->isFinal) {
                throw std::runtime_error("Error: Token '" + token + "' is not valid.");
            }
        
            return currentState;
        }
    };