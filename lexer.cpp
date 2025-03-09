#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include "Automaton.hpp"
#include "State.hpp"


void processToken(const std::string& input) { //validan el isFinal y isDeathState

    State* start = new State("START", false, false); 
    State* integer = new State("INTEGER", true, false);  
    State* real = new State("REAL", true, false);     
    State* variable = new State("VARIABLE", true, false);  
    State* assignment = new State("ASSIGNMENT", true, false);
    State* sum = new State("SUM", true, false);
    State* subtract = new State("SUBTRACT", true, false);
    State* product = new State("PRODUCT", true, false);
    State* division = new State("DIVISION", true, false);
    State* leftParenthesis = new State("LEFT_PARENTHESIS", true, false);
    State* rightParenthesis = new State("RIGHT_PARENTHESIS", true, false);
    State* decimalPoint = new State("DECIMAL_POINT", false, false);  

    //caracteres
    start->addTransition("=", assignment);
    start->addTransition("+", sum);
    start->addTransition("-", subtract);
    start->addTransition("*", product);
    start->addTransition("/", division);
    start->addTransition("(", leftParenthesis);
    start->addTransition(")", rightParenthesis);

    //numero enteros
    for (char wholeN = '0'; wholeN <= '9'; ++wholeN) {
        start->addTransition(std::string(1, wholeN), integer);
    }

    //punto decimal para el float
    integer->addTransition(".", decimalPoint);  

    //floats
    decimalPoint->addTransition("0", real);
    decimalPoint->addTransition("1", real);
    decimalPoint->addTransition("2", real);
    decimalPoint->addTransition("3", real);
    decimalPoint->addTransition("4", real);
    decimalPoint->addTransition("5", real);
    decimalPoint->addTransition("6", real);
    decimalPoint->addTransition("7", real);
    decimalPoint->addTransition("8", real);
    decimalPoint->addTransition("9", real);

    //abecedario
    for (char alph = 'a'; alph <= 'z'; ++alph) {
        start->addTransition(std::string(1, alph), variable); 
    }

    Automaton automaton(start);

    //para que acepte la entrada con o sin espacio
    std::string token = "";
    std::string floatToken = "";
    bool inFloat = false;

    for (size_t i = 0; i < input.length(); ++i) {
        char newToken = input[i];

        if (newToken == ' ') {
            continue;
        }

        token = std::string(1, newToken);  

        // Detectar si estamos en un número flotante
        if (isdigit(newToken)) {
            if (inFloat) {
                floatToken += token;  // Continuar concatenando el número flotante
            } else {
                token = std::string(1, newToken);
                inFloat = false;
            }
        } else if (newToken == '.') {
            // Estamos en un número flotante, esperar un dígito después del punto
            inFloat = true;
            floatToken += token;  // Concatenar el punto
        }

        // Si encontramos que el número flotante ha terminado (un dígito después del punto), lo imprimimos
        if (inFloat && isdigit(newToken) && !floatToken.empty()) {
            std::cout << "Token: " << floatToken << " Type: float" << std::endl;
            floatToken = "";  // Resetear el token flotante
            inFloat = false;  // Terminar de procesar el número flotante
            continue;  // Pasar al siguiente token
        }

        try {
            automaton.validate(token);
        } catch (const std::runtime_error& e) {
            std::cout << "Error al procesar '" << token << "': " << e.what() << std::endl;
        }
    }
}


int main() {
    std::string input;
    std::cout << "Prueba: ";
    std::getline(std::cin, input);
    std::cout << "Procesando: " << input << std::endl;

    processToken(input);

    return 0;
}
