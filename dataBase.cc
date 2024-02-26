#include "dataBase.h"
using namespace std;
void DataBase::setRoad(shared_ptr<Road> nRoad, int pos){(this->roads)[pos] = nRoad;}
void DataBase::setTile(shared_ptr<Tile> ntile, int pos){(this->tiles)[pos] = ntile;}
void DataBase::setResidence(shared_ptr<Residence> nRes, int pos){(this->residences)[pos] = nRes;}

DataBase::~DataBase(){}

DataBase::DataBase(){
    for(int i = 0;i<NUM_ROADS;i++){roads[i] = nullptr;}
    for(int i = 0;i<NUM_TILES;i++){tiles[i] = nullptr;}
    for(int i = 0;i<NUM_RESIDENCE;i++){residences[i] = nullptr;}
    int resourceList[NUM_TILES] = {0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5};
    int numList[NUM_TILES] = {2, 3, 3, 4, 4, 5, 5, 6, 6, 8, 8, 9, 9, 10, 10, 11, 11, 12, -1};
    ifstream file{"arrangement.dat"};
    while(!file.eof()){
        string line;
        getline(file,line);
        if(line != ""){
        istringstream sin{line};
        while(!sin.eof()){
            string segment;
            getline(sin,segment,'|');
            istringstream ss{segment};
            int type;
            ss >> type ;
            if(type == 0){
                int index, roadList1, roadList2, residenceList1, residenceList2;
                ss >> index >> residenceList1 >> residenceList2 >> roadList1 >> roadList2;
                int temp1[6];
                int temp2[6];
                for(int i = 0;i<6;i++){
                    if(i <= 2){
                        temp1[i] = residenceList1 % 100;
                        temp2[i] = roadList1 % 100;
                        residenceList1 /= 100;
                        roadList1 /= 100;
                    }
                    else{
                        temp1[i] = residenceList2 % 100;
                        temp2[i] = roadList2 % 100;
                        residenceList2 /= 100;
                        roadList2 /= 100;
                    }
                }
                int resType = this->randomGenerator->generateTypeII();
                while(resourceList[resType] == -1){resType = this->randomGenerator->generateTypeII();}
                int res = resourceList[resType];
                resourceList[resType] = -1;

                int resVal = this->randomGenerator->generateTypeII();
                int value = 0;
                if(res == 5){value = 7;}
                else{
                    while(numList[resVal] == -1){resVal = this->randomGenerator->generateTypeII();}
                    value = numList[resVal];
                    numList[resVal] = -1;
                }
                shared_ptr<Tile> nTile = make_shared<Tile>(index, res, value, temp2, temp1, false, -1, this);
                if(res == 5){nTile->setGeese(true);}
                this->setTile(nTile, index);
            }
            else if(type == 1){
                int index, neighbour, belongTiles;
                ss >> index >> neighbour >> belongTiles;
                int temp1[4];
                for(int i = 0; i < 4; i++){
                    int seg = neighbour%100;
                    neighbour /= 100;
                    if(seg >= NUM_ROADS){temp1[3-i] = -1;}
                    else{temp1[3-i] = seg;}
                }
                int temp2[3];
                for(int i = 0; i < 3;i++){
                    int seg = belongTiles%100;
                    belongTiles /= 100;
                    if(seg >= NUM_TILES){temp2[i] = -1;}
                    else{temp2[i] = seg;}
                }
                shared_ptr<Residence> nRes = make_shared<Residence>(index, -1, temp2, temp1, this);
                this->setResidence(nRes,index);
            }
            else if(type == 2){
                int index, neighbour, belongTiles;
                ss >> index >> neighbour >> belongTiles;
                int temp1 = neighbour % 100;
                int temp2 = neighbour / 100;
                shared_ptr<Road> nRoad = make_shared<Road>(index, temp1, temp2, -1, false, this);
                this->setRoad(nRoad, index);
            }
        }
        }
    }
    file.close();
    players[0] = make_shared<Player>(0,"BLUE",1);
    players[1] = make_shared<Player>(1,"RED",1);
    players[2] = make_shared<Player>(2,"ORANGE",1);
    players[3] = make_shared<Player>(3,"YELLOW",1);
    for(int i = 0;i<4;i++){players[i]->setSeed(randomSeed*randomSeed*i - 2 * randomSeed);}
}

