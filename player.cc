#include "player.h"
void Player::addRes(int type, int num){
    if(type == 0){numBrick += num;}
    else if(type == 1){numEnergy += num;}
    else if(type == 2){numGlass += num;}
    else if(type == 3){numHeat += num;}
    else if(type == 4){numWifi += num;}
    else{return;}
}

bool Player::canTradeRes(int resType){
    if(resType == 0){return (numBrick >= 1);}
    else if(resType == 1){return (numEnergy >= 1);}
    else if(resType == 2){return (numGlass >= 1);}
    else if(resType == 3){return (numHeat >= 1);}
    else if(resType == 4){return (numWifi >= 1);}
    else{return false;}
}

bool Player::canTradeMultiRes(int resType, int resNum){
    if(resType == 0){return (numBrick >= resNum);}
    else if(resType == 1){return (numEnergy >= resNum);}
    else if(resType == 2){return (numGlass >= resNum);}
    else if(resType == 3){return (numHeat >= resNum);}
    else if(resType == 4){return (numWifi >= resNum);}
    else{return false;}
}

void Player::tradeRes(int giveResType, int receiveResType){
    if(receiveResType == 0){numBrick += 1;}
    else if(receiveResType == 1){numEnergy += 1;}
    else if(receiveResType == 2){numGlass += 1;}
    else if(receiveResType == 3){numHeat += 1;}
    else if(receiveResType == 4){numWifi += 1;}
    else{return;}

    if(giveResType == 0){numBrick -= 1;}
    else if(giveResType == 1){numEnergy -= 1;}
    else if(giveResType == 2){numGlass -= 1;}
    else if(giveResType == 3){numHeat -= 1;}
    else if(giveResType == 4){numWifi -= 1;}
    else{return;}
}

void Player::tradeMultiRes(int giveResType, int receiveResType, int giveResNum, int receiveResNum){
    if(receiveResType == 0){numBrick += receiveResNum;}
    else if(receiveResType == 1){numEnergy += receiveResNum;}
    else if(receiveResType == 2){numGlass += receiveResNum;}
    else if(receiveResType == 3){numHeat += receiveResNum;}
    else if(receiveResType == 4){numWifi += receiveResNum;}
    else{return;}

    if(giveResType == 0){numBrick -= giveResNum;}
    else if(giveResType == 1){numEnergy -= giveResNum;}
    else if(giveResType == 2){numGlass -= giveResNum;}
    else if(giveResType == 3){numHeat -= giveResNum;}
    else if(giveResType == 4){numWifi -= giveResNum;}
    else{return;}
}

int Player::loseRes(shared_ptr<Random> randomGenerator){
    while(true){
        int type = randomGenerator->generateTypeVI();
        if(type == 0 && numBrick > 0){
            numBrick -= 1;
            return 0;
        }
        else if(type == 1 && numEnergy > 0){
            numEnergy -= 1;
            return 1;
        }
        else if(type == 2 && numGlass > 0){
            numGlass -= 1;
            return 2;
        }
        else if(type == 3 && numHeat > 0){
            numHeat -= 1;
            return 3;
        }
        else if(type == 4 && numWifi > 0){
            numWifi -= 1;
            return 4;
        }
    }
}

bool Player::hasRes(){
    return((numBrick+numEnergy+numGlass+numHeat+numWifi) > 0);
}

int Player::rollADice(int seed){
    if(this->diceType == 0){
        return seed;
    }
    else{
        cout << "Input a roll between 2 and 12;" << endl;
        cout << "Your Input:";
        int input = 0;
        cin >> input;
        while((input < 2) || (input > 12)){
            cout << "Invalid Roll." << endl;
            cout << "Input a roll between 2 and 12;" << endl;
            cout << "Your Input:";
            cin >> input;
        }
        return input;
    }
}

