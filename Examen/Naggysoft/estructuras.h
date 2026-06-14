///
/// estructuras.h
///

#pragma once
#include <string>
#include <vector>
#include <cmath>
//Puntos en el espacio 3D
struct Coord_3D {
double x;
double y;
double z;

Coord_3D operator+(const Coord_3D& otro) const {
    return { x + otro.x, y + otro.y, z + otro.z };
}

Coord_3D operator-(const Coord_3D& otro) const {
    return { x - otro.x, y - otro.y, z - otro.z };
}

double modulo() const {
    return std::sqrt(x * x + y * y + z * z);
}

};

// Dejamos declarado el vector global aquí para que tu código lo reconozca
extern std::vector<Coord_3D> puntos_originales;
//Puntos que se asociaran a clusters
struct Labeled {
Coord_3D coord;
char label;


};







