#ifndef TILE_H
#define TILE_H
#include <string>
using namespace std;
class DataBase;
class Tile{
    private:
    int index;
    int typeRes = 0;
    int numRes = 0;
    int roads[6];
    int residences[6];
    bool hasGeese = false;
    int geeseRes = 0;
    DataBase* base;
    public:
    Tile(int index,int typeRes,int numRes, int roads[], int residences[], bool hasGeese, int geeseRes, DataBase* base):
        index{index}, typeRes{typeRes}, numRes{numRes}, hasGeese{hasGeese}, geeseRes{geeseRes}, base{base}{
            for(int i = 0; i < 6; i++){
                this->roads[i] = roads[i];
                this->residences[i] = residences[i];
            }
        }
    ~Tile(){}
    int getIndex();
    string getTypeRes();
    string normalGetTypeRes();
    int getnumRes();
    int getRoad(int pos);
    int getResidences(int pos);
    bool isHasGeese();
    int getGeeseRes();
    int getResType();
    void setGeese(bool trigger);
    void setTypeNum(int newType, int newNum); // load tile resource type and roll number
};

#endif
