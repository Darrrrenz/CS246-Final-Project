#include "residence.h"
int Residence::getIndex(){return index;}
int Residence::getOwner(){return owner;}
bool Residence::isHasOwner(){return hasOwner;}
int Residence::getRoad(int pos){return relatedRoads[pos];}
/*the road is arrange like:
                   <ROAD 0>
          <ROAD 1>   <RES>  <ROAD 2>
                   <ROAD 3>
if no road exist in that direction, then the number is -1
*/
int Residence::getTile(int pos){return belongToTiles[pos];}
//the arrangement of the tiles do not matter
//if less than 3 tiles, then assigned -1
string Residence::printIndex(){
    if(this->index < 10){return " " + to_string(index);}
    else{return to_string(index);}
}
string Residence::getUpgradeLevel(){
    if(this->upgradeLevel == 0){return "B";}
    else if(this->upgradeLevel == 1){return "H";}
    else if(this->upgradeLevel == 2){return "T";}
    else{return " ";}
}
string Residence::getFullUpgradeLevel(){
    if(this->upgradeLevel == 0){return "Basement";}
    else if(this->upgradeLevel == 1){return "House";}
    else if(this->upgradeLevel == 2){return "Tower";}
    else{return " ";}
}
void Residence::setOwner(int index){
    this->owner = index;
    this->hasOwner = true;
}

int Residence::getLevel(){return this->upgradeLevel;}
void Residence::upgrade(){this->upgradeLevel += 1;}