bool Player::canLosetoGeese(){
    if(numBrick+numEnergy+numGlass+numHeat+numWifi >= 10){return true;}
    return false;
}
void Player::loseRestoGeese(shared_ptr<Random> randomGenerator){
    const int totalLose = (numBrick+numEnergy+numGlass+numHeat+numWifi) / 2;
    cout << "Builder " << this->getColor() << " lose " << totalLose << " resources to the geese. They lose:" << endl;
    int loseBrick = 0;
    int loseEnergy = 0;
    int loseGlass = 0;
    int loseHeat = 0;
    int loseWifi = 0;
    std::vector<int> v = randomGenerator->generateTypeV(numBrick+numEnergy+numGlass+numHeat+numWifi);
    for(int i = 0;i < totalLose;i++){
        int loseType = v.at(i);
        if(loseType >= 0 && loseType < numBrick){loseBrick += 1;}
        else if(loseType >= numBrick && loseType < numBrick + numEnergy){loseEnergy += 1;}
        else if(loseType >= numBrick + numEnergy && loseType < numBrick + numEnergy + numGlass){loseGlass += 1;}
        else if(loseType >= numBrick + numEnergy + numGlass && loseType < numBrick + numEnergy + numGlass + numHeat){loseHeat += 1;}
        else{loseWifi += 1;}
    }
    if(loseBrick > 0){
        cout << loseBrick << " BRICK." << endl;
        numBrick -= loseBrick;
    }
    if(loseEnergy > 0){
        cout << loseEnergy << " ENERGY." << endl;
        numEnergy -= loseEnergy;
    }
    if(loseGlass > 0){
        cout << loseGlass << " Glass." << endl;
        numGlass -= loseGlass;
    }
    if(loseHeat > 0){
        cout << loseHeat << " HEAT." << endl;
        numHeat -= loseHeat;
    }
    if(loseWifi > 0){
        cout << loseWifi << " WIFI." << endl;
        numWifi -= loseWifi;
    }
}

string Player::getColor(){return this->color;}
void Player::setDiceType(int diceType){this->diceType = diceType;}
void Player::playerResPrint(){
    cout << "Builder " << this->color << " has:" << endl;
    cout << numBrick << " BRICK" << endl;
    cout << numEnergy << " ENERGY" << endl;
    cout << numGlass << " GLASS" << endl;
    cout << numHeat << " HEAT" << endl;
    cout << numWifi << " WIFI" << endl;
    cout << builderPoint << " BUILDERPOINTS" << endl;
}

bool Player::canUpgradeT2(){
    if(this->numGlass >= 2 && this->numHeat >= 3){return true;}
    return false;
}
void Player::upgradeT2(){
    this->numGlass -= 2;
    this->numHeat -= 3;
    this->builderPoint += 1;
}

bool Player::canUpgradeT3(){
    if(this->numBrick >= 3 && this->numWifi >= 1 && this->numEnergy >= 2 
        && this->numGlass >= 2 && this->numHeat >= 2){return true;}
    return false;
}

void Player::upgradeT3(){
    this->numBrick -= 3;
    this->numEnergy -= 2;
    this->numGlass -= 2;
    this->numWifi -= 1;
    this->numHeat -= 2;
    this->builderPoint += 1;
}

bool Player::canBuildRoad(){
    if(this->numHeat >= 1 && this->numWifi >= 1){return true;}
    return false;
}
void Player::buildRoad(){
    this->numHeat -= 1;
    this->numWifi -= 1;
}

bool Player::canBuildRes(){
    if(this->numBrick >= 1 && this->numWifi >= 1 && this->numEnergy >= 1 && this->numGlass >= 1){return true;}
    return false;
}
void Player::buildRes(){
    this->numBrick -= 1;
    this->numEnergy -= 1;
    this->numGlass -= 1;
    this->numWifi -= 1;
    this->builderPoint += 1;
}
bool Player::isWinner(){
    int totalpoints = this->builderPoint;
    if(maxpets == true){totalpoints += 2;}
    if(totalpoints >= 10){return true;}
    return false;
}

void Player::setSeed(long unsigned int randomSeed){this->randomSeed = randomSeed;}
int Player::findMin(int i1, int i2){
    if(i1 >= i2){return i2;}
    return i1;
}
bool Player::withIn(int i, std::vector<int> v, int length){
    for(int index = 0; index < length; index++){
        if(v.at(index) == i){return true;}
    }
    return false;
}

ostream& Player::getResources(ostream& out) {
    out << this->numBrick << " ";
    out << this->numEnergy << " ";
    out << this->numGlass << " ";
    out << this->numHeat << " ";
    out << this->numWifi << " ";
    return out;
}

void Player::setResources(int Resnum, int type) {
    if(type == 0){numBrick = Resnum;}
    else if(type == 1){numEnergy = Resnum;}
    else if(type == 2){numGlass = Resnum;}
    else if(type == 3){numHeat = Resnum;}
    else if(type == 4){numWifi = Resnum;}
}

void Player::addAllRes(int resNum){
    numBrick += resNum;
    numEnergy += resNum;
    numGlass += resNum;
    numHeat += resNum;
    numWifi += resNum;
}

void Player::addPet(){
    numEnergy -= 3;
    numWifi -= 2;
    numBrick -= 1;
    pets++;
}

bool Player::canAddPet(){
    if(numEnergy >= 3 && numWifi >= 2 && numBrick >= 1){return true;}
    else{return false;}
}

int Player::getPetsNum(){return pets;}

void Player::setMostPets(bool setval){maxpets = setval;}
