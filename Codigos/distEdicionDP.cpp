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
        cerr << "Error " << arcName << endl;
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

int distEdicionDP(const string &S1, const string &S2) {
    int m = S1.length();
    int n = S2.length();
    vector<vector<int>> DP(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; i++) {
        DP[i][0] = DP[i - 1][0] + costo_del(S1[i - 1]);
    }
    for (int j = 1; j <= n; j++) {
        DP[0][j] = DP[0][j - 1] + costo_ins(S2[j - 1]);
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            int costoInsertar = costo_ins(S2[j - 1]) + DP[i][j - 1];
            int costoEliminar = costo_del(S1[i - 1]) + DP[i - 1][j];
            int costoSustituir = costo_sub(S1[i - 1], S2[j - 1]) + DP[i - 1][j - 1];

            DP[i][j] = min({costoInsertar, costoEliminar, costoSustituir});

            if (i > 1 && j > 1 && S1[i - 1] == S2[j - 2] && S1[i - 2] == S2[j - 1]) {
                int costoTransponer = costo_trans(S1[i - 2], S1[i - 1]) + DP[i - 2][j - 2];
                DP[i][j] = min(DP[i][j], costoTransponer);
            }
        }
    }

    return DP[m][n];
}

int main() {
    costoFilas("cost_insert.txt", costo_insercion);
    costoFilas("cost_delete.txt", costo_eliminacion);
    costoMatriz("cost_replace.txt", costo_sustitucion);
    costoMatriz("cost_transpose.txt", costo_transposicion);

    ifstream archCasos("caso6DP.txt");
    string S1, S2;
    vector<int> tam;
    vector<double> tPromedio;
    int numRep = 3; 

    while (archCasos >> S1 >> S2) {
        int longi = S1.length();
        tam.push_back(longi);
 
        int resultdistEdicionDP = distEdicionDP(S1, S2);
        cout << "Distancia " << S1 << " y " << S2 << ": " << resultdistEdicionDP << endl;
        double tTotal = 0.0;
        for (int i = 0; i < numRep; ++i) {
            auto start = high_resolution_clock::now();
            distEdicionDP(S1, S2); 
            auto end = high_resolution_clock::now();
            std::chrono::duration<double> duration = end - start;
            tTotal += duration.count();
        }

        double tiempoPromedio = tTotal / numRep;
        tPromedio.push_back(tiempoPromedio);
    }

    ofstream CSV("resultados_distEdicionDP.csv");
    CSV << "Cant Datos,T promedio [s]\n";
    for (size_t i = 0; i < tam.size(); ++i) {
        CSV << tam[i] << "," << tPromedio[i] << "\n";
    }

    cout << "Resultados creados" << endl;

    return 0;
}
