#ifndef TREEREADER_H
#define TREEREADER_H

#include<QWidget>

#include<vector>

#include "Types/edge.h"

class TreeReader
{
public:
    TreeReader(QWidget * widget);
    std::vector<std::pair<int,int> > getNodeCoordinates(int width,int height);
    std::vector<std::vector<Edge> > getGraph(){
        return graph;
    }
    QString getPath();
protected:
private:

    std::vector<std::vector<Edge> >graph;
    QString filePath;
    int getMaxLevel(int node,int parent,int lv);
    int getNodeCoordinates(int node,int parent,int lv,int deltaY,int xBegin,int xEnd,std::vector<std::pair<int,int> > & coords);
};

#endif // TREEREADER_H
