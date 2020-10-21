#ifndef POSITION_HPP
#define POSITION_HPP
#include <vector>
#include <string>
#include "Ship.hpp"
#include "AttackResult.hpp"



using namespace std;

class Position {
   private:
      Ship* ship;
      bool attacked;
      bool recent;

   public:
      Position();
      ~Position();

      bool HasShip(); //{return this->hasShip;}
      Ship* GetShip(); //{return *(this->ship);}
      void SetShip(Ship *ship); //{this->ship = ship;}
      bool HasBeenAttacked(); //{return this->attacked;}
      bool HasBeenAttackedRecently(); //{return this->recent;}

      AttackResult GetAttacked();
      string PositionString(bool showShip);
    
};

#endif