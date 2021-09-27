//
//  DFA.hpp
//  DFAcompare
//
//

#ifndef DFA_hpp
#define DFA_hpp

#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <fstream>

using namespace std;

class DFA
{
public:
    DFA();
    DFA(const vector< vector<int> > transitions, const unordered_set<int> acceptStates);
    DFA(ifstream& stream);
    
    DFA& operator=(const DFA& R);
    
    bool Evaluate(vector<int> input) const;
    bool isAcceptingState(int state);
    
    const vector< vector<int> >& getTransitions();
    int getTransition(const int& state, const int& let);
    int numStates();
    
    
    int alphaSize() const;
private:
    vector< vector<int> > Transitions;
    unordered_set<int> AcceptStates;
    
    bool Validate();
    void Clear();
    
    
}; //class DFA

bool isInt(const string& str);
int getInt(ifstream& stream);

#endif /* DFA_hpp */
