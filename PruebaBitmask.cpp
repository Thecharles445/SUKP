#include <iostream>
#include <vector>

using namespace std;

int main() {
    // mismos datos de la primera prueba
    const int N = 3; // Numero de conjuntos
    const int M = 2; // Numero de items
    const int C = 20; // Capacidad maxima de la mochila

    int w[N] = {10, 5, 7}; 
    int b[M] = {150, 200};

    int matriz_requisitos[M][N] = {
        {1, 1, 0}, // Item 0 requiere: Conjunto 0 y 1
        {0, 1, 1}  // Item 1 requiere: Conjunto 1 y 2
    };

    // VARIABLES 
    int mejor_beneficio = 0;
    int mejor_mask = 0;
    int peso_de_la_mejor = 0;

    // El numero total de combinaciones posibles es 2^N (Para N=3, es 8)
    int total_combinaciones = (1 << N);

    cout << "=== EVALUANDO TODAS LAS COMBINACIONES CON BITMASK ===" << endl;

    // Bucle principal: recorre de 0 a 7 (las 8 combinaciones posibles)
    for (int mask = 0; mask < total_combinaciones; mask++) {
        
        // 1. Calcular el peso total de la mascara actual
        int peso_actual = 0;
        for (int j = 0; j < N; j++) {
            // Evaluacion de bits: verifica si el bit en la posicion j esta encendido (1)
            if ((mask & (1 << j)) != 0) {
                peso_actual += w[j];
            }
        }

        // Si esta combinacion de conjuntos supera la capacidad, es invalida
        if (peso_actual > C) {
            continue; // Salta a la siguiente combinacion
        }

        // 2. Determinar que items se desbloquean con esta mascara
        int beneficio_actual = 0;
        for (int i = 0; i < M; i++) {
            bool totalmente_activo = true;
            for (int j = 0; j < N; j++) {
                // Si el item requiere el conjunto j, pero el bit j en la mask es 0
                if (matriz_requisitos[i][j] == 1 && (mask & (1 << j)) == 0) {
                    totalmente_activo = false;
                    break;
                }
            }
            // Si cumple todos los requisitos binarios, se suma el beneficio
            if (totalmente_activo) {
                beneficio_actual += b[i];
            }
        }

        // Imprimir el estado de la combinacion actual
        cout << "Mascara " << mask << " (Binario: ";
        for (int j = N - 1; j >= 0; j--) {
            cout << ((mask & (1 << j)) ? "1" : "0");
        }
        cout << ") -> Peso: " << peso_actual << " | Beneficio: " << beneficio_actual << endl;

        // 3. Guardar si es la mejor combinacion vista hasta ahora
        if (beneficio_actual > mejor_beneficio) {
            mejor_beneficio = beneficio_actual;
            mejor_mask = mask;
            peso_de_la_mejor = peso_actual;
        }
    }

    cout << "Mejor Mascara (Decimal): " << mejor_mask << endl;
    cout << "Mejor Combinacion (Binario): ";
    for (int j = N - 1; j >= 0; j--) {
        cout << ((mejor_mask & (1 << j)) ? "1" : "0");
    }
    cout << "\nConjuntos a activar: ";
    for (int j = 0; j < N; j++) {
        if (mejor_mask & (1 << j)) {
            cout << j << " ";
        }
    }
    cout << "\nPeso Optimo Consumido: " << peso_de_la_mejor << " <= " << C << endl;
    cout << "Beneficio Maximo Obtenido (Z): " << mejor_beneficio << endl;

    return 0;
}