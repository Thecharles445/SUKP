#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Conjunto {
    int id;
    int peso;
};

// Función para ordenar conjuntos de menor a menor peso (Greedy Fast)
bool compararPesos(const Conjunto& a, const Conjunto& b) {
    return a.peso < b.peso;
}

int main() {
    string archivo_instancia = "sukp_585_600_0.15_0.85.txt"; 
    ifstream archivo(archivo_instancia);
    
    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir el archivo." << endl;
        return 1;
    }

    string token_m, token_n, token_knapsack, token_size, basura;
    int m, n, capacidad_maxima;

    archivo >> token_m >> token_n >> token_knapsack >> token_size >> capacidad_maxima;
    m = stoi(token_m.substr(2));
    n = stoi(token_n.substr(2));

    while (archivo >> basura) {
        if (basura == "items:" || basura == "items") break;
    }

    vector<int> beneficios_items(m);
    for (int i = 0; i < m; i++) {
        archivo >> beneficios_items[i];
    }

    while (archivo >> basura) {
        if (basura == "sets:" || basura == "sets") break;
    }

    vector<Conjunto> pesos_conjuntos(n);
    for (int j = 0; j < n; j++) {
        pesos_conjuntos[j].id = j;
        archivo >> pesos_conjuntos[j].peso;
    }

    vector<vector<int>> matriz_requisitos(m, vector<int>(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            archivo >> matriz_requisitos[i][j];
        }
    }
    archivo.close();

    cout << "=== EJECUTANDO LOGICA GREEDY (Por peso mas liviano) ===" << endl;

    vector<bool> conjuntos_activos(n, false);
    int peso_total = 0;

    // Ordenar una copia de los conjuntos para la estrategia greedy
    vector<Conjunto> conjuntos_ordenados = pesos_conjuntos;
    sort(conjuntos_ordenados.begin(), conjuntos_ordenados.end(), compararPesos);

    // Bucle de selección Greedy
    for (int k = 0; k < n; k++) {
        int id_conjunto = conjuntos_ordenados[k].id;
        int peso_conjunto = conjuntos_ordenados[k].peso;

        if (peso_total + peso_conjunto <= capacidad_maxima) {
            conjuntos_activos[id_conjunto] = true;
            peso_total += peso_conjunto;
        }
    }

    // Evaluación final del beneficio obtenido
    int beneficio_total = 0;
    for (int i = 0; i < m; i++) {
        bool item_completo = true;
        for (int j = 0; j < n; j++) {
            if (matriz_requisitos[i][j] == 1 && !conjuntos_activos[j]) {
                item_completo = false;
                break;
            }
        }
        if (item_completo) {
            beneficio_total += beneficios_items[i];
        }
    }

    cout << "Peso acumulado final: " << peso_total << " / " << capacidad_maxima << endl;
    cout << "Beneficio total obtenido por Greedy: " << beneficio_total << endl;

    return 0;
}
