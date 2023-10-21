#include "../include/Utils.hh"

/**
 * @brief Provoca un retrase intencionado en el programa.
 * 
 * @param milliseconds 
 */
void Utils::delay(int milliseconds)
  {
    long pause;
    clock_t now, then;
    pause = milliseconds * (CLOCKS_PER_SEC/1000);
    now = then = clock();
    while( (now-then) < pause ) now = clock();
  }

void Utils::NuevoArchivoSalida(std::ofstream& fichero_salida, bool& archivo_salida_abierto) {
  system("clear");
  fichero_salida.close();
  std::cin.ignore();
  std::string linea_lectura;
  std::cout << "Ingresa el fichero de salida: ";
  std::getline(std::cin, linea_lectura);
  fichero_salida.open(linea_lectura, std::ios_base::out);
  archivo_salida_abierto = true;
  if(!fichero_salida.is_open()) {
    std::cout << "El fichero no ha podido crearse, intentelo de nuevo\n";
    archivo_salida_abierto = false;
  }
}

void Utils::NuevoArchivoLectura(std::ifstream& fichero_lectura, bool& archivo_lectura_abierto) {
  system("clear");
  std::cin.ignore();
  fichero_lectura.close();
  std::string linea_lectura;
  std::cout << "Ingresa el fichero de lectura: ";
  getline(std::cin, linea_lectura);
  fichero_lectura.open(linea_lectura, std::ios_base::in);
  archivo_lectura_abierto = true;
  if(!fichero_lectura.is_open()) {
    std::cout << "El fichero no ha podido abrirse, intentelo de nuevo\n";
    std::getchar();
    archivo_lectura_abierto = false;
  }
}