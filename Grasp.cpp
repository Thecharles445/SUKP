#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Candidato {
    int idx;
    double score;
};

bool compararCandidatos(const Candidato& a, const Candidato& b) {
    return a.score > b.score;
}

int main() {
    srand(time(0));

    string archivo_instancia = "sukp_585_600_0.15_0.85.txt"; 
    ifstream archivo(archivo_instancia);
    if (!archivo.is_open()) return 1;

    int m = 0, n = 0, capacidad_maxima = 0;
    string linea;
    while (getline(archivo, linea)) {
        size_t pos_m = linea.find("m=");
        if (pos_m != string::npos) {
            m = stoi(linea.substr(pos_m + 2));
            size_t pos_n = linea.find("n=");
            if (pos_n != string::npos) n = stoi(linea.substr(pos_n + 2));
            size_t pos_size = linea.find("size=");
            if (pos_size != string::npos) capacidad_maxima = stoi(linea.substr(pos_size + 5));
            break; 
        }
    }

    while (getline(archivo, linea)) {
        if (linea.find("profit") != string::npos) break;
    }
    vector<int> beneficios_items(m);
    for (int i = 0; i < m; i++) archivo >> beneficios_items[i];
    
    string token_basura;
    getline(archivo, token_basura);
    while (getline(archivo, linea)) {
        if (linea.find("weight") != string::npos) break;
    }
    vector<int> pesos_conjuntos(n);
    for (int j = 0; j < n; j++) archivo >> pesos_conjuntos[j];
    
    getline(archivo, token_basura);
    vector<vector<int>> matriz_requisitos(m, vector<int>(n));
    vector<int> conjuntos_por_item(m, 0);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            archivo >> matriz_requisitos[i][j];
            if (matriz_requisitos[i][j] == 1) conjuntos_por_item[i]++;
        }
    }
    archivo.close();

    cout << "=== INSTANCIA CARGADA CORRECTAMENTE ===" << endl;
    cout << "=== EJECUTANDO MULTI-START GRASP CON BASE ALEATORIA ===" << endl;

    int mejor_beneficio_global = 0;
    int mejor_peso_global = 0;
    int intentos = 30; 

    for (int it = 0; it < intentos; it++) {
        vector<bool> conjuntos_activos(n, false);
        int peso_actual = 0;

        // FASE INDUCTORA DE CAOS: Forzamos los primeros 5 conjuntos totalmente al azar
        int forzados = 0;
        while (forzados < 5) {
            int r = rand() % n;
            if (!conjuntos_activos[r] && peso_actual + pesos_conjuntos[r] <= capacidad_maxima) {
                conjuntos_activos[r] = true;
                peso_actual += pesos_conjuntos[r];
                forzados++;
            }
        }

        // FASE CONSTRUCTIVA INTELIGENTE (RCL)
        while (true) {
            vector<Candidato> candidatos;
            for (int j = 0; j < n; j++) {
                if (conjuntos_activos[j] || peso_actual + pesos_conjuntos[j] > capacidad_maxima) continue;

                double beneficio_estimado = 0;
                for (int i = 0; i < m; i++) {
                    if (matriz_requisitos[i][j] == 1 && conjuntos_por_item[i] > 0) {
                        beneficio_estimado += (double)beneficios_items[i] / conjuntos_por_item[i];
                    }
                }
                double score = beneficio_estimado / pesos_conjuntos[j];
                candidatos.push_back({j, score});
            }

            if (candidatos.empty()) break;

            sort(candidatos.begin(), candidatos.end(), compararCandidatos);
            int k_actual = min(10, (int)candidatos.size()); 
            int elegido = candidatos[rand() % k_actual].idx;

            conjuntos_activos[elegido] = true;
            peso_actual += pesos_conjuntos[elegido];
        }

        int beneficio_intento = 0;
        for (int i = 0; i < m; i++) {
            bool completo = true;
            for (int j = 0; j < n; j++) {
                if (matriz_requisitos[i][j] == 1 && !conjuntos_activos[j]) {
                    completo = false;
                    break;
                }
            }
            if (completo) beneficio_intento += beneficios_items[i];
        }

        if (beneficio_intento > mejor_beneficio_global) {
            mejor_beneficio_global = beneficio_intento;
            mejor_peso_global = peso_actual;
        }
    }

    cout << "\n=== RESULTADO FINAL DE MULTI-START GRASP ===" << endl;
    cout << "Peso consumido final: " << mejor_peso_global << " / " << capacidad_maxima << endl;
    cout << "Beneficio total obtenido (Z): " << mejor_beneficio_global << endl;

    return 0;
}
