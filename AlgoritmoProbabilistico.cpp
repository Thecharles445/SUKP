#include <iostream>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <chrono> 

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

    string archivo_instancia = "sukp_600_585_0.10_0.75.txt"; 
    ifstream archivo(archivo_instancia);
    
    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir el archivo." << endl;
        return 1;
    }

    int m = 0, n = 0, capacidad_maxima = 0;
    string linea;

    while (getline(archivo, linea)) {
        size_t pos_m = linea.find("m=");
        if (pos_m != string::npos) {
            m = stoi(linea.substr(pos_m + 2));
            
            size_t pos_n = linea.find("n=");
            if (pos_n != string::npos) {
                n = stoi(linea.substr(pos_n + 2));
            }
            
            size_t pos_size = linea.find("size=");
            if (pos_size != string::npos) {
                capacidad_maxima = stoi(linea.substr(pos_size + 5));
            }
            break; 
        }
    }

    if (m == 0 || n == 0 || capacidad_maxima == 0) {
        cerr << "Error al parsear el encabezado del archivo." << endl;
        return 1;
    }

    while (getline(archivo, linea)) {
        if (linea.find("profit") != string::npos) break;
    }
    
    vector<int> beneficios_items(m);
    for (int i = 0; i < m; i++) {
        archivo >> beneficios_items[i];
    }
    
    string token_basura;
    getline(archivo, token_basura);

    while (getline(archivo, linea)) {
        if (linea.find("weight") != string::npos) break;
    }

    vector<int> pesos_conjuntos(n);
    for (int j = 0; j < n; j++) {
        archivo >> pesos_conjuntos[j];
    }
    
    getline(archivo, token_basura);

    vector<vector<int>> matriz_requisitos(m, vector<int>(n));
    vector<int> conjuntos_por_item(m, 0);
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            archivo >> matriz_requisitos[i][j];
            if (matriz_requisitos[i][j] == 1) {
                conjuntos_por_item[i]++;
            }
        }
    }
    archivo.close();

    cout << "=== INSTANCIA CARGADA CORRECTAMENTE ===" << endl;
    cout << "Items (M): " << m << " | Conjuntos (N): " << n << " | Capacidad: " << capacidad_maxima << endl;
    cout << "=== EJECUTANDO ALGORITMO PROBABILISTICO MULTI-RONDA (RCL) ===" << endl;
    
    // =========================================================================
    // INICIO DE LA MEDICIÓN DE TIEMPO GLOBAL
    // =========================================================================
    auto inicio = chrono::high_resolution_clock::now();

    int mejor_beneficio_global = 0;
    int mejor_peso_global = 0;
    int total_intentos = 20; // 20 ejecuciones independientes para explorar el espacio combinatorio

    for (int intento = 1; intento <= total_intentos; intento++) {
        vector<bool> conjuntos_activos(n, false);
        int peso_actual = 0;

        // Estructura de control dinámica por ronda
        while (true) {
            vector<Candidato> candidatos;

            for (int j = 0; j < n; j++) {
                if (conjuntos_activos[j]) continue; 
                if (peso_actual + pesos_conjuntos[j] > capacidad_maxima) continue;

                double beneficio_estimado = 0;
                for (int i = 0; i < m; i++) {
                    if (matriz_requisitos[i][j] == 1) {
                        if (conjuntos_por_item[i] > 0) {
                            // Score estocástico basado en el aporte potencial fraccionario de cada conjunto
                            beneficio_estimado += (double)beneficios_items[i] / conjuntos_por_item[i];
                        }
                    }
                }
                
                double score_final = beneficio_estimado / pesos_conjuntos[j];
                candidatos.push_back({j, score_final});
            }

            if (candidatos.empty()) break;

            sort(candidatos.begin(), candidatos.end(), compararCandidatos);

            // K = 30 para maximizar la exploración estocástica y alejarse del Greedy rígido
            int k_actual = min(30, (int)candidatos.size()); 
            int idx_elegido = rand() % k_actual;
            int conjunto_seleccionado = candidatos[idx_elegido].idx;

            conjuntos_activos[conjunto_seleccionado] = true;
            peso_actual += pesos_conjuntos[conjunto_seleccionado];
        }

        // Evaluación final de la ronda actual
        int beneficio_total_intento = 0;
        for (int i = 0; i < m; i++) {
            bool item_completo = true;
            for (int j = 0; j < n; j++) {
                if (matriz_requisitos[i][j] == 1 && !conjuntos_activos[j]) {
                    item_completo = false;
                    break;
                }
            }
            if (item_completo) {
                beneficio_total_intento += beneficios_items[i];
            }
        }

        if (beneficio_total_intento > mejor_beneficio_global) {
            mejor_beneficio_global = beneficio_total_intento;
            mejor_peso_global = peso_actual;
        }
    }

    
    auto fin = chrono::high_resolution_clock::now();
    chrono::duration<double> tiempo_total = fin - inicio;

    cout << "\n=== RESULTADO FINAL DE LAS RONDAS PROBABILISTICAS ===" << endl;
    cout << "Mejor Peso acumulado final encontrado: " << mejor_peso_global << " / " << capacidad_maxima << endl;
    cout << "Mejor Beneficio total obtenido tras " << total_intentos << " intentos: " << mejor_beneficio_global << endl;
    cout << "Tiempo de ejecucion total del algoritmo: " << tiempo_total.count() << " segundos." << endl;

    return 0;
}
