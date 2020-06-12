#include "hld.h"

HLD::HLD(QString filePath)
{
    std::ifstream in;
    in.open(filePath.toStdString());
    if(!in.is_open()){
        qInfo() << "error, filename not valid\n";
        return;
    }
    int a,b,w;
    in >> n; // number of nodes , nodes are numbered from 0 to n-1
    initializeVectors(n);
    for(int i=1;i<n;i++){//edges are numbered from 0 to n-2
        in>>a>>b>>w;
        graph[a].push_back(edge(i-1,b,w));
        graph[b].push_back(edge(i-1,a,w));
        existsEdge[a].insert(b);
        existsEdge[b].insert(a);
    }
    buildHeavyLightDecomposition();
    //debugPrint();
    //test LCA
    //cout << "************LCA init:\n";
    lca = LCA(parentEdge);
    //initialize segment tree!!!!
    qInfo() << "before calling initSegmentTree";
    initSegmentTrees();
    qInfo() << "after calling initSegmentTree";
}
int HLD::saveMaximumChildAndGetChildSubtreeSize(int childSubtreeSize,int & maxChildSubtreeSize, int & maxChild, int child){ //O(1)
    if(childSubtreeSize>maxChildSubtreeSize){
        maxChildSubtreeSize=childSubtreeSize;
        maxChild=child;
    }
    return childSubtreeSize;
}

int HLD::overToWithCeil(int x){
    return x/2+(x&1);
}

int HLD::calculateHeavyLightEdges(int node,int parent){ //O(N)
    int totalNodesInSubtree=1,maxChildSubtreeSize=0,maxChild=0;
    for(edge child:graph[node])
        if(child.node!=parent){
            totalNodesInSubtree+=saveMaximumChildAndGetChildSubtreeSize(calculateHeavyLightEdges(child.node,node),maxChildSubtreeSize,maxChild,child.node);
            parentEdge[child.node].parent=node;
            parentEdge[child.node].edgeNumber=child.edgeNumber;
            parentEdge[child.node].weight=child.weight;
            mapEdgeParent[child.edgeNumber]=node;
        }
    hasHeavyChild[node]=parentEdge[maxChild].isHeavy=maxChildSubtreeSize>=overToWithCeil(totalNodesInSubtree);
    return totalNodesInSubtree;
}

void HLD::calculateHeavyPaths(){//N
    for(int i=0;i<graph.size();i++)
        if(!hasHeavyChild[i]){
            ///calculate heavy path
            int indexOfSeg=segmentTreeRanges.size();
            segEdgeRange newSeg;
            for(int node=i,indexInSeg=0;;node=parentEdge[node].parent,indexInSeg++){
                if(indexInSeg==0)
                    newSeg.begin=parentEdge[node].edgeNumber;
                /*if(node ==9){
                    qInfo() << "indexInSeg: " << indexInSeg << "segIndex: " << indexOfSeg << "i: " << i ;
                    qInfo() << "is 4 parent heavy edge: " << parentEdge[4].isHeavy;
                }*/
                edgeToSegmentTree[parentEdge[node].edgeNumber].segIndex=indexOfSeg;
                edgeToSegmentTree[parentEdge[node].edgeNumber].indexInSeg=indexInSeg;
                if(parentEdge[node].parent==0||!parentEdge[node].isHeavy){ //root or parent with light edge
                    newSeg.end=parentEdge[node].edgeNumber;
                    break;
                }
            }
            segmentTreeRanges.push_back(newSeg);
        }
}

void HLD::initializeVectors(int n){ // O(5N)
    existsEdge = std::vector<std::set<int> >(n);
    graph = std::vector<std::vector<edge> >(n,std::vector<edge>());
    parentEdge = std::vector<ParentInfo>(n,ParentInfo());
    edgeToSegmentTree = std::vector<segInfo>(n-1,segInfo());
    hasHeavyChild = std::vector<bool>(n);
    mapEdgeParent = std::vector<int>(n-1);
}

void HLD::buildHeavyLightDecomposition(){
    calculateHeavyLightEdges(0,0);
    calculateHeavyPaths();
}

/*void debugPrint(){
    cout << "graph:\n";
    for(int i=0;i<n;i++){
        cout << "adjacent to " << i << ":\n";
        for(edge edgeV: graph[i]){
            cout << "|( node = " << edgeV.node << " , edgeNumber = " << edgeV.edgeNumber << " , edgeWeight = " << edgeV.weight << " )|\n";
        }
    }
    cout << "parentEdge:\n";
    for(int i=0;i<n;i++)
        cout << "( node = " << i << " , parent = " << parentEdge[i].parent << " , weight = " << parentEdge[i].weight << " , edgeNumber = "
        << parentEdge[i].edgeNumber << " , isHeavy = " << parentEdge[i].isHeavy << " )\n";
    cout << "edgeToSegmentTree:\n";
    for(int i=0;i<n-1;i++)
        cout << "( edge = " << i << " , segIndex = " << edgeToSegmentTree[i].segIndex << " , indexInSeg = " << edgeToSegmentTree[i].indexInSeg
        << " )\n";
    cout << "hasHeavyChild:\n";
    for(int i=0;i<n;i++)
        cout << "( node = " << i << " , hasHeavyChild = " << hasHeavyChild[i] << " )\n";
    cout << "segmentTreeRanges:\n";
    for(int i=0;i<segmentTreeRanges.size();i++)
        cout << "( segmentTreeNumber = " << i << " , begin = " << segmentTreeRanges[i].begin << " , end = " << segmentTreeRanges[i].end << " )\n";
}*/

