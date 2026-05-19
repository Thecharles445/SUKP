#include <iostream>

using namespace std;

int main() {
    // 1. Elementos Bases
    // Tenemos 4 elementos (ID: 0, 1, 2, 3)
    int peso_elemento0 = 10;
    int peso_elemento1 = 20;
    int peso_elemento2 = 15;
    int peso_elemento3 = 30;

    // 2. Solucion Planteada
    // 1 = La llevo, 0 = La dejo 
    int llevar_elemento0 = 1; // Si
    int llevar_elemento1 = 1; // Si
    int llevar_elemento2 = 1; // Si
    int llevar_elemento3 = 0; // No

    // 3. Conjuntos
    // Proyecto A: Da 100 de Beneficiosi tienes las herramientas 0, 1 Y 2.
    // Proyecto B: Da 50 de Beneficio si tienes las herramientas 2 Y 3.
    int premio_proyectoA = 100;
    int premio_proyectoB = 50;

    // 4. EL CALCULO y revisar Mochila
    int peso_total_mochila = 0;
    int beneficio_total = 0;

    // A. Calculamos el peso sumando solo lo que decidimos llevar
    if (llevar_elemento0 == 1) peso_total_mochila = peso_total_mochila + peso_elemento0;
    if (llevar_elemento1 == 1) peso_total_mochila = peso_total_mochila + peso_elemento1;
    if (llevar_elemento2 == 1) peso_total_mochila = peso_total_mochila + peso_elemento2;
    if (llevar_elemento3 == 1) peso_total_mochila = peso_total_mochila + peso_elemento3;

    // B. Revisamos si completamos el Proyecto A (Pide herramienta 0, 1 y 2)
    if (llevar_elemento0 == 1 && llevar_elemento1 == 1 && llevar_elemento2 == 1) {
        beneficio_total = beneficio_total + premio_proyectoA;
    }

    // C. Revisamos si completamos el Proyecto B (Pide herramienta 2 y 3)
    if (llevar_elemento2 == 1 && llevar_elemento3 == 1) {
        beneficio_total = beneficio_total + premio_proyectoB;
    }

    // 5. Mostrar Resultdos
    cout << "--- Resultados de la Mochila Basica ---" << endl;
    cout << "Peso total de lo que cargamos: " << peso_total_mochila << " kg" << endl;
    cout << "Beneficio total ganado: $" << beneficio_total << endl;

    return 0;
}