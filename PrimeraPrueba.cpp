#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

// Estructura para representar un conjunto (item con beneficio)
struct Conjunto {
    int id;
    int beneficio;
    vector<int> elementos_requeridos;
};

int main() {
    // 1. Configuracion inicial
    // Pesos de los elementos base (m = 5)
    vector<int> pesos_elementos = {10, 20, 15, 30, 25};
    int capacidad_maxima = 50;

    // Definicion de conjuntos (n = 3)
    vector<Conjunto> lista_conjuntos = {
        {0, 100, {0, 1, 2}}, // Requiere elementos 0, 1 y 2
        {1, 50,  {2, 3}},    // Requiere elementos 2 y 3
        {2, 80,  {0, 4}}     // Requiere elementos 0 y 4
    };

    // 2. Pre-procesamiento: Creacion del Mapeo Inverso (Elemento -> Conjuntos)
    // Esto permite una complejidad O(grado del elemento) en lugar de O(n*m)
    vector<vector<int>> elemento_a_conjuntos(pesos_elementos.size());
    for (const auto& conj : lista_conjuntos) {
        for (int elem_id : conj.elementos_requeridos) {
            elemento_a_conjuntos[elem_id].push_back(conj.id);
        }
    }

    // 3. Representacion de la solucion (Variable de decision: Elementos)
    // Ejemplo: Activamos los elementos 0, 1 y 2
    vector<int> solucion_elementos = {1, 1, 1, 0, 0}; 

    // 4. Evaluacion Eficiente (Fitness)
    int peso_total = 0;
    int beneficio_total = 0;
    
    // Usamos un contador para saber cuantos elementos le faltan a cada conjunto
    vector<int> faltantes_por_conjunto;
    for (const auto& conj : lista_conjuntos) {
        faltantes_por_conjunto.push_back(conj.elementos_requeridos.size());
    }

    // Procesamos solo los elementos activos
    for (int i = 0; i < solucion_elementos.size(); ++i) {
        if (solucion_elementos[i] == 1) {
            peso_total += pesos_elementos[i]; // Calculo de peso lineal O(m)

            // Notificamos a los conjuntos que contienen este elemento
            for (int conj_id : elemento_a_conjuntos[i]) {
                faltantes_por_conjunto[conj_id]--;
                
                // Si el contador llega a 0, el conjunto esta completo
                if (faltantes_por_conjunto[conj_id] == 0) {
                    beneficio_total += lista_conjuntos[conj_id].beneficio;
                }
            }
        }
    }

    // 5. Resultados
    cout << "--- Resultado de la Evaluacion ---" << endl;
    cout << "Peso Total: " << peso_total << " / " << capacidad_maxima << endl;
    if (peso_total <= capacidad_maxima) {
        cout << "Beneficio Total Obtenido: " << beneficio_total << endl;
        cout << "Estado: FACTIBLE" << endl;
    } else {
        cout << "Estado: NO FACTIBLE (Excede capacidad)" << endl;
    }

    return 0;
}