void DataBase::printBoard(){
    ifstream file{"format.dat"};
    while(!file.eof()){
        string line;
        getline(file,line);
        if(line != ""){
        istringstream sin{line};
        while(!sin.eof()){
            string segment;
            getline(sin,segment,'|');
            istringstream sin2{segment};
            int type, index, special;
            sin2 >> type >> index >> special;
            if(type == 0){
                if(special == 0){
                    if (index < 10){cout << "    " << index << "   ";}
                    else{cout << "   " << index << "   ";}
                }
                else if(special == 1){cout << (this->tiles[index])->getTypeRes();}//remember to change this later....
                else if(special == 2){
                    int n = (this->tiles[index])->getnumRes();
                    if(this->tiles[index]->getResType() == 5){cout << "       ";}
                    else if (n < 10){cout << "   " << n << "  ";}
                    else{cout << "  " << n << "  ";}
                }
                else if(special == 3){
                    if(this->tiles[index]->getResType() == 5){cout << "         ";}
                    else if(this->tiles[index]->isHasGeese()){cout << "  GEESE  ";}
                    else{cout << "         ";}
                }
            }
            else if(type == 1){
                if(this->residences[index] == nullptr){continue;}
                else{
                    shared_ptr<Residence> res = (this->residences)[index];
                    if(!res->isHasOwner()){
                        int n = (this->residences)[index]->getIndex();
                        if (n < 10){cout << "| " << n << "|";}
                        else{cout << "|" << n << "|";}
                    }
                    else{
                        int playerIndex = res->getOwner();
                        string playerColor = this->players[playerIndex]->getColor();
                        string upgrade = res->getUpgradeLevel();
                        cout << "|" << playerColor.substr(0,1) << upgrade << "|";
                    }
                }
            }
            else if(type == 2){
                if(this->roads[index] == nullptr){continue;}
                else{
                    shared_ptr<Road> roa = this->roads[index];
                    if(!roa->isHasOwner()){
                        int n = (this->roads)[index]->getIndex();
                        if (n < 10){cout << " " << n;}
                        else{cout << n;}
                    }
                    else{
                        int playerIndex = roa->getOwner();
                        string roadColor = this->players[playerIndex]->getColor();
                        cout << roadColor.substr(0,1) << 'R';
                    }
                }
            }
            else if(type == 3){
                if(special == 0){cout << "--";}
                else{cout << "|";}
            }
            else if(type == 4){
                for(int i = 0;i < special;i++){
                    cout << " ";
                }
            }
            else{continue;}
        }
        cout << endl;
        }
    }
    file.close();
}

bool DataBase::setResOwner(int resIndex, int playerIndex){
    // check adjacent residences
    bool hasAdjRes = false;
    for(int i=0; i<4; i++){
        int roadindex = this->residences[resIndex]->getRoad(i);
        if(roadindex >= 0 && roadindex < NUM_ROADS){
            shared_ptr<Road> checkRoad = this->roads[roadindex];
            int adjacentRes;
            if(checkRoad->getEndOne() == resIndex){adjacentRes = checkRoad->getEndTwo();}
            else if(checkRoad->getEndTwo() == resIndex){adjacentRes = checkRoad->getEndOne();}
            if(this->residences[adjacentRes]->isHasOwner() == true){
                hasAdjRes = true;
                break;
            }
        }
    }
    if(this->residences[resIndex]->isHasOwner()){
        cout << "YOU CANNOT CHOOSE THIS RESIDENCE, IT ALREADY HAS OWNER" << endl; //may need to change
        return false;
    }
    else if(hasAdjRes){
        cout << "YOU CANNOT CHOOSE THIS RESIDENCE, IT'S ADJACENT RESIDENCE HAS OWNER" << endl; //may need to change
        return false;
    }
    else{
        this->residences[resIndex]->setOwner(playerIndex);
        printBoard();
        return true;
    }
}
bool DataBase::setRoadOwner(int roadIndex, int playerIndex){
    if(this->roads[roadIndex]->isHasOwner()){
        cout << "YOU CANNOT CHOOSE THIS ROAD, IT ALREADY HAS OWNER" << endl; //may need to change
        return false;
    }
    else{
        this->roads[roadIndex]->setOwner(playerIndex);
        printBoard();
        return true;
    }
}

