/*
C++ Battleship Game
Version: 1.0
Author: Enrique Dehaerne
*/
#include <iostream>
#include <vector>
#include <string>
#include<dos.h>
#include <conio.h>
#include <chrono>
#include <thread>
#include <map>
#include <math.h>
#include "Game.hpp"
#include "Board.hpp"
#include "Position.hpp"
#include "Ship.hpp"


#ifdef __unix__  
#include <unistd.h>

#elif _WIN32
#include <synchapi.h>

#endif

using namespace std;

// Early declaration of some helper functions
string getHitString();
string getMissString();
string getSunkString();
string getWonString();
int getAttackPositionFromPlayer(int boardSize);
void clear();
void pause();

/*******************************************************************
                SHIP CLASS
********************************************************************/

// A ship that is placed on board positions.
Ship::Ship(int size){
    this->size = size;
    this->hp = size;
};
Ship::~Ship() {};

bool Ship::IsSunk(){return this->hp == 0;}

// Get hit by an attack. Lowers the ship's HP and returns an Attack result.
AttackResult Ship::GetHit() {
    this->hp --;
    if (IsSunk()) {
        return sunk;
    } else {
        return hit;
    }
}

/*******************************************************************
                POSITION CLASS
********************************************************************/

// A position on a board. May have a ship placed on it.
Position::Position() {
   this->attacked=false;
   this->recent=false;
   this->ship=NULL;
};
Position::~Position() {};

bool Position::HasShip(){return this->ship != NULL;}
void Position::SetShip(Ship* ship){this->ship = ship;};
bool Position::HasBeenAttacked(){return this->attacked;}
bool Position::HasBeenAttackedRecently(){return this->recent;}

// Prints a string representing the state of this position.
// Modifies the 'recent' attribute of the position when a full turn has passed.
string Position::PositionString(bool showShip) {
    if (HasShip()) {
        string posLine = "| ";
        if (showShip) {
            posLine += "{";
        } else {
            posLine +=" ";
        }
        if (HasBeenAttacked()) {
            if (HasBeenAttackedRecently()) {
                posLine += "#";
                recent = showShip;
            } else {
                posLine += "X";
            }
        } else {
            posLine += " ";
        }
        if (showShip) {
            posLine += "} ";
        } else {
            posLine +="  ";
        }
        return posLine;
    } else {
        string posLine = "| ";
        posLine += " ";
        if (HasBeenAttacked()) {
            if (HasBeenAttackedRecently()) {
                posLine += "@";
                recent = showShip;
            } else {
                posLine += "O";
            }
        } else {
            posLine += " ";
        }
        posLine +=  "  ";
        return posLine;
    }
}

// Get attacked. Marks the position as attacked recently.
AttackResult Position::GetAttacked() {
    if (HasBeenAttacked()) {
        throw "You have already attacked this position! Please give another position to attack.";
    } else if (HasShip()) {
        attacked = true;
        recent = true;
        return ship->GetHit();
    } else {
        attacked = true;
        recent = true;
        return miss;
    }
}


/*******************************************************************
                BOARD CLASS
********************************************************************/

// A board that belongs to a player of a battleship game.
// A board has an array of positions of size
Board::Board(string playerName, int size){
    this->playerName = playerName;
    this->positions = {};
    for (int i=0; i<size*size;i++) {
        this->positions.push_back(new Position());
    };
    this->shipsLeft=0;
};
Board::~Board(){};

Position* Board::GetPosition(int index) {
    return (this->positions[index]);}
int Board::GetShipsLeft(){return this->shipsLeft;};
string Board::GetPlayerName(){return this->playerName;};

// Prints a board of a given size using pre made strings. 
// Will print ships or not depending on the given `showShips` argument.
void Board::PrintBoard(int size, bool showShips, map<int,string> preMadeStrings) {
    string board = preMadeStrings[2] + preMadeStrings[1] + "0 ";
    for (int i=0;i<size*size;i++) {
        if (i % size == 0 && i != 0) {
            board += "|\n" + preMadeStrings[4] +  to_string((int) floor(i/size)) + " ";
        };
        board += GetPosition(i)->PositionString(showShips);
    };

    board += "|\n";
    board += preMadeStrings[3];
    cout << board;
}

