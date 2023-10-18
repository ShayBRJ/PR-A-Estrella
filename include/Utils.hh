#pragma once
#include <iostream>
#include <fstream>
#include <time.h>

namespace Utils {
  void delay(int milliseconds);
  void NuevoArchivoSalida(std::ofstream& fichero_salida, bool& archivo_salida_abierto);
  void NuevoArchivoLectura(std::ifstream& fichero_lectura, bool& archivo_lectura_abierto);
}
