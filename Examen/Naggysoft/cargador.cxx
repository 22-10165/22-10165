#include "estructuras.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

using std::string;
using std::vector;



// --- TUS VARIABLES GLOBALES (Añadimos esto aquí arriba) ---
const bool debug_mode = true;
char linea[1024]; 
vector<Coord_3D> puntos_originales = {}; // Tu vector global de puntos
void error(const char *message, const char *program) {
    fprintf(stderr, message, program);
    exit(EXIT_FAILURE);
}

// esta función no reconoce los campos por separado - simplemente lee e imprime la linea completa
void leer_linea(const char *sep, FILE *archivo, bool load = false) {
    if (load) {
        error("leer_linea NO puede usarse como cargador - no reconoce los campos de la estructura eseada", "");
    }
    for (;;) {
        fgets(linea, sizeof(linea), archivo);
        if (feof(archivo)) break;
        if (debug_mode) {
            fprintf(stdout, "%s", linea);
        }
    }
}


// esta función reconoce los campos "coordenada x", "coordenada y", y "coordenada z"
void leer_sss(const char *sep, FILE *archivo, bool load = true) {
    double cx;
    double cy;
    double cz;

  // Esto funciona
    const char *CSV = "%lf,%lf,%lf\n";   // Lee tres doubles separados por comas
    const char *format = string(sep) == ".csv" ? CSV : "horror";


     while (!feof(archivo)) {
          // lectura
          fscanf(archivo,format,&cx,&cy,&cz);

          if (debug_mode) {
              fprintf(stdout, "{ Coordenada x: %f, y: %f, z: %f }\n", cx, cy, cz);
          }

          if (load) {
              // en modo cargador: agregar el estudiante
              puntos_originales.push_back({cx, cy, cz});
          }
      }
}


  // El tipo de nuestros lectores (y cargadores) de archivos .csv y .tsv
  typedef void Reader(const char *sep, FILE *file, bool load);

  // filename: nombre del archivo a cargar
  // sep: separador de campos - solo se permite .csv (separar por coma ",") y .tsv (separar por TAB "\t")
  // reader: el lector (y cargador ... ¡si el parámetro 'load' esta "activado"!) de archivos
  // load: es la condición (flag) que permite que el lector cargue los registros en la tabla de estudiantes

  void loader(const char *filename, const char *sep, Reader reader, bool load = false) {

      FILE *data = fopen(filename, "r");
      if (data == nullptr) {
          error("El archivo %s no pudo ser abierto\n", filename);
      }

      reader(sep, data, load);

      fclose(data);
  }
/*
  void pause() {
      fprintf(stdout, "Press <Enter> to continue - Presione <Entrar> para continuar\n");
      getchar();
  }
*/
    void check_data_load() {
        if (debug_mode) {
        fprintf(stdout, "Tabla de puntos 3D cargados:\n");
            for (const Coord_3D& p : puntos_originales) {
                fprintf(stdout, "{ X: %.4f, Y: %.4f, Z: %.4f }\n", p.x, p.y, p.z);
            }
        }
        fprintf(stdout, "%zu puntos cargados exitosamente\n", puntos_originales.size());
    }

/*

    int main(int argc, const char *argv[]) {

        if (argc != 2) {
            error("uso: %s <nombre del archivo a cargar (.csv | .tsv)>\n", argv[0]);
        }

        const char *filename = argv[1];

        size_t len = strlen(filename);
        if (len < 5 || filename[len - 4] != '.') {
            error("El archivo %s tiene una extensión inválida\n", argv[0]);
        }

        const char *ext = &filename[len - 4];
        if (string(ext) != ".csv" && string(ext) != ".tsv" ) {
            error("El archivo %s tiene una extensión no soportada\n", argv[0]);
        }

        fprintf(stdout, "Usando la funcion leer_linea para leer el archivo\n");
        loader(filename, ext, leer_linea);
        pause();

        fprintf(stdout, "Usando la funcion leer_sss para cargar el archivo\n");
        loader(filename, ext, leer_sss, true);
        check_data_load();
        pause();
        exit(EXIT_SUCCESS);
    }



*/


