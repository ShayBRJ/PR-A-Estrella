/**
 * @file main.cc
 * @author Borja Medina Ramos
 * @brief Programa principal que muestra el menú dónde se debe insertar un fichero de entrada y otro de salida.
 * Tras ello evalua y realiza la búsqueda A* e introduce los resultados en el fichero de salida propuesto.
 * @version 0.1
 * @date 2023-10-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "../include/Maze.hh"
#include <fstream>
#include <string.h>

#include <sstream>

void MostrarMenu() {
  std::cout << "\tMENÚ PRINCIPAL\n";
  std::cout << "Opciones: \n";
  std::cout << "1) Seleccionar fichero de lectura\n";
  std::cout << "2) Seleccionar fichero de salida\n";
  std::cout << "3) Ejecutar A*\n";
  std::cout << "4) Salir\n";

}

void Print2File(std::ofstream& file_out, Maze maze, SIB info_block) {
  file_out << "\t\t\tBúsqueda A*";
  file_out << "\n\nNodo origen y destino:\n";
  for(int i = 0; i < maze.GetM(); i++) {
    for(int j = 0; j < maze.GetN(); j++) {
      switch (maze.GetMaze()[i][j]->getBlock())
      {
      case 'E':
        file_out << 'E';
        break;

      case 'S':
        file_out << 'S';
        break;

      case '#':
        file_out << '#';
        break;
      
      default:
        file_out << ' ';
        break;
      }
    }
    file_out << std::endl;
  }
  file_out << "\n\nNodos inspeccionados:\n";
  for(int i = 0; i < maze.GetM(); i++) {
    for(int j = 0; j < maze.GetN(); j++) {
      if(maze.GetMaze()[i][j]->getBlock()== '#') file_out << '#';
      else if(std::find(info_block.inspeccionados.begin(), info_block.inspeccionados.end(), maze.GetMaze()[i][j]) != info_block.inspeccionados.end()) {
        file_out << 'I';
      }
      else file_out << ' ';
    }
  file_out << std::endl;
  }
  file_out << "\n\nCasillas inspeccionadas: " << std::endl;
  for(auto x : info_block.inspeccionados) file_out << "( " << x->getPoxX() << ", " << x->gePosY() << " ) ";
  file_out << "\nNúmero de nodos inspeccionados: " << info_block.inspeccionados.size() << std::endl;
  file_out << "\n\nNodos generados:\n";
  for(int i = 0; i < maze.GetM(); i++) {
    for(int j = 0; j < maze.GetN(); j++) {
      if(maze.GetMaze()[i][j]->getBlock()== '#') file_out << '#';
      else if(std::find(info_block.generados.begin(), info_block.generados.end(), maze.GetMaze()[i][j]) != info_block.generados.end()) {
        file_out << 'G';
      }
      else file_out << ' ';
    }
      file_out << std::endl;
  }
  file_out << "\n\nCasillas generadas: " << std::endl;
  for(auto x : info_block.generados) file_out << "( " << x->getPoxX() << ", " << x->gePosY() << " ) ";
  file_out << "\nNúmero de nodos generados: " << info_block.generados.size() << std::endl;


  file_out << "\n\nCamino:\n";
  for(int i = 0; i < maze.GetM(); i++) {
    for(int j = 0; j < maze.GetN(); j++) {
      if(maze.GetMaze()[i][j]->getBlock()== '#') file_out << '#';
      else if(std::find(info_block.camino.begin(), info_block.camino.end(), maze.GetMaze()[i][j]) != info_block.camino.end()) {
        file_out << 'C';
      }
      else file_out << ' ';
    }
      file_out << std::endl;
  }
  file_out << "\n\nCasillas del camino: " << std::endl;
  for(auto x : info_block.camino) file_out << "( " << x->getPoxX() << ", " << x->gePosY() << " ) ";
  file_out << "\nCoste: " << info_block.coste << std::endl;
  file_out << "\nFilas(m): " << info_block.size_m  << std::endl;
  file_out << "\nColumnas(n): " << info_block.size_n  << std::endl;

}


void BusquedaEstrellaMain(std::ifstream &fichero_lectura, std::ofstream &fichero_salida, bool archivo_lectura_abierto, bool archivo_salida_abierto) {
  system("clear");
  if(archivo_lectura_abierto != true || archivo_salida_abierto != true) {
    std::cout << "Se necesita un fichero de lectura y salida correcto\n";
    getchar();
    getchar();
    return;
  }
  int opcion;
  std::cout << "Selecciona la función heurística:\n";
  std::cout << "1) Manhattan:\n";
  std::cout << "2) Chebyshev:\n";
  std::cout << "Opción: ";
  std::cin >> opcion;
  if(opcion != 1 && opcion != 2) {
    std::cout << "Esa opción no es valida\n";
    getchar();
    getchar();
    return;
  }
  std::string s, tmp; 
  matrix matrix;
  std::getline(fichero_lectura, s);
  matrix.resize(atoi(s.c_str()));
  std::getline(fichero_lectura, s);
  int iterator = 0;
  while(getline(fichero_lectura, s)) {
    std::stringstream ss(s);
    while(getline(ss, tmp, ' ')) {
      matrix[iterator].push_back(atoi(tmp.c_str()));     
    }
    iterator++;
  } 
  Maze maze(matrix, matrix.size(), matrix.at(0).size());
  SIB sib = maze.BusquedaAEstrella(opcion);
  Print2File(fichero_salida, maze, sib);
  fichero_lectura.clear();
  fichero_lectura.seekg(0);
  getchar();
  getchar();
}


int main(int argc, char** argv) {
  
  int opcion;
  bool archivo_lectura_abierto = false, archivo_salida_abierto = false;
  std::string linea_lectura;  
  std::ifstream fichero_lectura;
  std::ofstream fichero_salida;
  do {
    system("clear");
    MostrarMenu();
    std::cout << "Seleccionar la opcion: ";
    std::cin >> opcion;
    switch (opcion)
    {
    case 1:
      Utils::NuevoArchivoLectura(fichero_lectura, archivo_lectura_abierto);
      break;
    case 2:
      Utils::NuevoArchivoSalida(fichero_salida, archivo_salida_abierto);
      break;
    case 3:
      BusquedaEstrellaMain(fichero_lectura, fichero_salida, archivo_lectura_abierto, archivo_salida_abierto);
      break;
    default:
      return 0;
    }
  }while(opcion > 0 && opcion < 6);
}