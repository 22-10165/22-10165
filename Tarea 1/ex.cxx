

//Nota aparte se uso gemini para corregir algunos errores de sintaxis y averiguar como definir disitnto la funcion void a double, ya que con void no se puede retornar vables


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

#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>


using namespace std;
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
double variance(const vector<double>& VA) {
    int n = VA.size();
    double prom=mean(VA);
    double sumacuadrados = 0;
    for (int i = 0; i < n; ++i) {
        sumacuadrados= sumacuadrados + ((VA[i]-prom)*(VA[i]-prom));
    }
    double varianza= sumacuadrados/(n-1);
    printf("varianza %.4f\n",varianza);
return varianza;
    }





double pearson_r(const vector<double>& VA, const vector<double>& VB) {
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
    return r;
}


#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>

using std::vector;
using std::string;
vector<char> dec_to_septapus(int n){
if (n == 0) return {'0'};
bool esNegativo = (n < 0);
if (esNegativo) n = -n;
    vector<char> resultado;
  vector<char> resultado_final;
      if (n == 0) return {'0'};
      while (n > 0) {
          int residuo = n % 7;       
          resultado.push_back(residuo + '0'); 
          n = n / 7;
      }
    if (esNegativo) resultado.push_back('-'); 
  int cantidadelem = resultado.size();
    for (int i = 0; i < cantidadelem; i++) {
     //Para invertir el orden
      resultado_final.push_back(resultado[cantidadelem - 1 - i]);

  }
  return resultado_final;
} // la cual convierte un numero decimal a su representacion en el sistema de Septapus Mirabilis
 
vector<char> dec_to_octopus(int n){
if (n == 0) return {'0'};
bool esNegativo = (n < 0);
if (esNegativo) n = -n;
  vector<char> resultado;
  vector<char> resultado_final;
      if (n == 0) return {'0'};
      while (n > 0) {
          int residuo = n % 8;       
          resultado.push_back(residuo + '0'); 
          n = n / 8;
      }
       if (esNegativo) resultado.push_back('-'); 
  int cantidadelem = resultado.size();
    for (int i = 0; i < cantidadelem; i++) {
     //Para invertir el orden
      resultado_final.push_back(resultado[cantidadelem - 1 - i]);

  }
  return resultado_final;
}// la cual convierte un numero decimal a su representacion en el sistema de Octopus Sapiens

vector<char> dec_to_hexakaidecapus(int n){
      vector<char> resultado;
    vector<char> resultado_final;

    
      if (n == 0) return {'0'};
    if (n == 0) return {'0'};
bool esNegativo = (n < 0);
if (esNegativo) n = -n;
  while (n > 0) {

    
      int residuo = n % 16;

      if (residuo < 10) {
          resultado.push_back(residuo + '0'); // Para 0-9
      } 
      else if (residuo == 10) {
          resultado.push_back('A');
      } 
      else if (residuo == 11) {
          resultado.push_back('B');
      } 
      else if (residuo == 12) {
          resultado.push_back('C');
      } 
      else if (residuo == 13) {
          resultado.push_back('D');
      } 
      else if (residuo == 14) {
          resultado.push_back('E');
      } 
      else if (residuo == 15) {
          resultado.push_back('F');
      }

      n = n / 16;


    
  }
      if (esNegativo) resultado.push_back('-'); 
  int cantidadelem = resultado.size();
    for (int i = 0; i < cantidadelem; i++) {
     //Para invertir el orden
      resultado_final.push_back(resultado[cantidadelem - 1 - i]);

  }
  return resultado_final;
} // la cual convierte un numero decimal a su representacion en el sistema de Hexakaidecapus Turing
vector<char> septapus_to_dec(vector<char> s){
    bool esNegativo = (s[0] == '-');
    int inicio;

    if (esNegativo) {
        inicio = 1;
    } else {
        inicio = 0; 
    }

    
  vector<char> resultado_final;
  vector<char> resultado;
  int valdecimal=0;
  double bm= 7;
  int N= s.size();
  for (int i = inicio; i < N; i++) {
    int var= pow(bm,N-1-i);
     int l= (s[i] - '0') * var;
    valdecimal+=l;
      }
if (esNegativo) {
        valdecimal = -valdecimal;
    }

  //Converitmos valdecimala  a vector de char como el while
  if (valdecimal == 0) return {'0'};
    //Aqui hay un while que solo admite positivos  por ende para hacer la conversion a vector primero se vueve a convertir val decimal en positivo
    bool resNegativo = (valdecimal < 0);
    if (resNegativo) {
        valdecimal = -valdecimal;
    }
      
      while (valdecimal > 0) {
         
          int digito = valdecimal % 10;
          resultado.push_back(digito + '0'); 

          valdecimal = valdecimal / 10;
      }
    if (resNegativo) {
              resultado.push_back('-');
          }
      for (int i = resultado.size() - 1; i >= 0; i--) {
          resultado_final.push_back(resultado[i]);
      }

    
      return resultado_final;
} // la cual convierte un numero representado en el sistema de Septapus Mirabilis a su representacion decimal
vector<char> octopus_to_dec(vector<char> s){
   bool esNegativo = (s[0] == '-');
    int inicio;

    if (esNegativo) {
        inicio = 1;
    } else {
        inicio = 0; 
    }

    vector<char> resultado_final;
    vector<char> resultado;
    int valdecimal=0;
    double bm= 8;
    int N= s.size();
    for (int i = inicio; i < N; i++) {
      int var= pow(bm,N-1-i);
       int l= (s[i] - '0') * var;
      valdecimal+=l;
        }
if (esNegativo) {
        valdecimal = -valdecimal;
    }

  //Converitmos valdecimala  a vector de char como el while
  if (valdecimal == 0) return {'0'};
    //Aqui hay un while que solo admite positivos  por ende para hacer la conversion a vector primero se vueve a convertir val decimal en positivo
    bool resNegativo = (valdecimal < 0);
    if (resNegativo) {
        valdecimal = -valdecimal;
    }
      

        while (valdecimal > 0) {

            int digito = valdecimal % 10;
            resultado.push_back(digito + '0'); 

            valdecimal = valdecimal / 10;
        }
      if (resNegativo) {
              resultado.push_back('-');
          }
        for (int i = resultado.size() - 1; i >= 0; i--) {
            resultado_final.push_back(resultado[i]);
        }
        return resultado_final;
  }  



