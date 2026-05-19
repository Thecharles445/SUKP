#include <iostream>
#include <vector>

using namespace std;

struct Conjunto {
    int beneficio;
    vector<int> elementos_requeridos;
};

int main() {
    // 1. DEFINICION DE LA INSTANCIA
    vector<int> pesos_elementos;
    pesos_elementos.push_back(10);
    pesos_elementos.push_back(20);
    pesos_elementos.push_back(15);
    pesos_elementos.push_back(30);

    int total_elementos = pesos_elementos.size();

    vector<Conjunto> lista_conjuntos;

    Conjunto c0;
    c0.beneficio = 100;
    c0.elementos_requeridos.push_back(0);
    c0.elementos_requeridos.push_back(1);
    c0.elementos_requeridos.push_back(2);
    lista_conjuntos.push_back(c0);

    Conjunto c1;
    c1.beneficio = 50;
    c1.elementos_requeridos.push_back(2);
    c1.elementos_requeridos.push_back(3);
    lista_conjuntos.push_back(c1);

    int total_conjuntos = lista_conjuntos.size();

    
    // PRE-PROCESAMIENTO: Construccion del Mapa Inverso
    // Se ejecuta UNA SOLA VEZ antes de iniciar la metaheuristica
    
    vector<vector<int>> mapa_inverso(total_elementos);
    for (int j = 0; j < total_conjuntos; j++) {
        for (int k = 0; k < lista_conjuntos[j].elementos_requeridos.size(); k++) {
            int id_elemento = lista_conjuntos[j].elementos_requeridos[k];
            mapa_inverso[id_elemento].push_back(j); 
        }
    }

    // 2. SOLUCION A EVALUAR
    vector<int> solucion;
    solucion.push_back(1); 
    solucion.push_back(1); 
    solucion.push_back(1); 
    solucion.push_back(0);

    // =========================================================================
    // MOTOR DE EVALUACION OPTIMIZADO
    // =========================================================================
    int peso_total = 0;
    int beneficio_total = 0;

    // Inicializacion del vector de control de faltantes
    vector<int> faltantes(total_conjuntos);
    for (int j = 0; j < total_conjuntos; j++) {
        faltantes[j] = lista_conjuntos[j].elementos_requeridos.size();
    }

    // Evaluacion conjunta en un solo ciclo principal O(m)
    for (int i = 0; i < total_elementos; i++) {
        if (solucion[i] == 1) {
            peso_total += pesos_elementos[i]; // Costo lineal

            // Notificacion asincrona a los conjuntos dependientes
            for (int idx = 0; idx < mapa_inverso[i].size(); idx++) {
                int id_conjunto_afectado = mapa_inverso[i][idx];
                faltantes[id_conjunto_afectado]--;

                // Verificacion de satisfaccion en tiempo constante O(1)
                if (faltantes[id_conjunto_afectado] == 0) {
                    beneficio_total += lista_conjuntos[id_conjunto_afectado].beneficio;
                }
            }
        }
    }

    // 4. DESPLIEGUE DE RESULTADOS
    cout << "Peso total: " << peso_total << " kg" << endl;
    cout << "Beneficio total: $" << beneficio_total << endl;

    return 0;
}