// Place a ship on the board on the given position indices.
void Board::PlaceShip(vector<int> positionIndices, int shipSize) {
    Ship* newShip = new Ship(shipSize);
    this->shipsLeft ++;
    for (int posIn: positionIndices) {
        GetPosition(posIn)->SetShip(newShip);
    }
}

// Get attacked on a certain position with given posIndex.
AttackResult Board::GetAttacked(int posIndex) {
    AttackResult result =  GetPosition(posIndex)->GetAttacked();
    if (result == sunk) {
        this->shipsLeft --;
        if (shipsLeft == 0) {
            return won;
        }
    }
    return result;
}


/*******************************************************************
                GAME CLASS
********************************************************************/

// A battleship game. Should be either a 'ClassicGame' or 'SalvoGame' derived class.
// This class has methods and attributes inherited by those derived classes.
Game::Game(int boardSize) {
    this->boardSize = boardSize;
    this->boardPlayerOne = NULL;
    this->boardPlayerTwo = NULL;
    this->finished = false;
}
Game::~Game() {}

void Game::SetBoardPlayerOne(Board* boardPlayerOne){this->boardPlayerOne = boardPlayerOne;}
void Game::SetBoardPlayerTwo(Board* boardPlayerTwo){this->boardPlayerTwo = boardPlayerTwo;}
vector<AttackResult> Game::GetTurnResult() {return turnResult;}
void Game::AddTurnResult(AttackResult attackResult){this->turnResult.push_back (attackResult);}
bool Game::HasFinished(){return finished;}

void Game::PrintAttackResult(AttackResult attackResult) {
    switch (attackResult)
    {
    case 0:
        cout << getMissString() << endl;
        break;
    case 1:
        cout << getHitString() << endl;
        break;
    case 2:
        cout << getSunkString() << endl;
        break;
    case 3:
        finished=true;
        cout << getWonString() << endl;
        break;
    default:
        throw "Could not identify attack result...";
        break;
    }
}

void Game::AttackHelper(Board*ownBoard, Board* enemyBoard) {
     int coordinates = getAttackPositionFromPlayer(boardSize);
    try {
        this->AddTurnResult(enemyBoard->GetAttacked(coordinates));
    } catch( const char* e) {
        cerr << e;
        this->AttackHelper(ownBoard,enemyBoard);
    }
}

// Prints the result of the last turn completed.
void Game::DisplayTurnResult(Board* ownBoard, Board* enemyBoard) {
    clear();
    cout  << ownBoard->GetPlayerName() << "'s turn result(s): \n\n";
    for(AttackResult res:turnResult) {
        PrintAttackResult(res);
    }
    this->turnResult.clear();
    if (!finished) {
        cout << enemyBoard->GetPlayerName() << " is up next.\n";
        pause();
    }
    
}

SalvoGame::SalvoGame(int boardSize) : Game(boardSize) {};
SalvoGame::~SalvoGame() {};

// Prompts the player for coordinates to attack a position on the enemy's board.
// For a salvo game, the player can attack as many positions as the player has ships that have not been sunk.
// Modifies the position attacked as well as the ship on the position if there is one.
void SalvoGame::Attack(Board* ownBoard, Board* enemyBoard) {
    cout << ownBoard->GetPlayerName() << ", your turn to attack " << enemyBoard->GetPlayerName() <<"!\n";
    cout << "You have " << ownBoard->GetShipsLeft() << " ships left so you can attack the same amount of coordinates.\n";
    for (int i=0; i<ownBoard->GetShipsLeft(); i++) {
        AttackHelper(ownBoard,enemyBoard);
    }
};

ClassicGame::ClassicGame(int boardSize) : Game(boardSize) {};
ClassicGame::~ClassicGame(){};