string DataBase::getPlayerColor(int index){return this->players[index]->getColor();}
void DataBase::setPlayerDiceType(int playerIndex, int diceType){this->players[playerIndex]->setDiceType(diceType);}
int DataBase::playerRoll(int playerIndex){return this->players[playerIndex]->rollADice(this->randomGenerator->generate());}
void DataBase::distributeRes(int rollNum, int playerIndex){
    if(rollNum == 7){
        shared_ptr<Tile> geeseTile = nullptr;
        for(int i = 0;i<NUM_TILES;i++){
            if(this->tiles[i]->isHasGeese()){
                geeseTile = this->tiles[i];
                break;
            }
        }
        for(int i = 0;i < 4;i++){if(this->players[i]->canLosetoGeese()){this->players[i]->loseRestoGeese(this->randomGenerator);}}
        cout << "choose where to place the GEESE" << endl;
        string input;
        int pos;
        cin >> input;
        //security...
        while(!cin.eof()){
            if(!canTransNumber(input)){cout << "Please input a valid index." << endl;}
            else{
                pos = stoi(input);
                if(pos < 0 || pos >= NUM_TILES){
                    cout << "Please input a valid index." << endl;
                }
                else if((geeseTile->getIndex()) == pos){
                    cout << "cannot move to the original tile, please choose another tile" << endl;
                }
                else{break;}
            }
            cin >> input;
        }
        if(cin.eof()){return;}
        shared_ptr<Tile> newGeeseTile = this->tiles[pos];
        geeseTile->setGeese(false);
        newGeeseTile->setGeese(true);
        int canSteal[4];
        for(int i = 0;i<4;i++){canSteal[i] = -1;}
        for(int i = 0;i < 6;i++){
            int resIndex = newGeeseTile->getResidences(i);
            if(this->residences[resIndex]->isHasOwner() && 
            this->players[this->residences[resIndex]->getOwner()]->hasRes()){
                canSteal[this->residences[resIndex]->getOwner()] = 1;
            }
        }
        bool empty = true;
        for(int i = 0;i < 4;i++){
            if(canSteal[i] != -1 && i != playerIndex){empty = false;}
        }
        if(empty){cout << "Builder " << this->players[playerIndex]->getColor() << " has no builders to steal form." << endl;}
        else{
            cout << "Builder " << this->players[playerIndex]->getColor() << " can choose to steal from ";
            for(int i = 0;i < 4;i++){
                if(canSteal[i] != -1 && i != playerIndex){cout << this->players[i]->getColor() << " ";}
            }
            cout << endl;
            cout << "Choose a builder to steal from." << endl;
            string color;
            cin >> color;
            while(!cin.eof()){
                if(color != "BLUE" && color != "YELLOW" && color != "ORANGE" && color != "RED"){
                    cout << "Please input a valid builder color." << endl;
                    cin >> color;
                }
                else if(color == this->players[playerIndex]->getColor()){
                    cout << "You cannot steal from yourself." << endl;
                    cin >> color;
                }
                else if(canSteal[transformPlayer(color)] == -1){
                    cout << "You cannot steal from this player." << endl;
                }
                else{break;}
            }
            if(cin.eof()){return;}
            int index = transformPlayer(color);
            int typeRes = this->players[index]->loseRes(this->randomGenerator);
            this->players[playerIndex]->addRes(typeRes,1);
            cout << "Builder " << this->players[playerIndex]->getColor() << " steals "
                << transformResInt(typeRes) << " from Builder " << this->players[index]->getColor() << endl;
        }
        return;
    }  //change this for geese
    int newRes[NUM_PLAYER][5];
    for(int i = 0;i<NUM_PLAYER;i++){
        for(int j = 0;j<5;j++){
            newRes[i][j] = 0;
        }
    }
    for(int i = 0;i<NUM_TILES;i++){
        shared_ptr<Tile> curTile = this->tiles[i];
        if(curTile->getnumRes() == rollNum && !curTile->isHasGeese()){
            for(int j = 0; j < 6;j++){
                int resIndex = curTile->getResidences(j);
                if(this->residences[resIndex]->isHasOwner()){
                    int playerIndex = this->residences[resIndex]->getOwner();
                    int initialNum = this->residences[resIndex]->getLevel() + 1;
                    newRes[playerIndex][curTile->getResType()] += initialNum;
                    this->players[playerIndex]->addRes(curTile->getResType(),initialNum);
                }
            }
        }
    }
    bool isEmpty = true;
    for(int i = 0;i<NUM_PLAYER;i++){
        bool playerIsEmpty = true;
        for(int j = 0;j<5;j++){
            if(newRes[i][j] != 0){
                isEmpty = false;
                if(playerIsEmpty){
                    cout << "Builder " << this->players[i]->getColor() << " gained:" << endl;
                    playerIsEmpty = false;
                }
                cout << newRes[i][j];
                if(j == 0){cout << " BRICK" << endl;}
                else if(j == 1){ cout << " ENERGY" << endl;}
                else if(j == 2){ cout << " GLASS" << endl;}
                else if(j == 3){ cout << " HEAT" << endl;}
                else if(j == 4){ cout << " WIFI" << endl;}
                else{ cout << " INVALID" << endl;}
            }
        }
    }
    if(isEmpty){cout << "No builders gained resources." << endl;}
}

