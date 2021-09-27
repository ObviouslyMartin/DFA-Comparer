//
//  UnFi.cpp
//  DFAcompare
//
//  Created by Will Lucic on 5/1/19.
//  Copyright © 2019 supersaiyansubtlety. All rights reserved.
//

#include "UnFi.hpp"
#include<iostream>

using namespace std;

UnFi::UnFi()
{
    
}

UnFi::UnFi(vector<int> states)
{
    for (auto state : states)
    {
        Make(state);
    }
}

const vector<vector<int> >& UnFi::getSets() const
{
    return Sets;
}

const unordered_map<int, int>& UnFi::getStateIndicies() const
{
    return StateIndices;
}

int UnFi::Make(int state)
{
    vector<int> S = {state};
    if (emptySets.empty())
    {
        Sets.push_back(S);
        StateIndices.insert(make_pair(state, Sets.size() - 1));
        return Sets.size() - 1; //return index of set in vector of sets
    }
    else
    {
        int reuse = emptySets.top();
        emptySets.pop();
        Sets[reuse] = S;
        return reuse;
    }
}


int UnFi::Find(int state)
{
    auto stateItr = StateIndices.find(state);
    if(stateItr == StateIndices.end())
    {
        return Make(state);
    }
    return stateItr->second;
}

int UnFi::Union(int ind1, int ind2)
{
    assert(ind1 >= 0);
    assert(ind2 >= 0);
    assert(ind1 < Sets.size());
    assert(ind2 < Sets.size());
    
    int& indG = (Sets[ind1] > Sets[ind2])? ind1 : ind2;
    int& indL = (indG == ind1)? ind2 : ind1;
    
    for (auto state : Sets[indL])
    {//insert set2 into set1
        Sets[indG].push_back(state);
        StateIndices[state] = indG;
    }
    //remove ind2
    Sets[indL].clear();
    emptySets.push(indL);
    
    return indG;
}


