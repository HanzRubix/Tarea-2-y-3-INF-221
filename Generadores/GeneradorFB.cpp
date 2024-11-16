#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime> 

using namespace std;

int long_min = 2;
int long_max = 14;
int incremento = 2;

string generarCadena(int longitud, char car) {
    string resultado;
    for (int i = 0; i < longitud; ++i) {
        resultado += car;
    }
    return resultado;
}

string genTransEspecifica(int longitud) {
    string cadena = "abcdefghijklmnopqrstuvwx";
    while (cadena.length() < longitud) {
        cadena += cadena;  
    }
    cadena = cadena.substr(0, longitud);  

    if (longitud > 2) {
        for (int i = 0; i < longitud - 1; i += 2) {
            if (i + 1 < longitud && cadena[i] < cadena[i + 1]) {
                swap(cadena[i], cadena[i + 1]);
            }
        }
    }

    return cadena;
}

string genAleatorio(int longitud) {
    string resultado;
    for (int i = 0; i < longitud; ++i) {
        char aleatorio = 'a' + rand() % 26;
        resultado += aleatorio;
    }
    return resultado;
}

void escribir(const string &nameArc, const string &S1, const string &S2) {
    ofstream archivo(nameArc, ios::app); 
    if (archivo.is_open()) {
        archivo << S1 << endl;
        archivo << S2 << endl;
    } else {
        cerr << "Error" << nameArc << endl;
    }
}

void genVacio() {
    ofstream archivo("caso1FB.txt");
    for (int i = long_min; i <= long_max; i += incremento) {
        string S1_vacio = generarCadena(i, ' ');
        string S2_vacio = generarCadena(i, ' ');
        escribir("caso1FB.txt", S1_vacio, S2_vacio);
    }
}

void genRepetido() {
    ofstream archivo("caso2FB.txt");
    for (int i = long_min; i <= long_max; i += incremento) {
        string S1_repetidos = generarCadena(i, 'a');
        string S2_repetidos = generarCadena(i, 'a');
        escribir("caso2FB.txt", S1_repetidos, S2_repetidos);
    }
}

void genTrans() {
    ofstream archivo("caso3FB.txt");
    for (int i = long_min; i <= long_max; i += incremento) {
        string S1_transposicion = "abcdefghij";
        while (S1_transposicion.length() < i) {
            S1_transposicion += S1_transposicion;
        }
        S1_transposicion = S1_transposicion.substr(0, i);

        string S2_transposicion = S1_transposicion;
        if (i > 1) {
            swap(S2_transposicion[i - 2], S2_transposicion[i - 1]);
        }

        escribir("caso3FB.txt", S1_transposicion, S2_transposicion);
    }
}

void genDistintos() {
    ofstream archivo("caso4FB.txt");
    for (int i = long_min; i <= long_max; i += incremento) {
        string S1_diferentes = generarCadena(i, 'a');
        string S2_diferentes = generarCadena(i, 'z');
        escribir("caso4FB.txt", S1_diferentes, S2_diferentes);
    }
}

void genSimilar() {
    ofstream archivo("caso5FB.txt");
    for (int i = long_min; i <= long_max; i += incremento) {
        string S1_similares = "hola";
        string S2_similares = "hola";
        while (S1_similares.length() < i) {
            S1_similares += "hola";
        }
        while (S2_similares.length() < i) {
            S2_similares += "holb";
        }
        S1_similares = S1_similares.substr(0, i);
        S2_similares = S2_similares.substr(0, i);
        escribir("caso5FB.txt", S1_similares, S2_similares);
    }
}

void genLongDistinto() {
    ofstream archivo("caso6FB.txt");
    for (int i = long_min; i <= long_max; i += incremento) {
        string S1 = genAleatorio(i);
        string S2 = genAleatorio(i + 2);
        escribir("caso6FB.txt", S1, S2);
    }
}

void genAleatorio() {
    ofstream archivo("caso7FB.txt");
    for (int i = long_min; i <= long_max; i += incremento) {
        string S1_aleatorio = genAleatorio(i);
        string S2_aleatorio = genAleatorio(i);
        escribir("caso7FB.txt", S1_aleatorio, S2_aleatorio);
    }
}

int main() {
    srand(time(0)); 
    genVacio();
    genRepetido();
    genTrans();
    genDistintos();
    genSimilar();
    genLongDistinto();
    genAleatorio();

    cout << "Dataset Creado." << endl;

    return 0;
}
