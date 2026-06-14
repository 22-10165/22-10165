#include "estructuras.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cfloat> // Para usar DBL_MAX (el número más grande posible)

using std::vector;

extern vector<Coord_3D> puntos_originales; 

vector<Labeled> puntos_acondicionados = {};

vector<Coord_3D> inicializar_centroides_pro(int k) {
    srand(time(nullptr));

    // 1. Preparar el vector con la estructura oficial Labeled
    puntos_acondicionados.clear();
    for (const auto& p_orig : puntos_originales) {
        puntos_acondicionados.push_back({p_orig, ' '}); 
    }

    vector<Coord_3D> centroides;

    // 2. CENTROIDE 1: Elegir uno al azar para romper el hielo
    int primer_indice = rand() % puntos_originales.size();
    centroides.push_back(puntos_originales[primer_indice]);

    // 3. CENTROIDES RESTANTES: Buscar los puntos más alejados
    for (int c = 1; c < k; ++c) {
        double maxima_distancia_idnea = -1.0;
        int indice_punto_mas_lejano = 0;

        // Evaluamos cada punto disponible para ver cuál está más lejos
        for (size_t i = 0; i < puntos_originales.size(); ++i) {
            Coord_3D punto_actual = puntos_originales[i];

            // Buscamos la distancia al centroide más cercano de los que ya elegimos
            double d_min = DBL_MAX;
            for (const auto& centroide_listo : centroides) {
                // ¡Aquí usamos tus operadores estrella! resta (-) y modulo()
                double d = (punto_actual - centroide_listo).modulo();
                if (d < d_min) {
                    d_min = d;
                }
            }

            // El punto que tenga la mayor "distancia mínima" es nuestro candidato alejado
            if (d_min > maxima_distancia_idnea) {
                maxima_distancia_idnea = d_min;
                indice_punto_mas_lejano = i;
            }
        }

        // Agregamos el punto ultra-alejado como el siguiente jefe de cluster
        centroides.push_back(puntos_originales[indice_punto_mas_lejano]);
    }

    return centroides;
}