#include "lca.h"

LCA::LCA()
{

}

void LCA::calculateLevels(int node,int lv,int parent){//O(N)
    level[node]=lv;
    for (int child:graph[node])
        if(child!=parent)
            calculateLevels(child,lv+1,node);
}
void LCA::calculateAnscestors(){//DP O(Nlog(N))
    for(int p=1;p<exp;p++)
        for(int node=0;node<graph.size();node++)
            anscestor[p][node]=anscestor[p-1][anscestor[p-1][node]];
}
std::vector<int> LCA::getParentNodes(const std::vector<ParentInfo> & parent){ // O(N)
    std::vector<int> ans;
    for(int i=0;i<parent.size();i++){
        //cout << "parent of i: " << parent[i].parent << "\n";
        ans.push_back(parent[i].parent==-1?0:parent[i].parent);
    }
    return ans;
}
LCA::LCA(const std::vector<ParentInfo> & parent){ // O(Nlog(N))
    this->parent = getParentNodes(parent);
    //this->parent[0]=0;
    this->exp=ceil(std::log2(parent.size()))+1;
    anscestor = std::vector<std::vector<int> >(exp,std::vector<int>(parent.size()));
    graph = std::vector<std::vector<int> >(parent.size(),std::vector<int>());
    for(int i=0;i<parent.size();i++){
        anscestor[0][i]=this->parent[i];
        graph[i].push_back(this->parent[i]);
        graph[this->parent[i]].push_back(i);
    }
    calculateAnscestors();
    level = std::vector<int>(parent.size());
    calculateLevels(0,0,0);
}
int LCA::getLCANode(int a, int b){ // O(logn)
    //make that level[a] >= level[b]
    if(level[a]<level[b])
        std::swap(a,b);
    //make level[a] equal to level[b]
    for(int p=exp-1;p>-1;p--){
        if(level[anscestor[p][a]]>=level[b]){
            a = anscestor[p][a];
        }
    }
    //cout << "a: " << a << "b: " << b << "exp: " << exp << "\n";
    //cout << "anscestors: " << anscestor[0][4] << " " << anscestor[0][1] << "\n";
    //now, level[a]==level[b]
    for(int p=exp-1;p>-1;p--){
        if(anscestor[p][a]!=anscestor[p][b]){
            a=anscestor[p][a];
            b=anscestor[p][b];
        }
    }
    //cout << "a: " << a << "b: " << b << "\n";
    return a==b ? a:anscestor[0][a];
}
int LCA::compareLevel(int a,int b){
    return level[a]-level[b];
}
