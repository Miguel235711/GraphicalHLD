#ifndef PARENTINFO_H
#define PARENTINFO_H


struct ParentInfo{
    int parent /*initialize in -1*/,edgeNumber,weight;
    bool isHeavy;
    ParentInfo(){
        this->parent=this->edgeNumber=this->weight=-1;
        this->isHeavy=false;
    }
};

#endif // PARENTINFO_H
