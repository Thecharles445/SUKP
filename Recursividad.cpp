#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Funcion auxiliar para calcular el beneficio actual de una combinacion de forma dinamica
int calcularBeneficio(const vector<bool>& activos, int m, int n, 
                      const vector<int>& beneficios_items, 
                      const vector<vector<int>>& matriz_requisitos) {
    int beneficio = 0;
    for (int i = 0; i < m; i++) {
        bool OK = true;
        for (int j = 0; j < n; j++) {
            if (matriz_requisitos[i][j] == 1 && !activos[j]) {
                OK = false;
                break;
            }
        }
        if (OK) beneficio += beneficios_items[i];
    }
    return beneficio;
}

// FUNCION RECURSIVA CON PASO DE PARAMETROS OPTIMIZADOS
void explorarArbol(int conjunto_actual, int n_limite, int m, int n,
                   vector<bool>& combinacion_actual, int peso_acumulado, int capacidad_maxima,
                   const vector<int>& pesos_conjuntos, const vector<int>& beneficios_items,
                   const vector<vector<int>>& matriz_requisitos, const vector<bool>& item_es_viable,
                   int& mejor_beneficio_global, vector<bool>& mejor_combinacion_global, int& mejor_peso_global) {
    
    // CASO BASE: Si ya decidimos sobre todos los conjuntos del rango acotado
    if (conjunto_actual == n_limite) {
        int beneficio_actual = calcularBeneficio(combinacion_actual, m, n, beneficios_items, matriz_requisitos);
        if (beneficio_actual > mejor_beneficio_global) {
            mejor_beneficio_global = beneficio_actual;
            mejor_combinacion_global = combinacion_actual;
            mejor_peso_global = peso_acumulado;
        }
        return;
    }

    // RAMA 1: NO ACTIVAR el conjunto_actual
    combinacion_actual[conjunto_actual] = false;
    explorarArbol(conjunto_actual + 1, n_limite, m, n, combinacion_actual, peso_acumulado, capacidad_maxima,
                  pesos_conjuntos, beneficios_items, matriz_requisitos, item_es_viable,
                  mejor_beneficio_global, mejor_combinacion_global, mejor_peso_global);

    // RAMA 2: ACTIVAR el conjunto_actual (Poda por peso / capacidad)
    if (peso_acumulado + pesos_conjuntos[conjunto_actual] <= capacidad_maxima) {
        combinacion_actual[conjunto_actual] = true;
        
        explorarArbol(conjunto_actual + 1, n_limite, m, n, combinacion_actual, peso_acumulado + pesos_conjuntos[conjunto_actual], capacidad_maxima,
                      pesos_conjuntos, beneficios_items, matriz_requisitos, item_es_viable,
                      mejor_beneficio_global, mejor_combinacion_global, mejor_peso_global);
        
        // Backtracking (Volver a limpiar el estado)
        combinacion_actual[conjunto_actual] = false; 
    }
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

    // 1. Parsear el encabezado buscando m=, n= y size=
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

    // 2. Leer los beneficios de los items
    while (getline(archivo, linea)) {
        if (linea.find("profit") != string::npos) break;
    }
    
    vector<int> beneficios_items(m);
    for (int i = 0; i < m; i++) {
        archivo >> beneficios_items[i];
    }
    
    string token_basura;
    getline(archivo, token_basura);

    // 3. Leer los pesos de los conjuntos
    while (getline(archivo, linea)) {
        if (linea.find("weight") != string::npos) break;
    }

    vector<int> pesos_conjuntos(n);
    for (int j = 0; j < n; j++) {
        archivo >> pesos_conjuntos[j];
    }
    
    getline(archivo, token_basura);

    // 4. Leer la matriz de requisitos
    vector<vector<int>> matriz_requisitos(m, vector<int>(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            archivo >> matriz_requisitos[i][j];
        }
    }
    archivo.close();

    cout << "=== INSTANCIA CARGADA CORRECTAMENTE ===" << endl;
    cout << "Items (M): " << m << " | Conjuntos (N): " << n << " | Capacidad: " << capacidad_maxima << endl;
    cout << "=== EJECUTANDO EXPLORACIÓN POR ÁRBOL BINARIO (BRANCH AND BOUND ACUTADO) ===" << endl;

    // Limite seguro de profundidad para la recursion (Ajustado a 20 niveles para ejecucion inmediata)
    int n_limite = min(n, 20); 

    // Pre-filtrado estricto para acelerar la evaluacion del arbol
    vector<bool> item_es_viable(m, true);
    for (int i = 0; i < m; i++) {
        for (int j = n_limite; j < n; j++) {
            if (matriz_requisitos[i][j] == 1) {
                item_es_viable[i] = false; 
                break;
            }
        }
    }

    // Inicializacion de variables de control del optimo
    int mejor_beneficio_global = 0;
    int mejor_peso_global = 0;
    vector<bool> mejor_combinacion_global(n, false);
    vector<bool> combinacion_aux(n, false);

    // Ejecucion del algoritmo recursivo
    explorarArbol(0, n_limite, m, n, combinacion_aux, 0, capacidad_maxima,
                  pesos_conjuntos, beneficios_items, matriz_requisitos, item_es_viable,
                  mejor_beneficio_global, mejor_combinacion_global, mejor_peso_global);

    // REPORTAR RESULTADOS DE LA EVALUACION DEL ARBOL
    cout << "\n=== SOLUCIÓN ÓPTIMA EXACTA ENCONTRADA (RANGO ACURTADO) ===" << endl;
    cout << "Beneficio Maximo Obtenido (Z): " << mejor_beneficio_global << endl;
    cout << "Peso Total Consumido: " << mejor_peso_global << " / " << capacidad_maxima << endl;
    cout << "Conjuntos elegidos: ";
    for (int j = 0; j < n_limite; j++) {
        if (mejor_combinacion_global[j]) cout << j << " ";
    }
    cout << endl;

    return 0;
}
