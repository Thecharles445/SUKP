#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

// Estructura para ordenar los candidatos en la RCL
struct Candidato {
    int idx;
    double score;
};

// Funcion de comparacion para ordenar la RCL descendentemente
bool compararCandidatos(const Candidato& a, const Candidato& b) {
    return a.score > b.score;
}

int main() {
    // Inicializar semilla aleatoria
    srand(time(0));

    // Datos base de tu problema
    const int N = 3; // Conjuntos
    const int M = 2; // Items
    int pesos_conjuntos[N] = {10, 5, 7}; 
    int beneficios_items[M] = {100, 40};
    int capacidad_maxima = 20;

    int matriz_requisitos[M][N] = {
        {1, 1, 0}, // Item 0: Conjunto 0 y 1
        {0, 1, 1}  // Item 1: Conjunto 1 y 2
    };

    
    double ALPHA = 0.7; // Balance: 0.7 marginal, 0.3 estatico
    int K = 2;          // Tamaño de la lista de mejores candidatos (RCL)

    // Estado del problema
    bool conjuntos_activos[N] = {false, false, false};
    int peso_actual = 0;

    cout << "=== EJECUTANDO ALGORITMO PROBABILISTICO (RCL) ===" << endl;

    // Bucle para activar conjuntos uno a uno
    for (int paso = 0; paso < N; paso++) {
        vector<Candidato> candidatos;

        // 1. Evaluar todos los conjuntos disponibles para calcular su Score
        for (int j = 0; j < N; j++) {
            if (conjuntos_activos[j]) continue; // Saltar si ya esta activo

            // Comprobar si cabe en la mochila
            if (peso_actual + pesos_conjuntos[j] > capacidad_maxima) continue;

            // Componente Marginal (M) dinamico
            int beneficio_marginal = 0;
            for (int i = 0; i < M; i++) {
                if (matriz_requisitos[i][j] == 1) {
                    beneficio_marginal += beneficios_items[i];
                }
            }
            double M_j = (double)beneficio_marginal / pesos_conjuntos[j];

            // Componente Estatico (P)  Basado en el beneficio total absoluto del item
            double P_j = 0;
            for (int i = 0; i < M; i++) {
                if (matriz_requisitos[i][j] == 1) {
                    P_j += beneficios_items[i]; // Estructura base
                }
            }
            

            // Formula
            double score_final = (ALPHA * M_j) + ((1.0 - ALPHA) * P_j);
            
            candidatos.push_back({j, score_final});
        }

        // Si no hay candidatos factibles que quepan, se termina el proceso
        if (candidatos.empty()) break;

        // 2. Ordenar candidatos por su score de forma descendente
        sort(candidatos.begin(), candidatos.end(), compararCandidatos);

        // Ajustar K en caso de que queden menos candidatos que el valor de K
        int k_actual = min(K, (int)candidatos.size());

        // 3. Seleccionar uno al azar dentro de los K mejores 
        int idx_elegido_en_rcl = rand() % k_actual;
        int conjunto_seleccionado = candidatos[idx_elegido_en_rcl].idx;

        // Activar el conjunto elegido de forma estocastica
        conjuntos_activos[conjunto_seleccionado] = true;
        peso_actual += pesos_conjuntos[conjunto_seleccionado];

        cout << "-> Activado Conjunto " << conjunto_seleccionado 
             << " (Elegido al azar del Top " << k_actual << " de la RCL)" 
             << " | Peso acumulado: " << peso_actual << "/" << capacidad_maxima << endl;
    }

    // --- EVALUACION DE RESULTADOS ---
    int beneficio_total = 0;
    cout << "\n=== RESULTADO FINAL DE LA RONDA PROBABILISTICA ===" << endl;
    if (conjuntos_activos[0] && conjuntos_activos[1]) beneficio_total += beneficios_items[0];
    if (conjuntos_activos[1] && conjuntos_activos[2]) beneficio_total += beneficios_items[1];

    cout << "Beneficio total obtenido: " << beneficio_total << endl;
    return 0;
}
