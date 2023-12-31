#include "../include/Box.hh"

/**
 * @brief Constructor de la clase Box
 * 
 * @param state Estado de la casilla.
 * @param pos_x Posición X en la que se encuentra.
 * @param pos_y Posición Y en la que se encuentra.
 * @param block_print Bloque identificador que se utilizará cuando se imprima por salida.
 */
Box::Box(int state, int pos_x, int pos_y, char block_print) {
  this->State = state;
  this->_posX = pos_x;
  this->_posY = pos_y;
  this->bloque_print = block_print;
}

/**
 * @brief Inicializa las casillas teniendo en cuenta las diferentes casillas que la rodean.
 * 
 * @param maze 
 */
void Box::Inicialize(Maze maze) {
  int casillas_maze = 0;
  int n = maze.GetN();
  int m = maze.GetM();
  for(int i = this->_posX - 1; i <= _posX + 1; i++) {
    for(int j = _posY - 1; j <= _posY + 1; j++) {
      if(i >= 0 && j >= 0 && i < m && j < n) {
        if(i == _posX && j == _posY) continue;
        if(maze.GetMaze()[i][j]->getState() == 1) {
          casillas_maze++;
          continue;
        }
        this->_boxes.insert(std::make_pair(casillas_maze, maze.GetMaze()[i][j]));
      }
    casillas_maze++;
    }
  }
  movement_cost();
}
/**
 * @brief Evalua el coste requerido para hacer el salto a la siguiente casilla.
 * 
 */
  void Box::movement_cost() {
    for(auto x : this->_boxes) {
      switch (x.first)
      {
      case UP:
        this->_cost.insert(std::make_pair(x.first, 5));
        break;
      case DOWN:
        this->_cost.insert(std::make_pair(x.first, 5));
        break;
      case LEFT:
        this->_cost.insert(std::make_pair(x.first, 5));
        break;
      case RIGHT:
        this->_cost.insert(std::make_pair(x.first, 5));
        break;
        default:
        this->_cost.insert(std::make_pair(x.first, 7));
        break;
      }
    }
  }

/**
 * @brief Calcula la f(x) para evaluar el coste final y así hacer el recorrido de menor coste.
 * 
 * @param iterator Determina el indice de la casilla a saltar y su coste asociado.
 * @param child Necesario para evaluar el coste de la casilla más cercana y evaluar si accediendo a ella conseguimos el menor coste.
 * @return double 
 */
double Box::CalculateF(int iterator, Box* child) {
  return child->getHvalue() + this->function_g + this->_cost[iterator];
}

/**
 * @brief Función heurística que proporciona un coste aproximado del camino real.
 * 
 * @param maze Matriz que representa el laberinto.
 * @return double 
 */
double Box::FunctionH(Maze maze, int opt) {
  switch (opt)
  {
  case 1:
    return this->function_h = (std::abs(maze.GetPosEnd().first - this->_posX) + std::abs(maze.GetPosEnd().second - this->_posY)) * 3;
    break;
  case 2:
    return this->function_h = std::max(std::abs(maze.GetPosEnd().first - this->_posX), std::abs(maze.GetPosEnd().second - this->_posY)) * 5;
    break;
  default:
    return this->function_h = (std::abs(maze.GetPosEnd().first - this->_posX) + std::abs(maze.GetPosEnd().second - this->_posY)) * 3;
    break;
  }
}
    // A continuación se muestran todos los setters y getters de los atributos de la clase.
    void Box::SetFValue(double value) { this->f_value = value;}
    void Box::SetGValue(double value) { this->function_g = value;}
    double Box::getHvalue() const {return this->function_h;}
    double Box::getGvalue() const {return this->function_g;}
    double Box::getPoxX() const {return this->_posX;}
    double Box::gePosY() const {return this->_posY;}
    void Box::SetBlockSpc() { this->bloque_print = 'x';}
    void Box::SetBlockWay() { this->bloque_print = 'W';}
    char Box::getBlock() { return bloque_print;}
    double Box::GetFValue() const { return this->f_value;}
    std::map<int, Box*> Box::GetMap() {return this->_boxes;}
    std::map<int, int> Box::GetCost() {return this->_cost;}
    void Box::SetPrevious(Box* previous) { this->previous = previous;}
    Box* Box::GetPrevious() { return this->previous;}
    int Box::getState() const {return this->State;}

    bool Box::operator<(const Box other) const {
      return ((this->gePosY() + this->getPoxX()) - (other.gePosY() + other.getPoxX()) < 0);
    }