#pragma once
#include "Box.hh"
#include "Utils.hh"
#include <vector>
#include <list>
#include <set>
#include <algorithm>

class Box;

struct SIB //Search Information block
{
  std::list<Box*> inspeccionados;
  std::list<Box*> camino;
  std::list<Box*> generados;
  std::string tipo_busqueda;
  std::pair<int,int> nodo_origen;
  std::pair<int,int> nodo_destino;
  int size_n;
  int size_m;
  double coste;
};

typedef std::vector<std::vector<Box*>> Boxes;
typedef std::vector<std::vector<int>> matrix;

class Maze {
  public:
    SIB BusquedaAEstrella();
    Maze(matrix,int, int);
    int GetM() {return this->_m;}
    int GetN() {return this->_n;}
    std::pair<int, int> GetPosStart() { return _pos_start; }
    std::pair<int, int> GetPosEnd() { return _pos_end; }
    Boxes GetMaze() const {return this->maze;}
  private:
    void printMaze(Box*);
    Box* SelectLessCost(std::list<Box*> A);
    std::pair<int, int> _pos_start;
    std::pair<int, int> _pos_end;
    Boxes maze;
    int _m;
    int _n;
    Box* start;
    Box* end;
};

