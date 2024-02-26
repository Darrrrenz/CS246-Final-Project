#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include "random.h"
#include "dataBase.h"
#include "road.h"
#include "tile.h"
#include "residence.h"
using namespace std;
bool startGameSetting();
void preTurnConfig();
bool gamePlay(bool seed, bool load, bool board, bool random, string seednum, string filename);
void playTurn();
int transformPlayer(string player);
int transformRes(string res);
void saveGame(string filename = "backup.sv");
bool loadGame(string filename);
bool loadBoard(string filename);
bool canTransNumber(string str);
void determineRes();
int turn = 0;
bool bonusOn = false;
unique_ptr<DataBase> base {nullptr};

int main(int argc, char *argv[]){
    bool seed = false, load = false, board = false;
    bool random = true;
    string seednum, filename;
    // check command-line arguments
    for(int i=1; i<argc; i++){
        if(string(argv[i]) == "-seed"){
            seed = true;
            i++;
            seednum = argv[i];}
        else if(string(argv[i]) == "-load"){
            load = true;
            i++;
            filename = argv[i];}
        else if(string(argv[i]) == "-board"){
            board = true;
            i++;
            filename = argv[i];}
        else if(string(argv[i]) == "-random-board"){random = true;}
        else if(string(argv[i]) == "-enablebonus"){bonusOn = true;}
    }
    // check how to generate board
    if(load == true && board == true){
        cerr << "You've entered contradictory commands." << endl;
        return -1;
    }
    else if(load == true || board == true){random = false;}
    while(true){
        bool startplay = gamePlay(seed, load, board, random, seednum, filename);
        if(cin.eof() || !startplay){break;}
        cout << "Do you want to play again?" << endl;
        string response;
        cin >> response;
        while(response != "yes" && response != "no"){cin >> response;}
        if(response == "yes"){continue;}
        else{break;}
    }
}

bool gamePlay(bool seed, bool load, bool board, bool random, string seednum, string filename){
    base = make_unique<DataBase>();
    turn = 0;
    bool start;
    // implement command-line arguments
    if(seed == true){
        int newseed;
        if(istringstream iss{seednum}; iss >> newseed){base->setRandomSeed(newseed);}
        else{cout << "You have entered an invalid seed." << endl;}
    }
    if(load == true){
        if(loadGame(filename)){base->printBoard();}
        else{return false;}
    }
    else if(board == true){
        if(loadBoard(filename)){
            if(bonusOn){determineRes();}
            if(cin.eof()){
                return false;
            }
            base->printBoard();
            start = startGameSetting();
        }
        else{return false;}
        
    }
    else if(random == true){
        //game resource amount determine
        if(bonusOn){determineRes();}
        if(cin.eof()){
            return false;
        }
        base->printBoard();
        start = startGameSetting();
    }
    //insert more functions here
    while(!cin.eof()){
        preTurnConfig();
        playTurn();
        if(base->findWinner()){break;}
        turn++;
    }
    if(!base->endWithWinner() && start == true){
        turn--;
        saveGame();
    }
    return true;
}

bool startGameSetting(){
    for(int i = 0;i<4;i++){
        cout << "Builder " << base->getPlayerColor(i) << " where do you want to build a basement?" << endl;
        cout << "YOUR CHOICE: ";
        string input;
        int index;
        cin >> input;
        if(cin.eof()){return false;}
        while(true){
            if(canTransNumber(input)){
                index = stoi(input);
                if(index < 0 || index >= 54){cout << "INVALID RESIDENCE NUMBER." << endl;}
                else if(base->setResOwner(index,i)){break;}
            }
            else{cout << "PLEASE INPUT AN INT." << endl;}
            cout << "YOUR CHOICE: ";
            if(cin.eof()){return false;}
            cin >> input;
        }
    }
    for(int i = 3;i >= 0;i--){
        cout << "Builder " << base->getPlayerColor(i) << " where do you want to build a basement?" << endl;
        cout << "YOUR CHOICE: ";
        string input;
        int index;
        cin >> input;
        if(cin.eof()){return false;}
        while(true){
            if(canTransNumber(input)){
                index = stoi(input);
                if(index < 0 || index >= 54){cout << "INVALID RESIDENCE NUMBER." << endl;}
                else if(base->setResOwner(index,i)){break;}
            }
            else{cout << "PLEASE INPUT AN INT." << endl;}
            cout << "YOUR CHOICE: ";
            if(cin.eof()){return false;}
            cin >> input;
        }
    }
    return true;
}

