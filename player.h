#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include "random.h"
#include <iostream>
#include <sstream>
#include <memory>
using namespace std;
class DataBase;
class Player{
    private:
    int index;
    string color;
    int numBrick = 0;
    int numEnergy = 0;
    int numWifi = 0;
    int numHeat = 0;
    int numGlass = 0;
    int builderPoint = 2;
    int diceType;
    int randomSeed = std::chrono::system_clock::now().time_since_epoch().count();
    int findMin(int i1, int i2);
    bool withIn(int i, std::vector<int> v, int size);
    int pets = 0;
    bool maxpets = false;
    public:
    Player(int index, string color, int diceType):index{index},color{color},diceType{diceType}{}
    ~Player(){}
    void addRes(int type, int num);
    void setDiceType(int diceType);
    int rollADice(int seed);
    string getColor();
    void playerResPrint();
    bool canBuildRoad();
    void buildRoad();
    bool canBuildRes();
    void buildRes();
    bool canUpgradeT2();
    bool canUpgradeT3();
    void upgradeT2();
    void upgradeT3();
    bool isWinner();
    void setSeed(long unsigned int randomSeed);
    bool canTradeRes(int resType);
    bool canTradeMultiRes(int resType, int resNum);
    void tradeRes(int giveResType, int receiveResType);
    void tradeMultiRes(int giveResType, int receiveResType, int giveResNum, int receiveResNum);
    bool canLosetoGeese();
    void loseRestoGeese(shared_ptr<Random> randomGenerator);
    bool hasRes();
    int loseRes(shared_ptr<Random> randomGenerator);
    ostream& getResources(ostream& out);
    void setResources(int Resnum, int type);
    void addAllRes(int resNum);
    void addPet();
    bool canAddPet();
    int getPetsNum();
    void setMostPets(bool setval);
};


#endif
