#ifndef CANVAS_H
#define CANVAS_H

#include<QGraphicsScene>
#include<QPen>
#include<QPainter>
#include<QDebug>
#include<QGraphicsTextItem>
#include "Types/edge.h"

class Canvas : public QGraphicsScene
{
public:
    Canvas(std::vector<std::pair<int,int> >coords,std::vector<std::vector<Edge> > graph,int titleBarHeight,int width,int height);
protected:

};

#endif // CANVAS_H