void preTurnConfig(){
    int playerIndex = turn % 4;
    cout << "Builder " << base->getPlayerColor(playerIndex) << "'s turn" << endl;
    string command;
    cin >> command;
    while(!cin.eof() && command != "roll"){
        if(command == "load"){base->setPlayerDiceType(playerIndex,1);}
        else if(command == "fair"){base->setPlayerDiceType(playerIndex,0);}
        else{cout << "Invalid command." << endl;}
        cin >> command;
    }
    if(cin.eof()){return;}
    int roll = base->playerRoll(playerIndex);
    cout << "Builder " << base->getPlayerColor(playerIndex) << " rolls " << roll << endl;
    
    base->distributeRes(roll,playerIndex);
}

void playTurn(){
    int playerIndex = turn % 4;
    string command;
    cin >> command;
    while(!cin.eof() && command != "next"){
        if(command == "board"){base->printBoard();}
        else if(bonusOn && command == "geese"){cout << "Geese is currently at tile " << base->getGeesePos() <<"." << endl;}
        else if(command == "status"){base->printPlayerStatus();}
        else if(command == "residences"){base->printPlayerResidence(playerIndex);}
        else if(command == "build-road"){
            string input;
            cin >> input;
            if(!canTransNumber(input)){
                cout << "Please use a valid index." << endl;
            }
            else{
                int roadIndex = stoi(input);
                base->buildRoad(playerIndex,roadIndex);
            }
        }
        else if(command == "build-res"){
            string input;
            cin >> input;
            if(!canTransNumber(input)){
                cout << "Please use a valid index." << endl;
            }
            else{
                int resIndex = stoi(input);
                base->buildRes(playerIndex,resIndex);
            }
            
        }
        else if(command == "improve"){
            string input;
            cin >> input;
            if(!canTransNumber(input)){
                cout << "Please use a valid index." << endl;
            }
            else{
                int resIndex = stoi(input);
                base->upgradeRes(playerIndex,resIndex);
            }
        }
        else if(command == "trade"){
            string color, give, receive;
            cin >> color >> give >> receive;
            int colorIndex = transformPlayer(color);
            int giveIndex = transformRes(give);
            int receiveIndex = transformRes(receive);
            if(colorIndex == -1){cout << "Please input valid color. (BLUE, RED, ORANGE, or YELLOW)" << endl;}
            else if(giveIndex == -1 || receiveIndex == -1){cout << "Please input valid resource. (BRICK, ENERGY, GLASS, HEAT, or WIFI)" << endl;}
            else if(playerIndex == colorIndex){cout << "You cannot trade with yourself." << endl;}
            else if(giveIndex == receiveIndex){cout << "You cannot trade the same type of resource" << endl;}
            else{base->trade(playerIndex,colorIndex,giveIndex,receiveIndex);}
        }
        else if(bonusOn && command == "free-trade"){
            string color,give,givenum,receive,receivenum;
            cin >> color >> give >> givenum >> receive >> receivenum;
            if(!canTransNumber(givenum) || !canTransNumber(receivenum)){
                cout << "Please input valid resource number." << endl;
            }
            else{
                int colorIndex = transformPlayer(color);
                int giveIndex = transformRes(give);
                int receiveIndex = transformRes(receive);
                if(colorIndex == -1){cout << "Please input valid color. (BLUE, RED, ORANGE, or YELLOW)" << endl;}
                else if(giveIndex == -1 || receiveIndex == -1){cout << "Please input valid resource. (BRICK, ENERGY, GLASS, HEAT, or WIFI)" << endl;}
                else if(playerIndex == colorIndex){cout << "You cannot trade with yourself." << endl;}
                else if(giveIndex == receiveIndex){cout << "You cannot trade the same type of resource" << endl;}
                else{base->freeTrade(playerIndex,colorIndex,giveIndex,receiveIndex,stoi(givenum),stoi(receivenum));}
            }
        }
        else if(bonusOn && command == "get-a-pet"){
            base->getAPet(playerIndex);
            base->checkPetPoints();
        }
        else if(command == "save"){
            string filename;
            cin >> filename;
            if(filename == "format.dat" || filename == "arrangement.dat"){
                cout << "Please enter another file name." << endl;
            }
            else{saveGame(filename);}
        }
        else if(bonusOn && command == "help"){
            cout << "Valid commands:" << endl;
            cout << "board" << endl;
            cout << "geese" << endl;
            cout << "status" << endl;
            cout << "residences" << endl;
            cout << "build-road <edge#>" << endl;
            cout << "build-res <housing#>" << endl;
            cout << "improve <housing#>" << endl;
            cout << "trade <colour> <give> <take>" << endl;
            cout << "free-trade <colour> <give> <give-num> <take> <take-num>" << endl;
            cout << "get-a-pet" << endl;
            cout << "next" << endl;
            cout << "save <file>" << endl;
            cout << "help" << endl;
        }
        else if(command == "help"){
            cout << "Valid commands:" << endl;
            cout << "board" << endl;
            cout << "status" << endl;
            cout << "residences" << endl;
            cout << "build-road <edge#>" << endl;
            cout << "build-res <housing#>" << endl;
            cout << "improve <housing#>" << endl;
            cout << "trade <colour> <give> <take>" << endl;
            cout << "next" << endl;
            cout << "save <file>" << endl;
            cout << "help" << endl;
        }
        else if(command != ""){
            cout << "invalid command, please use 'help' for information" << endl;
        }
        cin >> command;
    }
}

