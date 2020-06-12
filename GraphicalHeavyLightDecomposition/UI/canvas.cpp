#include "canvas.h"

Canvas::Canvas(std::vector<std::pair<int,int> >coords,std::vector<std::vector<Edge> > graph,int titleBarHeight,int width,int height)
{
    setBackgroundBrush(QBrush(Qt::white,Qt::SolidPattern));
    setSceneRect(0,-titleBarHeight,width,height);
    std::vector<bool> visited(graph.size());
    //addEllipse(0,0,50,50,QPen(Qt::red),QBrush(Qt::red));
    for(int i=0;i<coords.size();i++){
        auto coord = coords[i];
        for(auto adjacent: graph[i])
             if(!visited[adjacent.node]){
                addLine(coords[i].first+20,coords[i].second+20,coords[adjacent.node].first+20,coords[adjacent.node].second+20,QPen(Qt::black));
                auto cost = new QGraphicsTextItem();
                int xMid = (coords[i].first+20+coords[adjacent.node].first+20)/2, yMid = (coords[i].second+20+coords[adjacent.node].second+20)/2;
                cost->setPos(xMid,yMid);
                cost->setPlainText(QString::number(adjacent.cost));
                cost->setDefaultTextColor(Qt::blue);
                addItem(cost);
             }
        addEllipse(coord.first,coord.second,40,40,QPen(Qt::red),QBrush(Qt::red));
        visited[i]=true;
        auto io = new QGraphicsTextItem();
        io->setPos(coord.first+15,coord.second+15);
        io->setPlainText(QString::number(i));
        io->setDefaultTextColor(Qt::white);
        addItem(io);
    }
    //addEllipse(400,400,100,100,QPen(Qt::red),QBrush(Qt::red));
}
/*void Canvas::paintEvent(QPaintEvent *event){
    QPainter painter;
    painter.begin(this);
    auto pen = QPen();
    pen.setWidth(10);
    pen.setBrush(Qt::SolidPattern);
    painter.setPen(pen);
    //painter.setBrush(Qt::red);
    painter.drawEllipse(100,100,50,50);
    painter.end();
}*/


