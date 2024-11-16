#include <bits/stdc++.h>
#include <chrono>
using namespace std;
using namespace std::chrono;

vector<int> costo_insercion(26);
vector<int> costo_eliminacion(26);
vector<vector<int>> costo_sustitucion(26, vector<int>(26));
vector<vector<int>> costo_transposicion(26, vector<int>(26));

void costoFilas(const string &arcName, vector<int> &tabla) {
    ifstream arch(arcName);
    if (arch.is_open()) {
        for (int i = 0; i < 26; i++) {
            arch >> tabla[i];
        }
        arch.close();
    } else {
        cerr << "Error" << arcName << endl;
    }
}

void costoMatriz(const string &arcName, vector<vector<int>> &tabla) {
    ifstream arch(arcName);
    if (arch.is_open()) {
        for (int i = 0; i < 26; i++) {
            for (int j = 0; j < 26; j++) {
                arch >> tabla[i][j];
            }
        }
        arch.close();
    } else {
        cerr << "Error" << arcName << endl;
    }
}

int costo_ins(char c) {
    return costo_insercion[c - 'a'];
}

int costo_del(char c) {
    return costo_eliminacion[c - 'a'];
}

int costo_sub(char a, char b) {
    return costo_sustitucion[a - 'a'][b - 'a'];
}

int costo_trans(char a, char b) {
    return costo_transposicion[a - 'a'][b - 'a'];
}

int distEdicionFuerzaB(const string &S1, const string &S2, int i, int j) {
    if (i == S1.length() && j == S2.length()) {
        return 0;
    }
    if (i == S1.length()) {
        return costo_ins(S2[j]) + distEdicionFuerzaB(S1, S2, i, j + 1);
    }
    if (j == S2.length()) {
        return costo_del(S1[i]) + distEdicionFuerzaB(S1, S2, i + 1, j);
    }

    int costoInsertar = costo_ins(S2[j]) + distEdicionFuerzaB(S1, S2, i, j + 1);
    int costoEliminar = costo_del(S1[i]) + distEdicionFuerzaB(S1, S2, i + 1, j);
    int costoSustituir = costo_sub(S1[i], S2[j]) + distEdicionFuerzaB(S1, S2, i + 1, j + 1);

    int costoTransponer = INT_MAX;
    if (i + 1 < S1.length() && j + 1 < S2.length() && S1[i] == S2[j + 1] && S1[i + 1] == S2[j]) {
        costoTransponer = costo_trans(S1[i], S1[i + 1]) + distEdicionFuerzaB(S1, S2, i + 2, j + 2);
    }

    return min({costoInsertar, costoEliminar, costoSustituir, costoTransponer});
}

int main() {
    costoFilas("cost_insert.txt", costo_insercion);
    costoFilas("cost_delete.txt", costo_eliminacion);
    costoMatriz("cost_replace.txt", costo_sustitucion);
    costoMatriz("cost_transpose.txt", costo_transposicion);

    ifstream archCasos("caso6FB.txt");
    string S1, S2;
    vector<int> tam;
    vector<double> tPromedio;
    int numRep = 1;

    while (archCasos >> S1 >> S2) {
        int longi = S1.length();
        tam.push_back(longi);
        cout << "longitud cadena: " << longi << endl; 

        double tiempoTotal = 0.0;
        for (int i = 0; i < numRep; ++i) {
            auto start = high_resolution_clock::now();
            int resultadodistEdicionFuerzaB = distEdicionFuerzaB(S1, S2, 0, 0);
            auto end = high_resolution_clock::now();
            std::chrono::duration<double> duration = end - start;
            cout << "Distancia " << S1 << " y " << S2 << ": " << resultadodistEdicionFuerzaB << endl;
            tiempoTotal += duration.count();
        }

        double tProm = tiempoTotal / numRep;
        tPromedio.push_back(tProm);
    }

    ofstream archCSV("resultados_distEdicionFuerzaB.csv");
    archCSV << "Cant Datos,T promedio [s]\n";
    for (size_t i = 0; i < tam.size(); ++i) {
        archCSV << tam[i] << "," << tPromedio[i] << "\n";
    }

    cout << "Resultados creados" << endl;

    return 0;
}
