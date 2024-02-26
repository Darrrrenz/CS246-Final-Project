#include "road.h"
using namespace std;
int Road::getEndOne(){return endOne;}
int Road::getEndTwo(){return endTwo;}
bool Road::isHasOwner(){return hasOwner;}
int Road::getIndex(){return index;}
int Road::getOwner(){return owner;}
Road::~Road(){}
string Road::printIndex(){
    if(index < 10){return " "+ to_string(index);}
    else{return to_string(index);}
}
void Road::setOwner(int index){
    this->owner = index;
    this->hasOwner = true;
}
