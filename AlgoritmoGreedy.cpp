#include <iostream>
#include <vector>

using namespace std;

int main() {
    int pesos_conjuntos[3] = {10, 5, 7};  
    int beneficios_items[2] = {100, 40};
    int capacidad_maxima = 20;

    // Empezamos con todos los conjuntos apagados
    bool conjuntos_activos[3] = {false, false, false};
    int peso_total = 0;

    cout << "=== EJECUTANDO LOGICA GREEDY (Por peso mas liviano) ===" << endl;

    
    // Paso 1: Elige el mas liviano de todos (Conjunto 1, peso 5)
    if (peso_total + pesos_conjuntos[1] <= capacidad_maxima) {
        conjuntos_activos[1] = true;
        peso_total += pesos_conjuntos[1];
        cout << "Greedy eligio activar Conjunto 1 (Peso: 5). Peso acumulado: " << peso_total << endl;
    }

    // Paso 2: Elige el siguiente mas liviano disponible (Conjunto 2, peso 7)
    if (peso_total + pesos_conjuntos[2] <= capacidad_maxima) {
        conjuntos_activos[2] = true;
        peso_total += pesos_conjuntos[2];
        cout << "Greedy eligio activar Conjunto 2 (Peso: 7). Peso acumulado: " << peso_total << endl;
    }

    // Paso 3: Intenta elegir el siguiente (Conjunto 0, peso 10)
    if (peso_total + pesos_conjuntos[0] <= capacidad_maxima) {
        conjuntos_activos[0] = true;
        peso_total += pesos_conjuntos[0];
    } else {
        cout << "Greedy descarto Conjunto 0 (Peso: 10) porque no cabe en la mochila." << endl;
    }

    int beneficio_total = 0;
    if (conjuntos_activos[0] == true && conjuntos_activos[1] == true) {
        beneficio_total += beneficios_items[0];
    }
    if (conjuntos_activos[1] == true && conjuntos_activos[2] == true) {
        beneficio_total += beneficios_items[1];
        cout << "¡Item 1 desbloqueado! Ganaste: " << beneficios_items[1] << endl;
    }

    cout << "Beneficio total obtenido por Greedy: " << beneficio_total << endl;
    return 0;
}
