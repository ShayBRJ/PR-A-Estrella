/**
 * @file Utils.hh
 * @author Borja Medina Ramos
 * @brief Contiene utilidades necesarias para obtener ciertos resultados u operaciones.
 * @version 0.1
 * @date 2023-10-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include <iostream>
#include <fstream>
#include <vector>

namespace Utils {
  void delay(int milliseconds);
  void NuevoArchivoSalida(std::ofstream& fichero_salida, bool& archivo_salida_abierto);
  void NuevoArchivoLectura(std::ifstream& fichero_lectura, bool& archivo_lectura_abierto);
}