int transformPlayer(string player){
    if(player == "BLUE"){return 0;}
    else if(player == "RED"){return 1;}
    else if(player == "ORANGE"){return 2;}
    else if(player == "YELLOW"){return 3;}
    return -1;
}

int transformRes(string res){
    if(res == "BRICK"){return 0;}
    else if(res == "ENERGY"){return 1;}
    else if(res == "GLASS"){return 2;}
    else if(res == "HEAT"){return 3;}
    else if(res == "WIFI"){return 4;}
    return -1;
}

void saveGame(string filename){
    ofstream file{filename};
    if(!file){
        cout << "Unable to save in the file: " << filename << endl;
        return;
    }
    int currentplayer = turn % 4;
    file << currentplayer << endl;
    for(int i=0; i < 4; i++){
        base->savePlayerData(file, i);
    }
    base->saveBoard(file);
    file << base->saveGeeseRes() << endl;
    file.close();
    cout << "Successfully saved in file: " << filename << endl;
}

bool loadGame(string filename){
    ifstream file{filename};
    if(!file){
        cerr << "Unable to open the file: " << filename << endl;
        return false;
    }
    string currturn;
    getline(file, currturn);
    istringstream iss{currturn};
    iss >> turn;
    for(int i=0; i<4; i++){
        string playerdata;
        getline(file, playerdata);
        base->loadPlayerData(playerdata, i);
    }
    string boarddata;
    int geeseRes;
    getline(file, boarddata);
    file >> geeseRes;
    base->loadBoardData(boarddata, geeseRes);
    file.close();
    cout << "Successfully loaded the game in file: " << filename << endl;
    return true;
}

bool loadBoard(string filename){
    ifstream file{filename};
    if(!file){
        cerr << "Unable to open the file: " << filename << endl;
        return false;
    }
    string boarddata;
    getline(file, boarddata);
    base->loadBoardData(boarddata, -1);
    file.close();
    cout << "Successfully loaded the board in file: " << filename << endl;
    return true;
}

bool canTransNumber(string str){
    for (int i = 0; i < (int)str.length(); i++) {
      if(!isdigit(str[i])){return false;}
   }
   return true;
}

void determineRes(){
    cout << "How many resource do you want to have before the game?" << endl;
    cout << "Poor: no resource available." << endl;
    cout << "Medium: 2 resource of each type available" << endl;
    cout << "Rich: 5 resource of each type available" << endl;
    cout << "Beginner: 10 resource of each type available" << endl;
    cout << "Your choice:";
    string response;
    while(!cin.eof()){
        cin >> response;
        if(response == "Poor"){
            base->baseRes(0);
            break;
        }
        else if(response == "Medium"){
            base->baseRes(1);
            break;
        }
        else if(response == "Rich"){
            base->baseRes(2);
            break;
        }
        else if(response == "Beginner"){
            base->baseRes(3);
            break;
        }
        else{cout << "Please input a valid answer." << endl << "Your choice:";}
    }
}
