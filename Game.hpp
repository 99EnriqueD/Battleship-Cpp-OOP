#ifndef GAME_HPP
#define GAME_HPP
#include <iostream>
#include <vector>
#include <string>
#include "Board.hpp"
#include "Position.hpp"
#include "AttackResult.hpp"



using namespace std;


class Game {
    protected:
        Board* boardPlayerOne, *boardPlayerTwo;
        int boardSize;
        vector<AttackResult> turnResult;
        bool finished;
        void PrintAttackResult(AttackResult attackResult);
        void AttackHelper(Board*ownBoard, Board* enemyBoard);

    public:
        Game(int boardSize);
        ~Game();

        Board* GetBoardPlayerOne();
        void SetBoardPlayerOne(Board* boardPlayerOne);
        Board* GetBoardPlayerTwo();
        void SetBoardPlayerTwo(Board* boardPlayerTwo);
        int GetBoardSize();
        vector<AttackResult> GetTurnResult();
        void SetTurnResult(vector<AttackResult> turnResult);
        void AddTurnResult(AttackResult attackResult);
        bool HasFinished();

        virtual void Attack(Board* ownBoard, Board* enemyBoard){};
        
        void DisplayTurnResult(Board* ownBoard, Board* enemyBoard);
        void PlaceShips(Board board);

        
      
};

class ClassicGame: public Game {
    public:
        ClassicGame(int boardSize);
        ~ClassicGame();
        void Attack(Board* ownBoard, Board* enemyBoard);

};  

class SalvoGame: public Game {
    public:
        SalvoGame(int boardSize);
        ~SalvoGame();
        void Attack(Board* ownBoard, Board* enemyBoard);

};

#endif
