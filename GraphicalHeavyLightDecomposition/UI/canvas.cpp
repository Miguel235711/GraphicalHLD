#include "canvas.h"

Canvas::Canvas(std::vector<std::pair<int,int> >coords,std::vector<std::vector<Edge> > graph,int titleBarHeight,int width,int height)
{
    mapEdgeToIndex = std::vector<std::map<int,int> > (graph.size());
    edgeToEdgeLabel = std::vector<std::map<int,QGraphicsTextItem *> > (graph.size());
    this->graph=graph;
    for(int a=0;a<graph.size();a++){
        for(int i=0;i<graph[i].size();i++)
            mapEdgeToIndex[a].insert(std::make_pair(graph[a][i].node,i));
    }
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
                cost->setFont(QFont("Sans",15));
                edgeToEdgeLabel[i].insert(std::make_pair(adjacent.node,cost));
                addItem(cost);
             }
        addEllipse(coord.first,coord.second,40,40,QPen(Qt::red),QBrush(Qt::red));
        visited[i]=true;
        auto io = new QGraphicsTextItem();
        io->setPos(coord.first+6,coord.second+7.5);
        io->setPlainText(QString::number(i));
        io->setDefaultTextColor(Qt::white);
        io->setFont(QFont("Sans",15));
        addItem(io);
    }
    //addEllipse(400,400,100,100,QPen(Qt::red),QBrush(Qt::red));
}
void Canvas::updateDraw(int a,int b,int newW){
    qInfo() << "updateDraw\n";
    bool successfull=false;
    auto it = edgeToEdgeLabel[a].find(b);
    QGraphicsTextItem * ref;
    if(it==edgeToEdgeLabel[a].end()){
        auto it2 = edgeToEdgeLabel[b].find(a);
        if(it!=edgeToEdgeLabel[b].end()){
            ref=it2->second;
            successfull=true;
        }else{
            qInfo() << "Error when updating weight";
        }
    }else{
        ref=it->second;
        successfull=true;
    }
    if(successfull){
        ref->setPlainText("");
        ref->setPlainText(QString::number(newW));
        QFuture<void> f = QtConcurrent::run([ref](){
            ref->setDefaultTextColor(Qt::green);
            QThread::sleep(1);
            ref->setDefaultTextColor(Qt::blue);
        });
    }
}
void Canvas::update(int a,int b,int newW){
    graph[a][mapEdgeToIndex[a][b]].cost=newW;
    graph[b][mapEdgeToIndex[b][a]].cost=newW;
    updateDraw(a,b,newW);
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