int HLD::ansOfMovingNodeToLCA(int node,int lcaNode,queryType qType,bool & flag){
    //qInfo() << "1.node: " << node << " lcaNode: " << lcaNode;
    int ans=10000;
    if(lcaNode==node)
        return ans;
    while(node&&lca.compareLevel(mapEdgeParent[segmentTreeRanges[edgeToSegmentTree[parentEdge[node].edgeNumber].segIndex].end],lcaNode)>=0){
        //qInfo() << "**node: " << node ;
        int segIndex=edgeToSegmentTree[parentEdge[node].edgeNumber].segIndex;
        //qInfo() << "segBeg: " << segmentTreeRanges[segIndex].begin ;
        //qInfo() << "**parent: " << parentEdge[node].parent;
        //qInfo() << "begQuery: " << edgeToSegmentTree[parentEdge[node].edgeNumber].indexInSeg << "endQuery: " << edgeToSegmentTree[segmentTreeRanges[segIndex].end].indexInSeg ;
        auto x = segmentTrees[qType][segIndex].GetRangeAns(edgeToSegmentTree[parentEdge[node].edgeNumber].indexInSeg,edgeToSegmentTree[segmentTreeRanges[segIndex].end].indexInSeg);
        if(flag){
            qInfo() << "x: " << x << "qType: " << qType;
            ans=x;
            qInfo() << "ans: " << ans;
            flag=false;
        }else{
            qInfo() << "ans: " << ans ;
            ans=comparators[qType](ans,x);
        }
        node = mapEdgeParent[segmentTreeRanges[edgeToSegmentTree[parentEdge[node].edgeNumber].segIndex].end];
    }
    //qInfo() << "2.node: " << node << "lca: " << lcaNode;
    if(node&&edgeToSegmentTree[parentEdge[node].edgeNumber].segIndex==edgeToSegmentTree[parentEdge[lcaNode].edgeNumber].segIndex&&edgeToSegmentTree[parentEdge[node].edgeNumber].indexInSeg<=edgeToSegmentTree[parentEdge[lcaNode].edgeNumber].indexInSeg-1){
        int segIndex=edgeToSegmentTree[parentEdge[node].edgeNumber].segIndex;
        auto x = segmentTrees[qType][segIndex].GetRangeAns(edgeToSegmentTree[parentEdge[node].edgeNumber].indexInSeg,edgeToSegmentTree[parentEdge[lcaNode].edgeNumber].indexInSeg-1);
        if(flag){
            qInfo() << "x: " << x << "qType " << qType;
            ans=x;
            flag=false;
        }else{
            ans=comparators[qType](ans,x);
            qInfo() << "*ans: " << ans ;
        }
    }
    qInfo() << "**ans: " << ans ;
    return ans;
}

int HLD::query(int a,int b,queryType qType){
    int lcaNode = lca.getLCANode(a,b);
    bool flag1=true,flag2=true;
    int res1=ansOfMovingNodeToLCA(a,lcaNode,qType,flag1), res2=ansOfMovingNodeToLCA(b,lcaNode,qType,flag2);
    if(flag1&&flag2)
       return 0;
    if(flag1)
        return res2;
    if(flag2)
        return res1;
    return comparators[qType](res1,res2);
}

void HLD::update(int edgeIndex,int w){ //(log(N))
    for(int i=0;i<segmentTrees.size();i++)
        segmentTrees[i][edgeToSegmentTree[edgeIndex].segIndex].UpdatePos(edgeToSegmentTree[edgeIndex].indexInSeg,w);
}
bool HLD::update(int a, int b,int w){
    ///find if it exists edge between this
    auto isABAnEdge= existsEdge[a].find(b);
    if(isABAnEdge==existsEdge[a].end()) //case when the edge does not exist
        return false;
    if(lca.compareLevel(a,b)<0) //level[a]<level[b]
        std::swap(a,b);
    //level[a]>level[b]
    qInfo() << "update(a,b,w) a: " << a << " b: " << b;
    update(parentEdge[a].edgeNumber,w);
    return true;
}

void HLD::initSegmentTrees(){
    segmentTrees=std::vector<std::vector<SegmentTree> >(Count,std::vector<SegmentTree>(segmentTreeRanges.size()));
    qInfo()<<"number of types: "<<segmentTrees.size();
    qInfo() <<"number of segmentTrees per type: "<<segmentTrees[0].size() << " | " << segmentTreeRanges.size()<<"\n";
    int times=0;
    for(int origNode=0;origNode<graph.size();origNode++){
        int segmentIndex=edgeToSegmentTree[parentEdge[origNode].edgeNumber].segIndex;
        if(!hasHeavyChild[origNode]){
            qInfo()  <<  ++times;
            std::vector<int> values;
            for(int node=origNode;;node=parentEdge[node].parent){
                values.push_back(parentEdge[node].weight);
                if(parentEdge[node].edgeNumber==segmentTreeRanges[segmentIndex].end)
                    break;
            }
            qInfo() << "segmentTrees.size(): " << segmentTrees.size() << "\n";
            for(int i=0;i<segmentTrees.size();i++){
                //qInfo() << "i: " << i;
                //qInfo() << "insideForSize: "<<segmentTrees[i].size() << "\n";
                //if(comparators[i]){
                //    qInfo()<<"mmm....";
                ///}
                //qInfo() << " null";
                segmentTrees[i][segmentIndex]=SegmentTree(values,
                    comparators[i]
                );

                //qInfo() << "for to create segment trees: " << segmentTrees[i].size();
            }
            qInfo() << "after creating...";
        }
    }
    qInfo() << "initSegmentTrees end: ";
}


