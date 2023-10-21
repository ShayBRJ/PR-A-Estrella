/**
 * @file Maze.hh
 * @author Borja Medina Ramos
 * @brief Definición de la clase Maze que contendrá las casillas del laberinto
 * @version 0.1
 * @date 2023-10-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "Box.hh"
#include "Utils.hh"
#include <vector>
#include <list>
#include <set>
#include <algorithm>

class Box;
/**
 * @brief Estructura que recoge la información de la búsqueda para
 * posteriormente ingrersarla en los ficheros de salida.
 * 
 */
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


/**
 * @brief Estructura de dato que contendrá las casillas y que tendrá el control sobre esta.
 * Ya sea en la creación como en la modificación de las mismo o búsqueda desde la entrada a 
 * la salida utilizando la búsqueda A*
 * 
 */
class Maze {
  public:
    SIB BusquedaAEstrella(int opcion);
    Maze(matrix,int, int);
    int GetM();
    int GetN();
    std::pair<int, int> GetPosStart();
    std::pair<int, int> GetPosEnd();
    Boxes GetMaze() const;
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

