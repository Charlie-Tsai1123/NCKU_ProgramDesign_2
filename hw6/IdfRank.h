#ifndef IDFRANK_H
#define IDFRANK_H
class IdfRank {
    public:
        int line;
        double idfSum;
        IdfRank (int line, double idfSum):line(line), idfSum(idfSum) {};
        IdfRank() {};
};
#endif