#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

struct Conjunto {
    int id;
    int peso;
};

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

    int m = 0, n = 0, capacidad_maxima = 0;
    string linea;

    // 1. Parsear el encabezado de forma robusta buscando m=, n= y size=
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

    // 2. Leer los beneficios de los items saltando la linea explicativa
    while (getline(archivo, linea)) {
        if (linea.find("profit") != string::npos) break;
    }
    
    vector<int> beneficios_items(m);
    for (int i = 0; i < m; i++) {
        archivo >> beneficios_items[i];
    }
    
    // Limpiar el buffer de la ultima lectura antes de leer lineas completas
    string token_basura;
    getline(archivo, token_basura);

    // 3. Leer los pesos de los conjuntos saltando la linea explicativa
    while (getline(archivo, linea)) {
        if (linea.find("weight") != string::npos) break;
    }

    vector<Conjunto> pesos_conjuntos(n);
    for (int j = 0; j < n; j++) {
        pesos_conjuntos[j].id = j;
        archivo >> pesos_conjuntos[j].peso;
    }
    
    getline(archivo, token_basura);

    // 4. Leer la matriz de requisitos inmediatamente despues
    vector<vector<int>> matriz_requisitos(m, vector<int>(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            archivo >> matriz_requisitos[i][j];
        }
    }
    archivo.close();

    cout << "=== INSTANCIA CARGADA CORRECTAMENTE ===" << endl;
    cout << "Items (M): " << m << " | Conjuntos (N): " << n << " | Capacidad: " << capacidad_maxima << endl;
    cout << "=== EJECUTANDO LOGICA GREEDY (Por peso mas liviano) ===" << endl;

    vector<bool> conjuntos_activos(n, false);
    int peso_total = 0;

    vector<Conjunto> conjuntos_ordenados = pesos_conjuntos;
    sort(conjuntos_ordenados.begin(), conjuntos_ordenados.end(), compararPesos);

    for (int k = 0; k < n; k++) {
        int id_conjunto = conjuntos_ordenados[k].id;
        int peso_conjunto = conjuntos_ordenados[k].peso;

        if (peso_total + peso_conjunto <= capacidad_maxima) {
            conjuntos_activos[id_conjunto] = true;
            peso_total += peso_conjunto;
        }
    }

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