void DataBase::printPlayerStatus(){for(int i = 0;i<NUM_PLAYER;i++){this->players[i]->playerResPrint();}}
void DataBase::printPlayerResidence(int playerIndex){
    cout << "Builder " << this->players[playerIndex]->getColor() << " has built:" << endl;
    for(int i = 0;i<NUM_RESIDENCE;i++){
        if(this->residences[i]->isHasOwner() && this->residences[i]->getOwner() == playerIndex){
            cout << "A " << this->residences[i]->getFullUpgradeLevel() << " at position " << i << endl;
        }
    }
}

void DataBase::buildRoad(int playerIndex, int roadIndex){
    if(!this->players[playerIndex]->canBuildRoad()){
        cout << "You do not have enough resource." << endl;
        return;
    }
    if(roadIndex < 0 || roadIndex >= NUM_ROADS){
        cout << "Please input a valid road index." << endl;
        return;
    }
    shared_ptr<Road> curRoad = this->roads[roadIndex];
    if(curRoad->isHasOwner()){
        cout << "Cannot build here." << endl;
        return;
    }
    shared_ptr<Residence> endOne = this->residences[curRoad->getEndOne()];
    shared_ptr<Residence> endTwo = this->residences[curRoad->getEndTwo()];
    // add check for adjacent roads
    bool connectRoad = false;
    for(int i=0; i<4; i++){
        int roadindex = endOne->getRoad(i);
        if(roadindex >= 0 && roadindex < NUM_ROADS && roadindex != roadIndex){
            shared_ptr<Road> checkRoad = this->roads[roadindex];
            if(checkRoad->isHasOwner() && checkRoad->getOwner() == playerIndex){connectRoad = true;}
        }
    }
    for(int i=0; i<4; i++){
        int roadindex = endTwo->getRoad(i);
        if(roadindex >= 0 && roadindex <= NUM_ROADS && roadindex != roadIndex){
            shared_ptr<Road> checkRoad = this->roads[roadindex];
            if(checkRoad->isHasOwner() && checkRoad->getOwner() == playerIndex){connectRoad = true;}
        }
    }
    if(connectRoad == true){
        curRoad->setOwner(playerIndex);
        cout << "successfully build road at " << roadIndex << endl;
        this->players[playerIndex]->buildRoad();
    }
    else if((endOne->isHasOwner() && endOne->getOwner() == playerIndex)
      || (endTwo->isHasOwner() && endTwo->getOwner() == playerIndex)){
        curRoad->setOwner(playerIndex);
        cout << "successfully build road at " << roadIndex << endl;
        this->players[playerIndex]->buildRoad();
    }
    else{cout << "Cannot build here." << endl;}
}

