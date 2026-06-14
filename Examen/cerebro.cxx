#include "estructuras.h"
#include <vector>
#include <cfloat> // Para usar DBL_MAX

using std::vector;

// Le avisamos al cerebro que el acondicionador ya creó este vector global
extern vector<Labeled> puntos_acondicionados;

const int MAX_ITERATIONS = 100;

//Esta funcion es para ver que punto esta mas cerca de cada centroide
void getLabels(const vector<Coord_3D>& centroides) {
    for (auto& p : puntos_acondicionados) {
        double min_distancia = DBL_MAX;
        char letra_mas_cercana = 'A';

        // Aqui se mide cada punto a ver que centroide le queda más cerca
        for (size_t j = 0; j < centroides.size(); ++j) {
            double d = (p.coord - centroides[j]).modulo();

            if (d < min_distancia) {
                min_distancia = d;
                letra_mas_cercana = 'A' + j; // esto les otorga las categorias
            }
        }
        //Se agrega el punto al centroide mas cecano 
        p.label = letra_mas_cercana;
    }
}



vector<Coord_3D> getCentroids(int k, const vector<Coord_3D>& centroides_viejos) {
    vector<Coord_3D> nuevos_centroides(k, {0.0, 0.0, 0.0});
    vector<int> contadores(k, 0);
    
    for (const auto& p : puntos_acondicionados) {
        int idx = p.label - 'A'; 
        if (idx >= 0 && idx < k) {
            
            nuevos_centroides[idx] = nuevos_centroides[idx] + p.coord;
            contadores[idx]++;
        }
    }

    for (int i = 0; i < k; ++i) {
        if (contadores[i] > 0) {
            nuevos_centroides[i].x /= contadores[i];
            nuevos_centroides[i].y /= contadores[i];
            nuevos_centroides[i].z /= contadores[i];
        } else {
            // estos por si no hay puntos en un cluster al hacer el cambio
            nuevos_centroides[i] = centroides_viejos[i];
        }
    }

    return nuevos_centroides;
}
/* Esto eslo que se la pasa a la funcion get centroida 
  viejos y nuevos: Listas de centroides para comparar su cambio de posición.
  iteraciones: El contador de vueltas actual del algoritmo.
  
  JUSTIFICACIÓN:
 shouldStop es la condicion de parada para al kmeans, es posible que al mover los centroides 
 este moviemeinto ya no sea significativo y Asi si despues de 100 iteraciones de la 
 funcion getcentroids no se cumple la condicion se detiene el programa, porque si no
 se puede generar un ciclo infinito.
 */


bool shouldStop(const vector<Coord_3D>& viejos, const vector<Coord_3D>& nuevos, int iteraciones) {
    if (iteraciones >= MAX_ITERATIONS) return true;

    for (size_t i = 0; i < viejos.size(); ++i) {
        
        if ((viejos[i] - nuevos[i]).modulo() > 1e-6) {
            return false; 
        }
    }
    return true; 
}


vector<Coord_3D> ejecutar_kmeans(int k, vector<Coord_3D> centroides_iniciales) {
    vector<Coord_3D> centroids = centroides_iniciales;
    vector<Coord_3D> oldCentroids;
    int iterations = 0;

    while (iterations == 0 || !shouldStop(oldCentroids, centroids, iterations)) {
        oldCentroids = centroids;
        iterations++;

        getLabels(centroids);
        centroids = getCentroids(k, oldCentroids);
    }

    return centroids;
}


