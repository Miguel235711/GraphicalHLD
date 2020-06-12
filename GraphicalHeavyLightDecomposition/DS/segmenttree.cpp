#include "segmenttree.h"

SegmentTree::SegmentTree()
{

}
bool SegmentTree::noContained(int dir,int l,int r){
    return SEG[dir].l>r || SEG[dir].r<l;
}
int SegmentTree::GetRangeAns(int dir, int l, int r) { // O(log(N))
    //getvalue(3,5) [dir].l -> 6
    //              [dir].r -> 8
    //SEG[dir].l -> 1
    //SEG[dir].r -> 2
    //getvalue(0, 3);
    if (l <= SEG[dir].l && SEG[dir].r <= r)
        return SEG[dir].value;
    if(noContained(dir*2+1,l,r))
        return GetRangeAns(dir*2+2,l,r);
    else if(noContained(dir*2+2,l,r))
        return GetRangeAns(dir*2+1,l,r);
    return aggregationFunction(
        GetRangeAns(dir * 2 + 1, l, r),
        GetRangeAns(dir * 2 + 2, l, r)
    );
}
void SegmentTree::UpdatePos(int dir, int pos, int newValue) { // O(log(N))
    if (SEG[dir].l == SEG[dir].r) {
        SEG[dir].value = values[pos] = newValue;
        return;
    }
    if (pos <= SEG[dir * 2 + 1].r)
        UpdatePos(dir * 2 + 1, pos, newValue);
    else
        UpdatePos(dir * 2 + 2, pos, newValue);
    SEG[dir].value = aggregationFunction(SEG[dir * 2 + 1].value, SEG[dir * 2 + 2].value);
}
SegmentTree::SegmentTree(const std::vector<int>& values) { // O(4N)
    this->values = values;
    this->SEG.resize(values.size() * 4);
    Build(0, 0, (values.size() - 1));
}
SegmentTree::SegmentTree(const std::vector<int>& values, std::function<int(int,int)>aggregationFunction) { // O(4N)
    this->values = values;
    this->SEG.resize(values.size()*4);
    this->aggregationFunction = aggregationFunction;
    Build(0, 0, (values.size()-1));

}
void SegmentTree::Build(int dir, int l, int r) { // O(4N)
    SEG[dir].l = l;
    SEG[dir].r = r;
    if (l == r) {
        SEG[dir].value = values[l];
        return;
    }
    int mid = (l + r) / 2;
    Build(dir * 2 + 1, l, mid);
    Build(dir * 2 + 2, mid + 1, r);
    SEG[dir].value = this->aggregationFunction(SEG[dir * 2 + 1].value, SEG[dir * 2 + 2].value);
}
int SegmentTree::GetRangeAns(int l, int r) {  //log(N)
    return GetRangeAns(0, l, r);
}
void SegmentTree::UpdatePos(int pos, int newValue) { //log(N)
    return UpdatePos(0, pos, newValue);
}
