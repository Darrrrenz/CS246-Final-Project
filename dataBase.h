#ifndef DATABASE_H
#define DATABASE_H
#include "road.h"
#include "tile.h"
#include "residence.h"
#include "random.h"
#include "player.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <memory>
#define NUM_ROADS 72
#define NUM_TILES 19
#define NUM_RESIDENCE 54
#define NUM_PLAYER 4
using namespace std;
class DataBase{
    private:
    long unsigned int randomSeed = std::chrono::system_clock::now().time_since_epoch().count();
    shared_ptr<Random> randomGenerator = make_shared<Random>(randomSeed);
    shared_ptr<Road> roads[NUM_ROADS];
    shared_ptr<Tile> tiles[NUM_TILES];
    shared_ptr<Residence> residences[NUM_RESIDENCE];
    shared_ptr<Player> players[NUM_PLAYER];
    string transformRes(int resIndex);
    public:
    DataBase();
    ~DataBase();
    void setRoad(shared_ptr<Road> nRoad, int pos);
    void setTile(shared_ptr<Tile> ntile, int pos);
    void setResidence(shared_ptr<Residence> nRes, int pos);
    void printBoard();
    bool setResOwner(int resIndex, int playerIndex);
    bool setRoadOwner(int roadIndex, int playerIndex);
    bool canTransNumber(string str);
    bool endWithWinner();
    string getPlayerColor(int index);
    void setPlayerDiceType(int playerIndex, int diceType);
    int playerRoll(int playerIndex);
    void distributeRes(int rollNum, int playerIndex);
    void printPlayerStatus();
    void printPlayerResidence(int playerIndex);
    void buildRoad(int playerIndex, int roadIndex);
    void buildRes(int playerIndex, int resIndex);
    void upgradeRes(int playerIndex, int resIndex);
    bool findWinner();
    void trade(int startPlayerIndex, int receivePlayerIndex, int giveRes, int receiveRes);
    void freeTrade(int startPlayerIndex, int receivePlayerIndex, int giveRes, int giveResNum, int receiveRes, int receiveResNum);
    int transformPlayer(string player);
    int transformRes(string res);
    string transformResInt(int res);
    ostream& savePlayerData(ostream& out, int playerIndex);
    ostream& saveBoard(ostream& out);
    int saveGeeseRes();
    void loadPlayerData(string data, int playerIndex);
    void loadBoardData(string data, int geeseIndex);
    void setRandomSeed(int seed);
    void baseRes(int type);
    int getGeesePos();
    void getAPet(int playerindex);
    void checkPetPoints();
};

#endif
