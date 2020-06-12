#ifndef SEGMENTTREE_H
#define SEGMENTTREE_H

#include <vector>
#include <algorithm>
#include <functional>


class SegmentTree
{
public:
    SegmentTree();
    SegmentTree(const std::vector<int>& values);
    SegmentTree(const std::vector<int>& values, std::function<int(int,int)> aggregationFunction);
    void Build(int dir, int l, int r);
    int GetRangeAns(int l, int r);
    void UpdatePos(int pos, int newValue);
protected:
private:
    struct Node {
        int l, r, value;
    };
    std::vector<int> values = std::vector<int>();
    std::vector<Node> SEG;
    std::function<int(int, int)> aggregationFunction;
    int GetRangeAns(int dir, int l, int r);
    void UpdatePos(int dir, int pos, int newValue);
    bool noContained(int dir,int l,int r);

};

#endif // SEGMENTTREE_H
