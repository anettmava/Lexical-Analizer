#ifndef STATE_HPP
#define STATE_HPP

#include <string>
#include <unordered_map>
#include <iostream>

class State{
    public:
        std::string name;
        bool isFinal;
        bool isDeathState;
        std::unordered_map<std::string, State*> transitions;

        State(const std::string &name, bool isFinal, bool isDeathState): name(name), isFinal(isFinal), isDeathState(isDeathState) { }

        void addTransition(const std::string &symbol, State* state) {
            transitions[symbol] = state;
        }

        State* getNextState(const std::string &symbol) {
            auto it = transitions.find(symbol);
            if (it != transitions.end()) {
                return it->second;
            }
            return nullptr;
        }

        std::string getName(){
            return name;
        } 
        
        std::string toString() const {
            return name + "," + (isFinal ? "true" : "false") + "," + (isDeathState ? "true" : "false");
        }
};

#endif