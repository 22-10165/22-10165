#include "estructuras.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

using std::vector;

extern vector<Coord_3D> puntos_originales;
extern vector<Labeled> puntos_acondicionados;

void loader(const char *filename, const char *sep, void (*reader)(const char *, FILE *, bool), bool load);
void leer_sss(const char *sep, FILE *archivo, bool load);
vector<Coord_3D> inicializar_centroides_pro(int k);
vector<Coord_3D> ejecutar_kmeans(int k, vector<Coord_3D> centroides_iniciales);


void generar_archivos_salida(const vector<Coord_3D>& centroides_finales, int k) {
    
    FILE* f_csv = fopen("clasificados.csv", "w");
    if (f_csv == nullptr) {
        fprintf(stderr, "Error al crear clasificados.csv\n");
        exit(EXIT_FAILURE);
    }
    for (const auto& p : puntos_acondicionados) {
        fprintf(f_csv, "%f,%f,%f,%c\n", p.coord.x, p.coord.y, p.coord.z, p.label);
    }
    fclose(f_csv);


    FILE* f_txt = fopen("summary.txt", "w");
    if (f_txt == nullptr) {
        fprintf(stderr, "Error al crear summary.txt\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < k; ++i) {
        int n_puntos = 0;
        double suma_distancias = 0.0;

        for (const auto& p : puntos_acondicionados) {
            if (p.label == ('A' + i)) {
                n_puntos++;
                suma_distancias += (p.coord - centroides_finales[i]).modulo();
            }
        }

        double md = (n_puntos > 0) ? (suma_distancias / n_puntos) : 0.0;


        fprintf(f_txt, "%c: %d, (%f, %f, %f), %f\n", 
                ('A' + i), n_puntos, centroides_finales[i].x, centroides_finales[i].y, centroides_finales[i].z, md);
    }
    fclose(f_txt);
}


int main(int argc, const char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <k> <archivo.csv>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int k = atoi(argv[1]);
    const char *filename = argv[2];

    if (k <= 0) {
        fprintf(stderr, "Error: k debe ser mayor a 0\n");
        exit(EXIT_FAILURE);
    }

    size_t len = strlen(filename);
    const char *ext = &filename[len - 4];

    loader(filename, ext, leer_sss, true);

    if ((size_t)k > puntos_originales.size()) {
        fprintf(stderr, "Error: k supera la cantidad de puntos\n");
        exit(EXIT_FAILURE);
    }

    vector<Coord_3D> arranque = inicializar_centroides_pro(k);
    vector<Coord_3D> centroides_finales = ejecutar_kmeans(k, arranque);

    // Genera tanto el archivo .csv como el .txt exigido por el cliente
    generar_archivos_salida(centroides_finales, k);

    fprintf(stdout, "Procesamiento NagySoft completado para k=%d.\n", k);
    return EXIT_SUCCESS;
}