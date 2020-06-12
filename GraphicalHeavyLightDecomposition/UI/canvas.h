#ifndef CANVAS_H
#define CANVAS_H

#include<QGraphicsScene>
#include<QPen>
#include<QPainter>
#include<QDebug>
#include<QGraphicsTextItem>
#include<QFuture>
#include <QtConcurrent/QtConcurrent>
#include <QThread>

#include "Types/edge.h"

#include <map>

class Canvas : public QGraphicsScene
{
public:
    Canvas(std::vector<std::pair<int,int> >coords,std::vector<std::vector<Edge> > graph,int titleBarHeight,int width,int height);
    void update(int a,int b,int newW);
    const std::vector<std::vector<Edge> > & getGraph(){
        return graph;
    }
protected:
private:
    std::vector<std::map<int,int> > mapEdgeToIndex;
    std::vector<std::vector<Edge> > graph;
    std::vector<std::map<int,QGraphicsTextItem *> > edgeToEdgeLabel;
    void updateDraw(int a,int b,int newW);
};

#endif // CANVAS_H
