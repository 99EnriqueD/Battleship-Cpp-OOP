
#ifndef SHIP_HPP
#define SHIP_HPP
#include <iostream>
#include <vector>
#include <string>
#include "AttackResult.hpp"


using namespace std;

// Ship that can be placed on positions on a game board
class Ship {
    private:
        int size, hp;

    public:
        int GetSize();
        int GetHP();
        AttackResult GetHit();

        // Returns 'true
        bool IsSunk();

        Ship(int size);
        ~Ship();

};

#endif