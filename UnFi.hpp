//
//  UnFi.hpp
//  DFAcompare
//
//  Created by Will Lucic on 5/1/19.
//  Copyright © 2019 supersaiyansubtlety. All rights reserved.
//

#ifndef UnFi_hpp
#define UnFi_hpp

#include <stdio.h>
#include <algorithm>
#include <vector>
#include <stack>
//#include <set>
#include <unordered_map>
#include <assert.h>

using namespace std;

class UnFi
{
public:
    UnFi();
    UnFi(vector<int> states);
    

    const vector<vector<int> >& getSets() const;
    const unordered_map<int, int>& getStateIndicies() const;

    int Make(int state);
    int Union(int ind1, int ind2);
    int Find(int state);
    int getState(int index);
    
private:
    vector<vector<int>> Sets;
    unordered_map<int, int> StateIndices;
    stack<int> emptySets;
};

#endif /* UnFi_hpp */
