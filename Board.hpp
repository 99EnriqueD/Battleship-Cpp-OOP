
#ifndef BOARD_HPP
#define BOARD_HPP
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "Game.hpp"
#include "Position.hpp"
#include "Ship.hpp"
#include "AttackResult.hpp"

using namespace std;

class Board {
    private:
        vector<Position*> positions;
        string playerName;
        int shipsLeft;

    public:
         Board(string playerName, int size);
        ~Board() ;

        Position* GetPosition(int index); //{return *(this->positions[index]);}
        int GetShipsLeft(); // {return this->ships;};
        string GetPlayerName(); //{return this->playerName;}

        AttackResult GetAttacked(int postionIndex);
        void PrintBoard(int size, bool showShips, map<int,string> preMadeStrings);
        void PlaceShip(vector<int> positionIndices, int shipSize);
};

#endif


