#ifndef HLD_H
#define HLD_H

#include<QString>
#include<QDebug>

#include "Types/parentinfo.h"
#include "DS/lca.h"
#include "DS/segmenttree.h"

#include <vector>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <set>

class HLD
{
public:
    enum queryType{
        sum,
        maximum,
        minimum,
        gcd,
        lcm,
        Count
    };
public:
    HLD(QString filePath);
    int saveMaximumChildAndGetChildSubtreeSize(int childSubtreeSize,int & maxChildSubtreeSize, int & maxChild, int child);
    int overToWithCeil(int x);
    int calculateHeavyLightEdges(int node,int parent);
    void calculateHeavyPaths();
    void initializeVectors(int n);
    void buildHeavyLightDecomposition();
    int ansOfMovingNodeToLCA(int node,int lcaNode,queryType qType,bool & flag);
    void initSegmentTrees();
    int query(int a,int b,queryType qType);
    bool update(int a,int b,int w);
protected:
private:
    struct edge{
        int edgeNumber,node,weight;
        edge(int edgeNumber,int node,int weight){
            this->edgeNumber=edgeNumber;
            this->node=node;
            this->weight=weight;
        }
        edge(){}
    };
    std::vector<std::vector<edge> > graph; // its size is set at the beggining of execution
    std::vector<std::set<int> > existsEdge;

    std::vector<int> mapEdgeParent; //  its size is set at the beggining of execution

    std::vector<ParentInfo> parentEdge; // its size is set at the beggining of execution

    struct segInfo{
        int segIndex,indexInSeg;
    };

    std::vector<segInfo> edgeToSegmentTree; // its size is set at the beggining of execution

    struct segEdgeRange{
        int begin,end;
    };

    std::vector<segEdgeRange>segmentTreeRanges; // its size increases during execution
    std::vector<bool> hasHeavyChild; // its size is set at the beggining of execution
    int n;

    LCA lca;
    std::vector<std::vector<SegmentTree> > segmentTrees;
    const std::vector<std::function<int(int,int)> >comparators={

        [](int a,int b){
            return a+b;
        },
        [](int a,int b){
            return std::max(a,b);
        },
        [](int a,int b){
            return std::min(a,b);
        },
        [](int a,int b){
            return std::__gcd(a,b);
        },
        [](int a,int b){
            int gcd = std::__gcd(a,b);
            return a*b/(gcd==0?1:gcd);
        }
    };
    void update(int edgeIndex,int w);
};

#endif // HLD_H
