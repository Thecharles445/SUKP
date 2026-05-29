#include <iostream>

using namespace std;

int main() {
    // PARAMETROS DEL MODELO
    const int N = 3; // Numero de conjuntos (Elementos base)
    const int M = 2; // Numero de items
    const int C = 20; // Capacidad maxima de la mochila

    // Vectores de parametros: Pesos (w) y Beneficios (b)
    int w[N] = {10, 5, 7}; 
    int b[M] = {150, 200};

    // Matriz de Incidencia (Relacion de pertenencia S_i)
    // matriz_requisitos[i][j] = 1 significa que el Item i requiere del Conjunto j
    int matriz_requisitos[M][N] = {
        {1, 1, 0}, // Item 0 requiere: Conjunto 0 y Conjunto 1
        {0, 1, 1}  // Item 1 requiere: Conjunto 1 y Conjunto 2
    };

    // VARIABLES DE DECISION
    // Tu vector de seleccion de conjuntos (Variables x_j)
    // Decidimos activar el conjunto 1 y el conjunto 2 (x_0=0, x_1=1, x_2=1)
    int x[N] = {0, 1, 1}; 
    
    // Vector de items activados (Variables y_i)
    int y[M] = {0, 0}; 


    // 1. Evaluar Restriccion de Capacidad: Sumatoria de (w_j * x_j)
    int peso_total = 0;
    for (int j = 0; j < N; j++) {
        peso_total += w[j] * x[j];
    }

    cout << "--- Evaluacion de Restricciones ---" << endl;
    cout << "Sumatoria(w_j * x_j) = " << peso_total << " <= " << C << endl;

    if (peso_total > C) {
        cout << "Resultado: Infaustable. Rompe la restriccion de capacidad." << endl;
        return 0;
    }

    // 2. Evaluar Restriccion Logica y determinar Variables y_i
    // y_i sera 1 si y solo si x_j = 1 para todo j donde matriz_requisitos[i][j] == 1
    for (int i = 0; i < M; i++) {
        bool cumple_restriccion = true;
        
        for (int j = 0; j < N; j++) {
            // Si el item i requiere el conjunto j, se debe cumplir que y_i <= x_j
            if (matriz_requisitos[i][j] == 1) {
                if (x[j] == 0) {
                    cumple_restriccion = false; // x_j es 0, por lo que y_i se fuerza a 0
                    break;
                }
            }
        }
        
        if (cumple_restriccion) {
            y[i] = 1; // El item se activa satisfactoriamente
        }
    }

    // 3. Evaluar Funcion Objetivo: Maximizacion de Sumatoria(b_i * y_i)
    int Z = 0;
    cout << "\n--- Estado de las Variables de Item (y_i) ---" << endl;
    for (int i = 0; i < M; i++) {
        cout << "y_" << i << " = " << y[i] << endl;
        Z += b[i] * y[i];
    }

    cout << "\nValor de la Funcion Objetivo Z = " << Z << endl;

    return 0;
}