#include <string>
#include <stdexcept>
#include <State.hpp>

class Automaton {
    public:
        State* S;
    
        // Constructor: recibe un puntero al estado inicial
        Automaton(State* S) : S(S) { }
    
        // Método de validación. Si la validación falla, lanza una excepción.
        void validate(const std::string &word) {
            bool result = false;
    
            // Si la cadena es vacía, se valida según el estado inicial
            if (word.empty()) {
                if (S->isFinal) {
                    result = true;
                } else {
                    throw std::runtime_error("Error: Empty string");
                }
            } else {
                State* currentState = S;
                // Recorre la cadena carácter por carácter
                for (size_t i = 0; i < word.length(); i++) {
                    std::string symbol(1, word[i]);
                    currentState = currentState->getNextState(symbol);
                    if (currentState == nullptr) {
                        throw std::runtime_error("Error: Not a valid symbol");
                    }
                    else{
                        std::cout<<"Token: "<<symbol<<"Type: "<<currentState->name<<std::endl;
                    }

                    result = currentState->isFinal;
                }
            }

            if (!result) {
                throw std::runtime_error("Error: Not valid.");
            }
        }
    };