// Prompts the player for coordinates to attack a position on the enemy's board.
// Modifies the position attacked as well as the ship on the position if there is one.
void ClassicGame::Attack(Board* ownBoard, Board* enemyBoard) {
    cout << ownBoard->GetPlayerName() << ", your turn to attack " << enemyBoard->GetPlayerName() <<"!";
    AttackHelper(ownBoard, enemyBoard);
};


/*******************************************************************
                HELPER FUNCTIONS
********************************************************************/

// Pauses program execution until a key is pressed by the user.
// This function will print "Please enter any key to continue...".
void pause() {
    #ifdef __unix__
        system("read");
    #elif _WIN32
        system("pause");
    #endif
}

// Clears the terminal
void clear()
{
#if defined _WIN32
    system("cls");
#elif __unix__
    system("clear");
#endif
}

string getTitleString() {
    string title;                                                                                                                                                                                                                                                                                                                                    
    title  = " ____        _   _   _           _     _       \n";
    title += "|  _ \\      | | | | | |         | |   (_)      \n";
    title += "| |_) | __ _| |_| |_| | ___  ___| |__  _ _ __  \n";
    title += "|  _ < / _` | __| __| |/ _ \\/ __| '_ \\| | '_ \\ \n";
    title += "| |_) | (_| | |_| |_| |  __/\\__ \\ | | | | |_) |\n";
    title += "|____/ \\__,_|\\__|\\__|_|\\___||___/_| |_|_| .__/ \n";
    title += "                                        | |    \n";
    title += "                                        |_|    \n\n";
    return title;          
}

string getHitString() {
    string hit;
    hit =  "  _    _ _ _   \n";
    hit += " | |  | (_) |  \n";
    hit += " | |__| |_| |_ \n";
    hit += " |  __  | | __|\n";
    hit += " | |  | | | |_ \n";
    hit += " |_|  |_|_|\\__|\n";
    return hit;
}

string getMissString() {
    string miss;
    miss =  "  __  __ _         \n";
    miss += " |  \\/  (_)        \n";
    miss += " | \\  / |_ ___ ___ \n";
    miss += " | |\\/| | / __/ __|\n";
    miss += " | |  | | \\__ \\__ \\\n";
    miss += " |_|  |_|_|___/___/\n";
    return miss;
}

string getSunkString() {
    string sunk;
    sunk =  "   _____             _    \n";
    sunk += "  / ____|           | |   \n";
    sunk += " | (___  _   _ _ __ | | __\n";
    sunk += "  \\___ \\| | | | '_ \\| |/ /\n";
    sunk += "  ____) | |_| | | | |   < \n";
    sunk += " |_____/ \\__,_|_| |_|_|\\_\\\n";
    return sunk;
}

string getWonString() {
    string won;
    won =  " __          __         \n";
    won += " \\ \\        / /         \n";
    won += "  \\ \\  /\\  / /__  _ __  \n";
    won += "   \\ \\/  \\/ / _ \\| '_ \\ \n";
    won += "    \\  /\\  / (_) | | | |\n";
    won += "     \\/  \\/ \\___/|_| |_|\n";
    return won;
}

string getTopLineString(int size) {
    string line = "Y ";
    for(int i=0; i<size; i++) {
        line += "------"; 
    }
    line += "-\n";
    return line;
}

string getXAxisString(int size) {
    string axis = "  X";
    for (int i=0; i<size; i++) {
        axis += "  ";
        axis += to_string(i);
        axis += "   ";
    };
    axis += "\n";
    return axis;
}

string getBottomLineString(int size) {
    string line = "  ";
    for(int i=0; i<size; i++) {
        line +="------";
    }
    line += "-\n";
    return line;
};

string getIntermediateLineString(int size) {
    string line = "  |";
    for(int i=0; i<size; i++) {
        line += "- - - ";
    }
    line += "\b|\n";
    return line;
};

