//
//  DFA.cpp
//  DFAcompare
//
//

#include "DFA.hpp"

DFA::DFA()
{
    
}

DFA::DFA(const vector< vector<int> > transitions, const unordered_set<int> acceptStates):
Transitions(transitions),
AcceptStates(acceptStates)
{
    Validate();
} //DFA::DFA(const vector< vector<int> > transitions, const vector<int> acceptStates)

DFA::DFA(ifstream& stream)
{
    int NLs = 0;
    vector<int> currTransitions;
    
    vector<vector<int> > transitions;
    while (NLs < 2)
    {
        if (stream.peek() == '\n')
        {
            stream.ignore(1);
            if (NLs == 0)
            {
                NLs++;
                transitions.push_back(currTransitions);
                currTransitions.clear();
            }
            else
            {
                //two successive newlines
                //move on to reading in accept states
                break;
            }
            
        }
        else
        {
            NLs = 0;
            int transition = getInt(stream);
            if (transition < 0)
            {
                cerr << "Discarding DFA." << endl;
                Clear();
                return;
            }
            currTransitions.push_back(transition);
        }
    }
    
    unordered_set<int> accepts;
    while (!stream.eof())
    {
        int accept = getInt(stream);
        if (accept < 0)
        {
            cerr << "Discarding DFA." << endl;
            Clear();
            return;
        }
        accepts.insert(accept);
        while (isspace(stream.peek()))
        {
            stream.ignore(1);
        }
    }
    
    Transitions = transitions;
    AcceptStates = accepts;
} //DFA::DFA(string str)

DFA& DFA::operator=(const DFA& R)
{
    Transitions = R.Transitions;
    AcceptStates = R.AcceptStates;
    return *this;
}

int DFA::alphaSize() const
{
    return Transitions.begin()->size();
} //int DFA::getAlphaSize() const

bool DFA::Evaluate(vector<int> input) const
{
    //start at start state
    int state = 0;
    
    //process input
    for (auto character : input)
    {
        state = Transitions[state][character];
    }
    //return true IFF state is accepting
    return AcceptStates.find(state) != AcceptStates.end();
} //bool DFA::evaluate(vector<int>) const

bool DFA::isAcceptingState(int state)
{
    return AcceptStates.find(state) != AcceptStates.end();
} //bool DFA::isAcceptingState(int state)

const vector< vector<int> >& DFA::getTransitions()
{
    return Transitions;
} //const vector< vector<int> >& DFA::getTransitions()

int DFA::getTransition(const int& state, const int& let)
{
    return Transitions[state][let];
} //int DFA::getTransition(const int& state, const int& let)

bool DFA::Validate()
{
    //initialize lastNumTransitions to size of first column
    auto lastNumTransitions = Transitions.begin()->size();
    for (auto state : Transitions)
    {
        //make sure transitions is not ragged 2d vector
        if (lastNumTransitions != state.size())
        {
            return false;
        }
        lastNumTransitions = state.size();
        
        //make sure all transitions are to existing states
        for (auto transition : state)
        {
            if (transition >= Transitions.size())
            {
                cerr << "DFA contains transition to non-existent state. Discarding DFA. " << endl;
                Clear();
                return false;
            }
            
            if (transition < 0)
            {
                cerr << "DFA contains transition to negatively-indexed state. Discarding DFA. " << endl;
                Clear();
                return false;
            }
        }
    }
    return true;
} //bool DFA::isValid()

void DFA::Clear()
{
    Transitions.clear();
    AcceptStates.clear();
} //void DFA::clear()

bool isInt(const string& str)
{
    for (auto c : str)
    {
        if (!isdigit(c)) { return false; }
    }
    
    return true;
}

int getInt(ifstream& stream)
{
    string token;
    stream >> token;
    if (!isInt(token))
    {
        cerr << "File provided contains non-integer value. " << endl;
        return -1;
    }
    return stoi(token);
}

int DFA::numStates() {
    return Transitions.size();
}
