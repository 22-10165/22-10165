///Tarea 1 Ejercicio 3
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>

using std::vector;
using std::string;



double mean(const vector<double>& VA) {
    int n = VA.size();
    double sum_A = 0;

    for (int i = 0; i < n; i++) {
        sum_A += VA[i];
        
    }
    //Aqui se podria hacer un if else para el caso denominador iual a cero, sin embargo (n == 0) ? 0 cumple esta funcion
    double prom = (n == 0) ? 0 : (sum_A)/n;
    return prom;
}

void variance(const vector<double>& VA) {
    int n = VA.size();
    double prom=promedio(VA);
    double sumacuadrados = 0;
    for (int i = 0; i < n; ++i) {
        sumacuadrados= sumacuadrados + ((VA[i]-prom)*(VA[i]-prom));
    }
    double varianza= sumacuadrados/(n-1);
    printf("varianza %.4f\n",varianza);
    }


//Utilizado como ejemplo el ejercico 4 para recibir y almacenar datos en vectores se establece
int main () {

     int n;
        printf("Ingrese la cantidad de elementos: ");
        scanf("%d", &n);

        vector<double> VA(n);

        printf("Ingrese los %d valores de VA: ", n);
        for (int i = 0; i < n; i++) scanf("%lf", &VA[i]);
        printf("\n--- Resultados ---\n");
        double l=mean(VA);
        printf("promedio %.4f\n",l);
        variance(VA);
        return 0;
    }

//Nota aparte se uso gemini para corregir algunos errores de sintaxis y averiguar como definir disitnto la funcion void a double, ya que con void no se puede retornar vables
    










//Tarea ejercicio4
//Esta pregunta es "AI encouraged". Les pedimos que usen inteligencia artificial.
//Recuerden que DEBEN mostrar los datos requeridos en un archivoo llamado "metadata.txt", y no dentro del código.
//Sea S un conjunto de elementos que poseen dos propiedades: A y B. Representamos S con dos vectores, VA y VB (valores de A y B), donde cada elemento de S corresponde a elementos de VA y VB que tienen el mismo índice.
//Programen una función, llamada pearson_r, que computa el coeficiente de correlación de las variables A y B.
//Digan qué modelo de IA usaron. No manden los "prompts" (pueden ser largos) pero recomendamos que los guarden -pueden ayudar en caso de revisión.

//El modelo utilizado fue gemini

//Resumen de lo que se pidio en gemini: Se pidio al modelo que creara una funcion bajo esta logica:
//1. Almacenar los datos en forma de vectores
//2. Calcular los valores necesarios que se iban a necesitar para la formula de pearson para que el programa final no fuera tan largo
//3. Hacer el calculo necesario para la formula de pearson y devolver el valor.

//Nota aparte
//Aqui se puede considerar que el programa no tiene una condicion if donde le notifica que al usuario que los vectores no tienen cantidad de elementos iguales aunque igual cumple la funcion ya que al no tener la  misma cantidad de elementos el programa no termina de ejecutarse.



#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio> // Para usar printf

using namespace std;

void pearson_r(const vector<double>& VA, const vector<double>& VB) {
    int n = VA.size();
    double sum_A = 0, sum_B = 0, sum_AB = 0;
    double sum_A2 = 0, sum_B2 = 0;

    for (int i = 0; i < n; i++) {
        sum_A += VA[i];
        sum_B += VB[i];
        sum_AB += VA[i] * VB[i];
        sum_A2 += VA[i] * VA[i];
        sum_B2 += VB[i] * VB[i];
    }

    // Fórmula directa computacionalmente eficiente
    double numerador = (n * sum_AB) - (sum_A * sum_B);
    double denominador = sqrt(((n * sum_A2) - (sum_A * sum_A)) * ((n * sum_B2) - (sum_B * sum_B)));

    double r = (denominador == 0) ? 0 : numerador / denominador;

    // Impresión con printf como mencionaste
    printf("\n--- Resultados ---\n");
    printf("Coeficiente de correlacion Pearson (r): %.4f\n", r);
}

int main() {
    int n;
    printf("Ingrese la cantidad de elementos: ");
    scanf("%d", &n);

    vector<double> VA(n), VB(n);

    printf("Ingrese los %d valores de VA: ", n);
    for (int i = 0; i < n; i++) scanf("%lf", &VA[i]);

    printf("Ingrese los %d valores de VB: ", n);
    for (int i = 0; i < n; i++) scanf("%lf", &VB[i]);

    pearson_r(VA, VB);

    return 0;
}

using namespace std;

int main(){
  return 0;
}

double mean(vector<double> v){
  return 0;
}

double variance(vector<double> v){
  return 0;
}

double pearson_r(vector<double> A, vector<double> B){
  return 0;
}

vector<char> dec_to_septapus(int n){return {};}
vector<char> dec_to_octopus(int n){return {};}
vector<char> dec_to_hexakaidecapus(int n){return {};}
vector<char> septapus_to_dec(vector<char> s){return {};}
vector<char> octopus_to_dec(vector<char> s){return {};}
vector<char> hexakaidecapus_to_dec(vector<char> s){return {};}
vector<char> septapus_to_octopus(vector<char> s){return {};}
vector<char> septapus_to_hexakaidecapus(vector<char> s){return {};}
vector<char> octapus_to_septapus(vector<char> s){return {};}
vector<char> octopus_to_hexakaidecapus(vector<char> s){return {};}
vector<char> hexakaidecapus_to_septapus(vector<char> s){return {};}
vector<char> hexakaidecapus_to_octopus(vector<char> s){return {};}