// la cual convierte un numero representado en el sistema de Octopus Sapiens a su representacion decimal

vector<char> hexakaidecapus_to_dec(vector<char> s) {
     bool esNegativo = (s[0] == '-');
    int inicio;

    if (esNegativo) {
        inicio = 1;
    } else {
        inicio = 0; 
    }
    vector<char> resultado_final;
    vector<char> resultado;
    if (esNegativo) {
        valdecimal = -valdecimal;
    }
    int valdecimal = 0;
    double bm = 16; 
    int N = s.size();

    for (int i = inicio; i < N; i++) {
        int var = pow(bm, N - 1 - i);
        int valor_real;

        if (s[i] >= '0' && s[i] <= '9') {
            valor_real = s[i] - '0';
        } 
        else if (s[i] == 'A' || s[i] == 'a') {
            valor_real = 10;
        } 
        else if (s[i] == 'B' || s[i] == 'b') {
            valor_real = 11;
        } 
        else if (s[i] == 'C' || s[i] == 'c') {
            valor_real = 12;
        } 
        else if (s[i] == 'D' || s[i] == 'd') {
            valor_real = 13;
        } 
        else if (s[i] == 'E' || s[i] == 'e') {
            valor_real = 14;
        } 
        else if (s[i] == 'F' || s[i] == 'f') {
            valor_real = 15;
        }


        valdecimal += valor_real * var;
    }


  if (valdecimal == 0) return {'0'};
    //Aqui hay un while que solo admite positivos  por ende para hacer la conversion a vector primero se vueve a convertir val decimal en positivo
    bool resNegativo = (valdecimal < 0);
    if (resNegativo) {
        valdecimal = -valdecimal;
    }
    while (valdecimal > 0) {
        int digito = valdecimal % 10;
        resultado.push_back(digito + '0'); 
        valdecimal = valdecimal / 10;
    }
      if (resNegativo) {
              resultado.push_back('-');
          }
    for (int i = resultado.size() - 1; i >= 0; i--) {
        resultado_final.push_back(resultado[i]);
    }
    

    return resultado_final;
}
 
  vector<char> septapus_to_octopus(vector<char> s) {
      vector<char> dec_vector = septapus_to_dec(s);
      int val_entero = 0;
      for (int i = 0; i < dec_vector.size(); i++) {
          val_entero = val_entero * 10 + (dec_vector[i] - '0');
      }
      return dec_to_octopus(val_entero);
  }
vector<char> septapus_to_hexakaidecapus(vector<char> s){
        vector<char> dec_vector = septapus_to_dec(s);
        int val_entero = 0;
        for (int i = 0; i < dec_vector.size(); i++) {
            val_entero = val_entero * 10 + (dec_vector[i] - '0');
        }
        return dec_to_hexakaidecapus(val_entero);
    } 
vector<char> octapus_to_septapus(vector<char> s){
       vector<char> dec_vector = octopus_to_dec(s);
          int val_entero = 0;
          for (int i = 0; i < dec_vector.size(); i++) {
              val_entero = val_entero * 10 + (dec_vector[i] - '0');
          }
          return dec_to_septapus(val_entero);
      } // la cual convierte un numero representado en el sistema de Octopus Sapiens a su representacion en el sistema de Septapus Mirabilis
vector<char> octopus_to_hexakaidecapus(vector<char> s){
  vector<char> dec_vector = octopus_to_dec(s);
      int val_entero = 0;
      for (int i = 0; i < dec_vector.size(); i++) {
          val_entero = val_entero * 10 + (dec_vector[i] - '0');
      }
      return dec_to_hexakaidecapus(val_entero);
  } // la cual convierte un numero representado en el sistema de Octopus Sapiens a su
vector<char> hexakaidecapus_to_septapus(vector<char> s){
  vector<char> dec_vector = hexakaidecapus_to_dec(s);
      int val_entero = 0;
      for (int i = 0; i < dec_vector.size(); i++) {
          val_entero = val_entero * 10 + (dec_vector[i] - '0');
      }
      return dec_to_septapus(val_entero);
  } // la cual convierte un numero representado en el sistema de Hexakaidecapus Turing a su representacion en el sistema de Septapus Mirabilis
vector<char> hexakaidecapus_to_octopus(vector<char> s){
  vector<char> dec_vector = hexakaidecapus_to_dec(s);
      int val_entero = 0;
      for (int i = 0; i < dec_vector.size(); i++) {
          val_entero = val_entero * 10 + (dec_vector[i] - '0');
      }
      return dec_to_octopus(val_entero);
  }
 // la cual convierte un numero representado en el sistema de Hexakaidecapus Turing a su representacion en el sistema de Octopus Sapiens
int main () {
        return 0;
    }