void DataBase::buildRes(int playerIndex,int resIndex){
    if(!this->players[playerIndex]->canBuildRes()){
        cout << "You do not have enough resource." << endl;
        return;
    }
    if(resIndex < 0 || resIndex >= NUM_RESIDENCE){
        cout << "Please input a valid residence index." << endl;
        return;
    }
    shared_ptr<Residence> curRes = this->residences[resIndex];
    // add check for adjacent residences
    bool hasAdjRes = false;
    for(int i=0; i<4; i++){
        int roadindex = curRes->getRoad(i);
        if(roadindex >= 0 && roadindex < NUM_ROADS){
            shared_ptr<Road> checkRoad = this->roads[roadindex];
            int adjacentRes;
            if(checkRoad->getEndOne() == resIndex){adjacentRes = checkRoad->getEndTwo();}
            else if(checkRoad->getEndTwo() == resIndex){adjacentRes = checkRoad->getEndOne();}
            if(this->residences[adjacentRes]->isHasOwner() == true){hasAdjRes = true;}
        }
    }
    if(curRes->isHasOwner() || hasAdjRes == true){
        cout << "Cannot build here." << endl;
        return;
    }
    for(int i = 0;i<4;i++){
        int roadIndex = curRes->getRoad(i);
        if(roadIndex >= 0 && roadIndex < NUM_ROADS){
            shared_ptr<Road> curRoad = this->roads[roadIndex];
            if(curRoad->isHasOwner() && curRoad->getOwner() == playerIndex){
                curRes->setOwner(playerIndex);
                this->players[playerIndex]->buildRes();
                cout << "Successfully build residence at " << resIndex << endl;
                return;
            }
        }
    }
    cout << "Cannot build here." << endl;
}

void DataBase::upgradeRes(int playerIndex, int resIndex){
    shared_ptr<Residence> res = this->residences[resIndex];
    if(res->isHasOwner() && res->getOwner() != playerIndex){
        cout << "Cannot upgrade this residence." << endl;
        return;
    }
    else if(!res->isHasOwner()){
        cout << "Cannot upgrade this residence" << endl;
        return;
    }
    int upgradeLevel = res->getLevel();
    if(upgradeLevel >= 2){
        cout << "Cannot further upgrade this residence" << endl;
        return;
    }
    else if(upgradeLevel == 0){
        if(!this->players[playerIndex]->canUpgradeT2()){
            cout << "You do not have enough resource." << endl;
            return;
        }
        res->upgrade();
        this->players[playerIndex]->upgradeT2();
        cout << "Successfully upgrade basement " << resIndex << " to a house." << endl; 
    }
    else if(upgradeLevel == 1){
        if(!this->players[playerIndex]->canUpgradeT3()){
            cout << "You do not have enough resource." << endl;
            return;
        }
        res->upgrade();
        this->players[playerIndex]->upgradeT3();
        cout << "Successfully upgrade house " << resIndex << " to a tower." << endl;
    }
}

bool DataBase::findWinner(){
    for(int i = 0;i < NUM_PLAYER; i++){
        if(this->players[i]->isWinner()){
            cout << "        GAME ENDS!         " << endl;
            cout << "Builder " << this->players[i]->getColor() << " is the winner!" << endl;
            return true;
        }
    }
    return false;
}

bool DataBase::endWithWinner(){
    for(int i = 0;i < NUM_PLAYER; i++){
        if(this->players[i]->isWinner()){return true;}
    }
    return false;
}

string DataBase::transformRes(int resIndex){
    if(resIndex == 0){return "BRICK";}
    else if(resIndex == 1){return "ENERGY";}
    else if(resIndex == 2){return "GLASS";}
    else if(resIndex == 3){return "HEAT";}
    else if(resIndex == 4){return "WIFI";}
    else{return "INVALID";}
}

