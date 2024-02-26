#ifndef RESIDENCE_H
#define RESIDENCE_H
#include <string>
using namespace std;
class DataBase;
class Residence{
    private:
    int index;
    int owner;
    int upgradeLevel = 0;
    int belongToTiles[3];
    int relatedRoads[4];
    bool hasOwner = false;
    DataBase* base;
    public:
    Residence(int index, int owner, int belongToTiles[], int relatedRoads[], DataBase* base):
        index{index}, owner{owner}, base{base}{
            for(int i = 0; i < 3;i++){this->belongToTiles[i] = belongToTiles[i];}
            for(int i = 0; i < 4;i++){this->relatedRoads[i] = relatedRoads[i];}
        }
    ~Residence(){}
    int getIndex();
    int getOwner();
    int getTile(int pos);
    int getRoad(int pos);
    int getLevel();
    bool isHasOwner();
    string printIndex();
    string getUpgradeLevel();
    string getFullUpgradeLevel();
    void setOwner(int index);
    void upgrade();
};

#endif
