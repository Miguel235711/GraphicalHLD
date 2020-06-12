#include "treereader.h"
#include<QFileDialog>
#include<QDebug>
#include<fstream>

TreeReader::TreeReader(QWidget * widget)
{
    QFileDialog dialog;
    filePath=dialog.getOpenFileName(widget,"Selecciona Archivo","","Files (*.in *.txt)");
    qInfo() << "Selected File Path: " << filePath;
    std::ifstream in;
    in.open(filePath.toStdString());
    int n,a,b,cost;
    in>>n;
    qInfo() << "TreeReader constructor() n= " << n << "\n";
    graph.resize(n);
    n-=1;
    while(n--){
        in>>a>>b>>cost;
        graph[a].push_back(Edge(b,cost));
        graph[b].push_back(Edge(a,cost));
    }
}
QString TreeReader::getPath(){
    return filePath;
}
int TreeReader::getMaxLevel(int node,int parent,int lv){ // from 1 to ...
    int maxLevel=0;
    for(auto child: graph[node]){
        if(child.node!=parent){
            maxLevel=std::max(getMaxLevel(child.node,node,lv+1),maxLevel);
        }
    }
    return maxLevel+1;
}

int TreeReader::getNodeCoordinates(int node,int parent,int lv,int deltaY,int xBegin,int xEnd,std::vector<std::pair<int,int> > & coords){
    int x = (xBegin+xEnd)/2, y = deltaY*lv;
    qInfo() << "***node: " << node << " xBegin: " << xBegin << " xEnd: " << xEnd;
    coords[node]=std::make_pair(x,y);
    int childrenCount=graph[node].size();
    int deltaX=(xEnd-xBegin+1)/std::max(1,childrenCount- (node==0?0:1));
    int j=0;
    for(auto child: graph[node]){
        if(child.node!=parent)
            qInfo() << " child: " << child.node;
    }
    for(int i=0;i<childrenCount;i++){
        auto child=graph[node][i];
        if(child.node!=parent){
            //qInfo() << "parent: " << node << " child: " << child.node;
            getNodeCoordinates(child.node,node,lv+1,deltaY,xBegin+deltaX*j,xBegin+deltaX*(j+1),coords);
            j++;
        }
    }
}
std::vector<std::pair<int,int> > TreeReader::getNodeCoordinates(int width,int height){
    qInfo() << "TreeReader::getNodeCoordinates():";
    auto heightInLevels=getMaxLevel(0,0,0);
    qInfo() << "n= " << graph.size() << "\n";
    std::vector<std::pair<int,int> > ans(graph.size()); //.first = x , .second = y
    qInfo() << "width: " << width << " height: " << height << "\n";
    qInfo() << "ans.size(): " << ans.size() << "\n";
    auto deltaY = height/heightInLevels;
    getNodeCoordinates(0,0,0,deltaY,0,width,ans);
    return ans;
}

