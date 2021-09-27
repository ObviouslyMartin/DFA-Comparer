//
//  main.cpp
//  DFAcompare
//
//

#include <iostream>
#include "DFA.hpp"
#include "UnFi.hpp"
#include <stack>
#include <fstream>
#include <vector>
#include <unordered_set>

using namespace std;

bool isEquivalentDFA(DFA A, DFA B);

#define TEST true

int main(int argc, const char * argv[])
{
    cout << "Specify paths to two files that define DFAs to be compared for equivalence. " << endl;
    string input = "";
    while (true)
    {
        //Get both files. Keep asking until valid path is specified for each or program is exited.
        ifstream file1;
        ifstream file2;
        
        ifstream* file = &file1;
        string ith = "first";
        for (int i = 0; i < 2; i++)
        {
            while(true)
            {
                cout << "Enter the path to the " << ith << " DFA file or press ENTER to exit: ";
                getline(cin, input);
                if (input == "")
                {
                    cout << "Exiting." << endl;
                    return 0;
                }
                if (TEST) { input = "DFA" + input + ".txt"; }
                file->open(input);
                if (!(*file))
                {
                    cerr << "Invalid file path specified. Try again. ";
                }
                else { break; }
            }
            ith = "second";
            file = &file2;
        }
        
        cout << "Determining equivalence..." << endl;
        
        //process DFA input text files into DFA
        DFA A(file1);
        DFA B(file2);
    
         if(isEquivalentDFA(A, B))
         {
             cout << "Equivalent\n";
         }
         else
         {
             cout << "Not equivalent\n";
         }
    }

    return 0;
}


bool isEquivalentDFA(DFA A, DFA B)
{
    if(A.alphaSize() != B.alphaSize())
        return false;
    stack<int> stateStack;
    int p = 0, q = A.numStates();
    int pprime = 0, qprime = 0;
    int ppInd, qpInd;
    UnFi U;
    int pind = U.Make(p);
    int qind = U.Make(q);
    U.Union(pind, qind);
    stateStack.push(p);
    stateStack.push(q);
    while (stateStack.size() >= 2)
    {
        q = stateStack.top();
        stateStack.pop();
        p = stateStack.top();
        stateStack.pop();
        if(A.isAcceptingState(p) != B.isAcceptingState(q - A.numStates()))
        {
            return false;
        }

        for (int a = 0; a < A.alphaSize(); a++) //for each character in the DFA's alphabet
        {
            pprime = A.getTransition(p, a);
            ppInd = U.Find(pprime); // Find is passed the state that is reached on a transition from p on a
            qprime = B.getTransition(q - A.numStates(), a) + A.numStates();
            qpInd = U.Find(qprime);
            
            if (ppInd != qpInd)
            {
                U.Union(ppInd, qpInd);
                stateStack.push(pprime);
                stateStack.push(qprime);
            }
        }
    }
    return true;
}


