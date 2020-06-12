#ifndef EDGE_H
#define EDGE_H


struct Edge
{
    int node,cost;
    Edge(){}
    Edge(int node,int cost){
        this->node=node;
        this->cost=cost;
    }
};

#endif // EDGE_H
