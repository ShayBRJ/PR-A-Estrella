#include "../include/Maze.hh"

Maze::Maze(matrix states, int m, int n) {
  this->_m = m;
  this->_n = n;
  maze.resize(m);
  for(int i = 0; i < m; i++) {
    maze[i].resize(n);
  }
  for(int i = 0; i < m; i++) {
    for(int j = 0; j < n; j++) {
      switch (states[i][j])
      {
      case 1:
        maze[i][j] = new Box(1, i, j, '#'); 
      break;
      case 0:
        maze[i][j] = new Box(0, i, j, ' '); 
      break;
      case 3:
        maze[i][j] = new Box(3, i, j, 'E');
        this->start = maze[i][j];
        this->_pos_start = std::make_pair(i,j);
      break;
      case 4:
        maze[i][j] = new Box(4, i, j, 'S');
        this->end = maze[i][j];
        this->_pos_end = std::make_pair(i,j);
      break;
      }
    }
  }
}

SIB Maze::BusquedaAEstrella() {
  std::list<Box*> A;
  std::list<Box*> C;
  SIB sib;
  sib.size_m = this->GetM();
  sib.size_n = this->GetN();
  sib.generados.push_front(start);
  A.push_back(start);
  while(!A.empty()) {
    Box* nodo = SelectLessCost(A);
    printMaze(nodo);
    A.remove(nodo);
    C.push_back(nodo);
    nodo->Inicialize(*this);
    if(nodo == this->end) {
      sib.inspeccionados = C;
      sib.coste = nodo->getGvalue();
      sib.camino.push_front(nodo);
      nodo = nodo->GetPrevious();
      while(nodo != start) {
        nodo->SetBlockWay();
        sib.camino.push_front(nodo);
        nodo = nodo->GetPrevious();
      }
      sib.camino.push_front(nodo);
      printMaze(nodo);
      return sib;
    }  
    for(auto x : nodo->GetMap()) {
      if(std::find(C.begin(), C.end(), x.second) != C.end()) continue;
      if(nodo->CalculateF(x.first ,x.second) < x.second->GetFValue() || std::find(A.begin(), A.end(), x.second) == A.end()) {
        x.second->FunctionH(*this);
        x.second->SetGValue(nodo->getGvalue() + nodo->GetCost()[x.first]);
        x.second->SetFValue(x.second->getHvalue() + x.second->getGvalue());
        x.second->SetPrevious(nodo);
        if(std::find(A.begin(), A.end(), x.second) == A.end()) {
          A.push_back(x.second);
          sib.generados.push_front(x.second);
        }
      }
    }
  }
  return sib;
}

void Maze::printMaze(Box* node) {
  if(node->getBlock() == ' ') node->SetBlockSpc();
  for(int i = 0; i < GetM(); i++) {
    for(int j=0; j < GetN(); j++) {

      if(GetMaze()[i][j]->getBlock() == 'W' || GetMaze()[i][j]->getBlock() == 'E' || GetMaze()[i][j]->getBlock() == 'S') {
        std::cout << "\x1B[32m" << GetMaze()[i][j]->getBlock() << "\033[0m";

      }
      else std::cout << this->GetMaze()[i][j]->getBlock();
    }
    std::cout << std::endl;
  }
  Utils::delay(100);
  if(node != start) system("clear");
}

Box *Maze::SelectLessCost(std::list<Box *> A) {
  std::map<double, Box *> boxes_to_calc_f;
  double cost = A.front()->GetFValue();
  for (auto x : A)
  {
    if (x->GetFValue() <= cost)
    {
      cost = x->GetFValue();
      boxes_to_calc_f.insert(std::make_pair(cost, x));
    }
  }
  return boxes_to_calc_f[cost];
}