// Prompts the user to pick between a 'classic' or a 'salvo' game mode.
// In the classic game mode, each user only attacks once during their turn.
// In the salvo game mode, each user can attack as many times as they have ships that have not been sunk.
int getGameFromPlayer() {
    //Get game type
    int gameType = -1;
    cout << "\nWhat type of game would you like to play (0: Classic game, 1: Salvo game)? ";
    
    while(!(cin >> gameType) || (gameType != 0 && gameType != 1)) {
    cout << "Incorrect input, please retry: ";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return gameType;
    
}

bool isLegalOrientationInput(int orientation) {
    return orientation != 0 || orientation != 1 || orientation != 2 || orientation != 3 || orientation != 4; 
}

// Checks to see if the positions intended for a ship fall within the game board.
bool isLegalInitPositionAndOrientation(int x, int y, int orientation, int shipSize, int boardSize) {
    if (orientation == 0) { // up
        return y >= shipSize-1;
    } else if (orientation ==1){ //down
        return y + shipSize <= boardSize;
    } else if (orientation ==2) { //left
        return x >= shipSize-1;
    } else { // right
        return x + shipSize <= boardSize;
    }   
}

// Calculates positions for a ship based on an intial position and an orientation.
vector<int> getShipPositions(int initIndex, int orientation, int shipSize, int boardSize, Board& board) {
    vector<int> positionIndices {initIndex};
    // Get positions based on initIndex and orientation
    if (orientation == 0) { // up
        for(int i=boardSize; i<shipSize*boardSize; i+=boardSize) {
            positionIndices.push_back(initIndex-i);
        }
    } else if (orientation ==1){ //down
        for(int i=boardSize; i<shipSize*boardSize; i+=boardSize) {
            positionIndices.push_back(initIndex+i);
        }
    } else if (orientation ==2) { //left
        for(int i=1; i<shipSize; i++) {
            positionIndices.push_back(initIndex-i);
        }
    } else { // right
        for(int i=1; i<shipSize; i++) {
            positionIndices.push_back(initIndex+i);
        }
    }
    // Make sure there are no ships in the positions calculated above.
    for (int posIndex: positionIndices) {
        if(board.GetPosition(posIndex)->HasShip()) {
            throw "There is already a ship in at least one of the positions that a new ship is attempting to be placed.\nPlease retry placing this ship...";
        }
    }
    return positionIndices;   
}

// Prompts the player for the positions that a ship should be placed.
// The positions are calculated from getting an initial position and an orientation that the ship grows from that position.
vector<int> getShipPositioningFromPlayer(int shipSize, int boardSize, Board& board) {
    int x = -1, y = -1, initIndex, orientation=-1;
    bool properInitCoordinates = false, properOrientation=false;
    vector<int> newShipPositionIndices;
    
    while(!properOrientation) {
        while(!properInitCoordinates) {
            cout << "\nOn which starting coordinates would you like to place a ship of size " << shipSize << "?";
            cout << "\nX: ";
            while(!(cin >> x) || (x <0 || x>boardSize-1)) {
            cout << "Incorrect input, please retry: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cout << "Y: ";
            while(!(cin >> y) || (y<0 || y>boardSize-1)) {
            cout << "Incorrect input, please retry: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            initIndex = x+y*boardSize;
            if (board.GetPosition(initIndex)->HasShip()) {
                cout << "This position already has a ship! Please place the ship in an empty position...";
            } else {
                properInitCoordinates = true;
            }
        }
        cout << "\nWhich way should this ship be placed from the given starting position (0:up, 1:down, 2:left, 3: right)?";
        cout << "\nEnter '4' if you want to choose another initial position";
        cout << "\nOrientation: ";
        while(!(cin >> orientation) || !isLegalOrientationInput(orientation)) {
        cout << "Incorrect input, please retry: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        if (orientation == 4) {
            cout << "Reseting initial position...";
            properInitCoordinates=false;
        } else if (isLegalInitPositionAndOrientation(x,y,orientation,shipSize,boardSize)) {
            try {
                newShipPositionIndices = getShipPositions(initIndex, orientation, shipSize, boardSize, board);
                properOrientation = true;
            } catch (const char* e) {
                cout << e;
            }
        } else {
            cout << "Illegal ship positioning, please try another orientation... ";
        }
    }
    return newShipPositionIndices;
}

// Prompts the player for the coordinates to attack.
int getAttackPositionFromPlayer(int boardSize) {
    int x=-1, y=-1;
    cout << "\nWhich coordinates would you like to attack?";
    cout << "\nX: ";
    while(!(cin >> x) || (x <0 || x>boardSize-1)) {
    cout << "Incorrect input, please retry: ";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "Y: ";
    while(!(cin >> y) || (y<0 || y>boardSize-1)) {
    cout << "Incorrect input, please retry: ";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return x+y*boardSize;
}

/*******************************************************************
                MAIN
********************************************************************/

int main() {

    /// Game parameters
    int gameBoardSize = 10;
    vector<int> shipSizes {5,4,3,3,2};

    int gameShipAmount = shipSizes.size();

    // vars used for printing game boards
    string topLineString = getTopLineString(gameBoardSize);
    string xAxistString = getXAxisString(gameBoardSize);
    string bottomLineString = getBottomLineString(gameBoardSize);
    string intermediateLineString = getIntermediateLineString(gameBoardSize);
    map<int, string> boardPrintStrings {
        {1, topLineString},
        {2, xAxistString},
        {3, bottomLineString},
        {4,intermediateLineString}
    };

    /// Init game.

    // Clear and color terminal.
    clear();
    system("Color 0A");
    
    cout << getTitleString();
    cout << "Welcome to battleship! Let's set up your game...\n\n";

    // Get player names.
    string playerOne, playerTwo;
    cout << "Player one's name: ";
    cin >> playerOne;
    cout << "Player two's name: ";
    cin >> playerTwo;

    // Choose game type.
    int gameType = getGameFromPlayer();
    Game* game;
    ClassicGame classicGame = ClassicGame(gameBoardSize);
    SalvoGame salvoGame = SalvoGame(gameBoardSize);
    if (gameType<0.5) {
        cout << "\nYou chose: Classic Game.\n\nNext we will set up your boards.\n";
            game = &classicGame;
    } else if (gameType>0.5) {
        cout << "\nYou chose: Salvo Game.\n\nNext we will set up your boards.\n";
            game = &salvoGame;
    }
    pause();

    /// Setup boards
   
    // Init boards.
    vector<Board*> boards = {new Board(playerOne, gameBoardSize), new Board(playerTwo, gameBoardSize)};
    // Iterate over every ship to allow the user to position a ship one at a time on their board.
    for (Board* board: boards) {
        for(int shipSize: shipSizes) {
        clear();
        cout << board->GetPlayerName() + ", please position your ships now: \n\n";
        board->PrintBoard(gameBoardSize, true, boardPrintStrings);
        vector<int> newShipPositionIndices = getShipPositioningFromPlayer(shipSize,gameBoardSize,*board);
        board->PlaceShip(newShipPositionIndices, shipSize);
        }
    }
    // Set the boards with ships
    game->SetBoardPlayerOne(boards[0]);
    game->SetBoardPlayerTwo(boards[1]);
    clear();
    cout << "\nBoth boards are now set up, " << boards[0]->GetPlayerName() << " will attack first." << endl;
    pause();


    /// Take turns attacking

    bool playerTwoTurn = false;
    while(!game->HasFinished()) {

        Board* ownBoard = boards[playerTwoTurn];
        Board* enemyBoard = boards[!playerTwoTurn];
        
        clear();
        enemyBoard->PrintBoard(gameBoardSize,false,boardPrintStrings);
        ownBoard->PrintBoard(gameBoardSize,true,boardPrintStrings);
        game->Attack(ownBoard,enemyBoard);
        game->DisplayTurnResult(ownBoard, enemyBoard);
        
        playerTwoTurn = !playerTwoTurn;
    }
    // Player has won.
    cout << "Congratulations " << boards[!playerTwoTurn]->GetPlayerName() << ", you won!" << endl;

    return 0;
};


