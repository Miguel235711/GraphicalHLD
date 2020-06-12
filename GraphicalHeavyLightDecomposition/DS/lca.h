#ifndef LCA_H
#define LCA_H

#include <vector>
#include <algorithm>
#include <cmath>

#include "Types/parentinfo.h"

class LCA
{
public:
    LCA();
    LCA(const std::vector<ParentInfo> & parent);
    int getLCANode(int a, int b);
    int compareLevel(int a,int b);
protected:
private:
    std::vector<int>parent;
    std::vector<std::vector<int> >graph;
    std::vector<std::vector<int> > anscestor; //[power of 2] [ origNode ]
    std::vector<int>level;// from 0 to ...
    int exp;
    void calculateLevels(int node,int lv,int parent);
    void calculateAnscestors();
    std::vector<int> getParentNodes(const std::vector<ParentInfo> & parent);

};

#endif // LCA_H
