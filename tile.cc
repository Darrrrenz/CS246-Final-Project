#include "tile.h"
using namespace std;
int Tile::getGeeseRes(){return this->geeseRes;}
int Tile::getIndex(){return this->index;}
int Tile::getnumRes(){return this->numRes;}
int Tile::getResidences(int pos){return (this->residences)[pos];}
/*  distribution of the residence and roads for a tile   
    <RES 0>         <ROAD 0>        <RES 1>
    <ROAD 1>                        <ROAD 2>
    <RES 2>                         <RES 3>
    <ROAD 3>                        <ROAD 4>
    <RES 4>         <ROAD 5>        <RES 5>*/
int Tile::getRoad(int pos){return (this->roads)[pos];}
bool Tile::isHasGeese(){return this->hasGeese;}
string Tile::getTypeRes(){
    if(this->typeRes == 0){return "  BRICK  ";}
    else if(this->typeRes == 1){return "  ENERGY ";}
    else if(this->typeRes == 2){return "  GLASS  ";}
    else if(this->typeRes == 3){return "  HEAT   ";}
    else if(this->typeRes == 4){return "  WIFI   ";}
    else if(this->typeRes == 5){return "  PARK   ";}
    else{return " INVALID ";}
}

string Tile::normalGetTypeRes(){
    if(this->typeRes == 0){return "BRICK";}
    else if(this->typeRes == 1){return "ENERGY";}
    else if(this->typeRes == 2){return "GLASS";}
    else if(this->typeRes == 3){return "HEAT";}
    else if(this->typeRes == 4){return "WIFI";}
    else if(this->typeRes == 5){return "PARK";}
    else{return " INVALID ";}
}

int Tile::getResType(){return this->typeRes;}
void Tile::setGeese(bool trigger){this->hasGeese = trigger;}

void Tile::setTypeNum(int newType, int newNum){
    this->typeRes = newType;
    this->numRes = newNum;
}
