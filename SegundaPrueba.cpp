#include <iostream>
#include <vector>

using namespace std;

int main() {
    // 1. Pesos de las herramientas (Conjuntos: Indice 0, 1 y 2)
    int peso_herramientas[3] = {8, 6, 12}; 
    
    // 2. Beneficios de los proyectos (Items: Indice 0 y 1)
    int beneficio_proyectos[2] = {150, 200};
    
    // Limite de espacio en el disco duro (Capacidad de la mochila)
    int espacio_maximo = 20;

    // 3. NUESTRA DECISION: ¿Que herramientas vamos a activar?
    // Decidimos activar la Herramienta 1 (Servidor) y la Herramienta 2 (IA).
    // Dejamos la Herramienta 0 (Base de datos) apagada.
    bool herramientas_activas[3] = {false, true, true};

    // 4. PASO LOGICO 1: Sumar el peso de lo que activamos
    int espacio_utilizado = 0;
    for (int i = 0; i < 3; i++) {
        if (herramientas_activas[i] == true) {
            espacio_utilizado += peso_herramientas[i]; // Suma 6 + 12 = 18 GB
        }
    }

    cout << "Espacio total utilizado en disco: " << espacio_utilizado << " GB" << endl;

    // 5. PASO LOGICO 2: Validar si cabe en nuestro disco duro
    if (espacio_utilizado > espacio_maximo) {
        cout << "Error: No hay suficiente espacio en el disco duro." << endl;
        return 0; // Detiene el programa porque la combinacion no es valida
    }

    // 6. PASO LOGICO 3 y 4: Escanear que proyectos se desbloquean y sumar ganancias
    int ganancias_totales = 0;

    // Evaluar Proyecto 0: Requiere Herramienta 0 Y Herramienta 1
    if (herramientas_activas[0] == true && herramientas_activas[1] == true) {
        ganancias_totales += beneficio_proyectos[0];
        cout << "Proyecto 0 (Tienda Online) lanzado. Ganancia: +" << beneficio_proyectos[0] << endl;
    } else {
        cout << "Proyecto 0 no se pudo lanzar (Faltan herramientas)." << endl;
    }

    // Evaluar Proyecto 1: Requiere Herramienta 1 Y Herramienta 2
    if (herramientas_activas[1] == true && herramientas_activas[2] == true) {
        ganancias_totales += beneficio_proyectos[1];
        cout << "Proyecto 1 (Chatbot Avanzado) lanzado. Ganancia: +" << beneficio_proyectos[1] << endl;
    } else {
        cout << "Proyecto 1 no se pudo lanzar (Faltan herramientas)." << endl;
    }

    // 7. Resultado final de la combinacion elegida
    cout << "Ganancia total de esta combinacion: $" << ganancias_totales << endl;

    return 0;
}