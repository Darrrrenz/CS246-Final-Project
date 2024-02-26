#ifndef ROAD_H
#define ROAD_H
#include <string>
using namespace std;
class DataBase;
class Road{
    private:
    int index;
    int endOne;
    int endTwo;
    int owner;
    bool hasOwner;
    DataBase* base;
    public:
    Road(int index, int endOne, int endTwo, int owner, bool hasOwner, DataBase* base):index{index}, endOne{endOne},
        endTwo{endTwo}, owner{owner}, hasOwner{hasOwner}, base{base}{}
    ~Road();
    int getIndex();
    int getEndOne();
    int getEndTwo();
    int getOwner();
    bool isHasOwner();
    string printIndex();
    void setOwner(int index);
};

#endif
