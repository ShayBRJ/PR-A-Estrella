#pragma once
#include <map>
#include <math.h>
#include <vector>
#include "Maze.hh"

#define UPL 0
#define UP 1
#define UPR 2
#define LEFT 3
#define RIGHT 4 
#define DOWNL 5
#define DOWN 6
#define DOWNR 7

class Maze;

class Box
{
  public:
    double FunctionH(Maze, int);
    Box(int state, int pos_x, int pos_y, char block);
    int getState() const;
    bool operator<(const Box) const;
    void Inicialize(Maze maze);
    void SetFValue(double value);
    void SetGValue(double value);
    double getHvalue() const;
    double getGvalue() const; 
    double getPoxX() const;
    double gePosY() const;
    void SetBlockSpc();
    void SetBlockWay();
    char getBlock();
    double GetFValue() const;
    std::map<int, Box*> GetMap();
    std::map<int, int> GetCost();
    void SetPrevious(Box* previous);
    Box* GetPrevious();
    double CalculateF(int, Box*);

  private:
    void movement_cost();
    double function_h;
    double function_g;
    Box* previous;
    double f_value;
    int _posX;
    int _posY;
    int State;
    char bloque_print;
    std::map<int, Box*> _boxes;
    std::map<int, int> _cost;
};