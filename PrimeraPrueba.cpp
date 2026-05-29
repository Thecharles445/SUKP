#include <iostream>
#include <vector>

using namespace std;

int main() {
    // 1. Definir los pesos de los 3 conjuntos (Indice 0, 1 y 2)
    int pesos_conjuntos[3] = {10, 5, 7}; 
    
    // 2. Definir los beneficios de los 2 items (Indice 0 y 1)
    int beneficios_items[2] = {100, 40};
    
    // Capacidad maxima de la mochila
    int capacidad_maxima = 20;

    // 3. Elegir una combinacion de conjuntos manualmente
    // Queremos activar el Conjunto 0 y el Conjunto 1 (el 2 se queda en false)
    bool conjuntos_activos[3] = {true, true, false};

    // 4. Calcular el peso total de la combinacion elegida
    int peso_total = 0;
    for (int i = 0; i < 3; i++) {
        if (conjuntos_activos[i] == true) {
            peso_total += pesos_conjuntos[i]; // Suma 10 + 5
        }
    }

    cout << "Peso total de los conjuntos elegidos: " << peso_total << endl;

    // 5. Validar si la combinacion cabe en la mochila
    if (peso_total > capacidad_maxima) {
        cout << "Error: Supera la capacidad de la mochila." << endl;
        return 0; // Termina el programa si no cabe
    }

    // 6. Calcular el beneficio de los items desbloqueados
    int beneficio_total = 0;

    // Evaluar Item 0: Requiere Conjunto 0 Y Conjunto 1
    if (conjuntos_activos[0] == true && conjuntos_activos[1] == true) {
        beneficio_total += beneficios_items[0];
        cout << "¡Item 0 desbloqueado! Ganaste: " << beneficios_items[0] << endl;
    }

    // Evaluar Item 1: Requiere Conjunto 1 Y Conjunto 2
    if (conjuntos_activos[1] == true && conjuntos_activos[2] == true) {
        beneficio_total += beneficios_items[1];
        cout << "¡Item 1 desbloqueado! Ganaste: " << beneficios_items[1] << endl;
    }

    cout << "Beneficio total obtenido: " << beneficio_total << endl;

    return 0;
}