void DataBase::trade(int startPlayerIndex, int receivePlayerIndex, int giveRes, int receiveRes){
    if(!this->players[startPlayerIndex]->canTradeRes(giveRes)){
        cout << "You don't have enough resource of this type (at least 1)." << endl;
        return;
    }
    else if(!this->players[receivePlayerIndex]->canTradeRes(receiveRes)){
        cout << "You cannot trade for this resource, since the target don't have enough of them (at least 1)." << endl;
        return;
    }
    cout << this->players[startPlayerIndex]->getColor() << " offers " << this->players[receivePlayerIndex]->getColor()
        << " one " <<this->transformRes(giveRes) << " for one " << this->transformRes(receiveRes) << endl;
    cout << "Does " << this->players[receivePlayerIndex]->getColor() << " accept this offer?" << endl;
    string answer;
    cin >> answer;
    while(!cin.eof() && ((answer != "yes") && (answer != "no"))){
        cout << "Please input yes/no." << endl;
        cin >> answer;
    }
    if(answer == "yes"){
        this->players[startPlayerIndex]->tradeRes(giveRes,receiveRes);
        this->players[receivePlayerIndex]->tradeRes(receiveRes,giveRes);
        cout << "Trade successful!" << endl;
    }
    else if(answer == "no"){
        cout << "Builder " << this->players[receivePlayerIndex]->getColor() << " decline the trade." << endl;}
}

void DataBase::freeTrade(int startPlayerIndex, int receivePlayerIndex, int giveRes, int receiveRes, int giveResNum, int receiveResNum){
    if(!this->players[startPlayerIndex]->canTradeMultiRes(giveRes,giveResNum)){
        cout << "You don't have enough resource of this type." << endl;
        return;
    }
    else if(!this->players[receivePlayerIndex]->canTradeMultiRes(receiveRes,receiveResNum)){
        cout << "You cannot trade for this resource, since the target don't have enough of them." << endl;
        return;
    }
    cout << this->players[startPlayerIndex]->getColor() << " offers " << this->players[receivePlayerIndex]->getColor()
        << " " << giveResNum << " " <<this->transformRes(giveRes) << " for " << receiveResNum << " " << this->transformRes(receiveRes) << endl;
    cout << "Does " << this->players[receivePlayerIndex]->getColor() << " accept this offer?" << endl;
    string answer;
    cin >> answer;
    while(!cin.eof() && ((answer != "yes") && (answer != "no"))){
        cout << "Please input yes/no." << endl;
        cin >> answer;
    }
    if(answer == "yes"){
        this->players[startPlayerIndex]->tradeMultiRes(giveRes,receiveRes,giveResNum,receiveResNum);
        this->players[receivePlayerIndex]->tradeMultiRes(receiveRes,giveRes,receiveResNum,giveResNum);
        cout << "Trade successful!" << endl;
    }
    else if(answer == "no"){
        cout << "Builder " << this->players[receivePlayerIndex]->getColor() << " decline the trade." << endl;}
}

int DataBase::transformPlayer(string player){
    if(player == "BLUE"){return 0;}
    else if(player == "RED"){return 1;}
    else if(player == "ORANGE"){return 2;}
    else if(player == "YELLOW"){return 3;}
    return -1;
}

int DataBase::transformRes(string res){
    if(res == "BRICK"){return 0;}
    else if(res == "ENERGY"){return 1;}
    else if(res == "GLASS"){return 2;}
    else if(res == "HEAT"){return 3;}
    else if(res == "WIFI"){return 4;}
    return -1;
}

string DataBase::transformResInt(int res){
    if(res == 0){return "BRICK";}
    else if(res == 1){return "ENERGY";}
    else if(res == 2){return "GLASS";}
    else if(res == 3){return "HEAT";}
    else if(res == 4){return "WIFI";}
    return "";
}

ostream& DataBase::savePlayerData(ostream& out, int playerIndex) {
    this->players[playerIndex]->getResources(out);
    out << "r ";
    for(int i = 0;i<NUM_ROADS;i++){
        if(this->roads[i]->getOwner() == playerIndex){
            out << this->roads[i]->getIndex() << " ";}
    }
    out << "h";
    for(int i = 0;i<NUM_RESIDENCE;i++){
        if(this->residences[i]->getOwner() == playerIndex && this->residences[i]->getUpgradeLevel() == "B"){
            out << " " << this->residences[i]->getIndex() << " B";}
        else if(this->residences[i]->getOwner() == playerIndex && this->residences[i]->getUpgradeLevel() == "H"){
            out << " " << this->residences[i]->getIndex() << " H";}
        else if(this->residences[i]->getOwner() == playerIndex && this->residences[i]->getUpgradeLevel() == "T"){
            out << " " << this->residences[i]->getIndex() << " T";}
    }
    out << endl;
    return out;
}

