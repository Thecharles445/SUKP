#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// PARAMETROS GLOBALES
const int N = 3; 
const int M = 2; 
const int C = 20; 

int w[N] = {10, 5, 7}; 
int b[M] = {150, 200};
int matriz_requisitos[M][N] = {
    {1, 1, 0},
    {0, 1, 1}
};

int mejor_beneficio_global = 0;
vector<bool> mejor_combinacion_global(N, false);

// Funcion auxiliar para calcular el beneficio actual de una combinacion
int calcularBeneficio(const vector<bool>& activos) {
    int beneficio = 0;
    for (int i = 0; i < M; i++) {
        bool OK = true;
        for (int j = 0; j < N; j++) {
            if (matriz_requisitos[i][j] == 1 && !activos[j]) {
                OK = false;
                break;
            }
        }
        if (OK) beneficio += b[i];
    }
    return beneficio;
}

// FUNCION RECURSIVA 
void explorarArbol(int conjunto_actual, vector<bool>& combinacion_actual, int peso_acumulado) {
    // CASO BASE: Si ya decidimos sobre todos los conjuntos (llegamos a una hoja del arbol)
    if (conjunto_actual == N) {
        int beneficio_actual = calcularBeneficio(combinacion_actual);
        if (beneficio_actual > mejor_beneficio_global) {
            mejor_beneficio_global = beneficio_actual;
            mejor_combinacion_global = combinacion_actual;
        }
        return;
    }

    //  RAMA 1: NO ACTIVAR el conjunto_actual (Opctor = false)
    combinacion_actual[conjunto_actual] = false;
    explorarArbol(conjunto_actual + 1, combinacion_actual, peso_acumulado);

    //  RAMA 2: ACTIVAR el conjunto_actual (Opcion = true) 
    // Solo entramos a esta rama si el peso lo permite
    if (peso_acumulado + w[conjunto_actual] <= C) {
        combinacion_actual[conjunto_actual] = true;
        
        // Ramificamos hacia el siguiente nivel llevando el nuevo peso
        explorarArbol(conjunto_actual + 1, combinacion_actual, peso_acumulado + w[conjunto_actual]);
        
        // Volvemos a dejar en false para los siguientes caminos (Backtracking)
        combinacion_actual[conjunto_actual] = false; 
    }
}

int main() {
    vector<bool> combinacion_aux(N, false);
    
    cout << "=== EJECUTANDO BRANCH AND BOUND ===" << endl;
    // Arranca en el conjunto 0, con la lista vacia y peso 0
    explorarArbol(0, combinacion_aux, 0);

    // REPORTAR RESULTADOS
    cout << "\nSolucion Optima Exacta Encontrada:" << endl;
    cout << "Beneficio Maximo (Z): " << mejor_beneficio_global << endl;
    cout << "Conjuntos elegidos: ";
    for(int j = 0; j < N; j++) {
        if(mejor_combinacion_global[j]) cout << j << " ";
    }
    cout << endl;

    return 0;
}
