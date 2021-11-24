#include <iostream>
#include "automata.h"

using namespace std;

/**
 * Constructor for Abstract DFA.
 * 
 * @param noStates
 *            Number of states in the DFA.
 */
AbstractDFA::AbstractDFA(int noStates) : _noStates(noStates), _currentState(0) {
	// DONE: initialize data structures
}

/**
 * Reset the automaton to the initial state.
 */
void AbstractDFA::reset() {
    // DONE: reset automaton to initial state
    _currentState = 0;

}

/**
 * Performs one step of the DFA for a given letter. If there is a transition
 * for the given letter, then the automaton proceeds to the successor state.
 * Otherwise it goes to the sink state. By construction it will stay in the
 * sink for every input letter.
 * 
 * @param letter
 *            The current input.
 */
void AbstractDFA::doStep(char letter) {
    // DONE: do step by going to the next state according to the current
    // state and the read letter.
    auto _actualTransition = _transitions.find(tpair(_currentState,letter));
    
    if (_actualTransition != _transitions.end())    
        _currentState = _actualTransition->second; 
    else                                    
        _currentState = -1; 
}

/**
 * Check if the automaton is currently accepting.
 * 
 * @return True, if the automaton is currently in the accepting state.
 */
bool AbstractDFA::isAccepting() {
    for (auto i : _states) {
        if (_currentState == i)
            return true;
    }
    return false;
}

/**
 * Run the DFA on the input.
 * 
 * @param inputWord
 *            stream that contains the input word
 * @return True, if if the word is accepted by this automaton
 */
bool AbstractDFA::run(const string &inputWord) {
    this->reset();
    for(int i = 0; i < inputWord.length(); i++) {
        doStep(inputWord[i]);
    }
    return isAccepting();
}


/**
 * Construct a new DFA that recognizes exactly the given word. Given a word
 * "foo" the constructed automaton looks like: -> () -f-> () -o-> () -o-> []
 * from every state (including the final one) every other input letter leads
 * to a distinguished sink state in which the automaton then remains
 * 
 * @param word
 *            A String that the automaton should recognize
 */
WordDFA::WordDFA(const string &word) : AbstractDFA(word.length()) {
    // DONE: fill in correct number of states
    
    // DONE: build DFA recognizing the given word
    for (int i = 0; i < word.length(); i++)
        _transitions[tpair(i,word[i])] = i+1;

    _states.push_back(word.length());
}

/**
 * Construct a new DFA that recognizes comments within source code. There
 * are three kinds of comments: single line comment that starts with // and ends
 * with a newline, multiline comments that starts with (* and ends with *), and
 * multiline comments that starts with { and ends with }
 */
CommentDFA::CommentDFA() : AbstractDFA(8) {
    // DONE: fill in correct number of states
    // DONE: build DFA recognizing comments
    
    /* Commento di tipo // */
    _transitions[tpair(0,'/')] = 1;
    _transitions[tpair(1,'/')] = 2;
    _transitions[tpair(2,'\n')] = 3;
    _states.push_back(3);

    /* Commento di tipo (* *) */
    _transitions[tpair(0,'(')] = 4;
    _transitions[tpair(4,'*')] = 5;
    _transitions[tpair(5,'*')] = 6;
    _transitions[tpair(6,')')] = 7;
    _states.push_back(7);

    /* Commento di tipo { } */
    _transitions[tpair(0,'{')] = 8;
    _transitions[tpair(8,'}')] = 9;
    _states.push_back(9);
 }

/**
 * Performs one step of the DFA for a given letter. This method works
 * differently than in the superclass AbstractDFA.
 * 
 * @param letter
 *            The current input.
 */
void CommentDFA::doStep(char letter) {
    // DONE: implement accordingly
    if (_currentState == 2 && letter != '\n') _currentState = 2;
    else if (_currentState == 5 && letter != '*') _currentState = 5;
    else if (_currentState == 6 && letter != ')' && letter != '*') _currentState = 5;
    else if (_currentState == 6 && letter == '*') _currentState = 6;
    else if (_currentState == 8 && letter != '}') _currentState = 8;
    else AbstractDFA::doStep(letter);
}	