ostream& DataBase::saveBoard(ostream& out){
    for(int i = 0;i<NUM_TILES;i++){
        out << this->tiles[i]->getResType() << " ";
        out << this->tiles[i]->getnumRes();
        if(i != NUM_TILES-1){out << " ";}
    }
    out << endl;
    return out;
}

int DataBase::saveGeeseRes(){
    for(int i = 0;i<NUM_TILES;i++){
        if(this->tiles[i]->isHasGeese() == true){return this->tiles[i]->getnumRes();}
    }
    return -1;
}

void DataBase::loadPlayerData(string data, int playerIndex){
    istringstream iss{data};
    int brick, energy, glass, heat, wifi;
    iss >> brick >> energy >> glass >> heat >> wifi;
    this->players[playerIndex]->setResources(brick, 0);
    this->players[playerIndex]->setResources(energy, 1);
    this->players[playerIndex]->setResources(glass, 2);
    this->players[playerIndex]->setResources(heat, 3);
    this->players[playerIndex]->setResources(wifi, 4);
    int index; // road/residence index
    string type; // residence type
    iss >> type;
    // load roads
    while(iss >> index){this->roads[index]->setOwner(playerIndex);}
    iss.clear();
    iss >> type;
    // load residences
    while(iss >> index >> type){
        if(type == "B"){this->residences[index]->setOwner(playerIndex);}
        else if(type == "H"){
            this->residences[index]->setOwner(playerIndex);
            this->residences[index]->upgrade();
        }
        else if(type == "T"){
            this->residences[index]->setOwner(playerIndex);
            this->residences[index]->upgrade();
            this->residences[index]->upgrade();
        }
    }
}

void DataBase::loadBoardData(string data, int geeseIndex){
    istringstream iss{data};
    int type, num;
    for(int i = 0; i<NUM_TILES; i++){
        iss >> type >> num;
        this->tiles[i]->setTypeNum(type, num);
        if(geeseIndex != -1){
            if(i == geeseIndex){this->tiles[i]->setGeese(true);}
            else if(i != geeseIndex){this->tiles[i]->setGeese(false);}
        }
        else if(geeseIndex == -1){
            if(type == 5){this->tiles[i]->setGeese(true);}
            else if(type != 5){this->tiles[i]->setGeese(false);}
        }
    }
}

void DataBase::setRandomSeed(int seed){
    randomGenerator = make_shared<Random>(seed);
}

bool DataBase::canTransNumber(string str){
    for (int i = 0; i < (int)str.length(); i++) {
      if(!isdigit(str[i])){return false;}
   }
   return true;
}

void DataBase::baseRes(int type){
    int addAmount = 0;
    if(type == 0){addAmount = 0;}
    else if(type == 1){addAmount = 2;}
    else if(type == 2){addAmount = 5;}
    else if(type == 3){addAmount = 10;}
    for(int i = 0;i<NUM_PLAYER;i++){
        this->players[i]->addAllRes(addAmount);
    }
}

int DataBase::getGeesePos(){
    for(int i = 0;i<NUM_TILES;i++){
        if(this->tiles[i]->isHasGeese()){return i;}
    }
    return -1;
}

void DataBase::getAPet(int playerindex){
    if(!this->players[playerindex]->canAddPet()){
        cout << "You do not have enough resources." << endl;
    }
    else{
        this->players[playerindex]->addPet();
        cout << "You successfully added a pet." << endl;
    }
}

void DataBase::checkPetPoints(){
    int petNums[4];
    int max = 4;
    int maxnum = 0;
    int maxindex = -1;
    for(int i=0; i<4; i++){
        petNums[i] = this->players[i]->getPetsNum();
        if(max < petNums[i]){
            max = petNums[i];
            maxindex = i;
            maxnum = 1;
        }
        else if(max == petNums[i]){
            maxindex = i;
            maxnum += 1;
        }
    }
    if(maxnum == 1){
        for(int i=0; i<4; i++){
            if(i == maxindex){this->players[i]->setMostPets(true);}
            else{this->players[i]->setMostPets(false);}
        }
        string platercolor = this->players[maxindex]->getColor();
        cout << platercolor << " has the most pets now." << endl;
    }
}
