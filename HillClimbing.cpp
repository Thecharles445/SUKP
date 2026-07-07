#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

int evaluarSolucion(const vector<bool>& conjuntos_activos, int m, int n,
                    const vector<int>& beneficios_items,
                    const vector<vector<int>>& matriz_requisitos) {
    int beneficio_total = 0;
    for (int i = 0; i < m; i++) {
        bool item_completo = true;
        for (int j = 0; j < n; j++) {
            if (matriz_requisitos[i][j] == 1 && !conjuntos_activos[j]) {
                item_completo = false;
                break;
            }
        }
        if (item_completo) {
            beneficio_total += beneficios_items[i];
        }
    }
    return beneficio_total;
}

int main() {
    srand(time(0));

    string archivo_instancia = "sukp_585_600_0.15_0.85.txt"; 
    ifstream archivo(archivo_instancia);
    
    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir el archivo." << endl;
        return 1;
    }

    int m = 0, n = 0, capacidad_maxima = 0;
    string linea;

    while (getline(archivo, linea)) {
        size_t pos_m = linea.find("m=");
        if (pos_m != string::npos) {
            m = stoi(linea.substr(pos_m + 2));
            
            size_t pos_n = linea.find("n=");
            if (pos_n != string::npos) {
                n = stoi(linea.substr(pos_n + 2));
            }
            
            size_t pos_size = linea.find("size=");
            if (pos_size != string::npos) {
                capacidad_maxima = stoi(linea.substr(pos_size + 5));
            }
            break; 
        }
    }

    if (m == 0 || n == 0 || capacidad_maxima == 0) {
        cerr << "Error al parsear el encabezado del archivo." << endl;
        return 1;
    }

    while (getline(archivo, linea)) {
        if (linea.find("profit") != string::npos) break;
    }
    
    vector<int> beneficios_items(m);
    for (int i = 0; i < m; i++) {
        archivo >> beneficios_items[i];
    }
    
    string token_basura;
    getline(archivo, token_basura);

    while (getline(archivo, linea)) {
        if (linea.find("weight") != string::npos) break;
    }

    vector<int> pesos_conjuntos(n);
    for (int j = 0; j < n; j++) {
        archivo >> pesos_conjuntos[j];
    }
    
    getline(archivo, token_basura);

    vector<vector<int>> matriz_requisitos(m, vector<int>(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            archivo >> matriz_requisitos[i][j];
        }
    }
    archivo.close();

    cout << "=== INSTANCIA CARGADA CORRECTAMENTE ===" << endl;
    cout << "Items (M): " << m << " | Conjuntos (N): " << n << " | Capacidad: " << capacidad_maxima << endl;
    cout << "=== EJECUTANDO BÚSQUEDA LOCAL: HILL CLIMBING ===" << endl;

    vector<bool> solucion_actual(n, false);
    int peso_actual = 0;
    
    for (int j = 0; j < n; j++) {
        if (peso_actual + pesos_conjuntos[j] <= capacidad_maxima) {
            solucion_actual[j] = true;
            peso_actual += pesos_conjuntos[j];
        }
    }

    int beneficio_actual = evaluarSolucion(solucion_actual, m, n, beneficios_items, matriz_requisitos);

    bool hubo_mejora = true;
    int iteracion = 0;

    while (hubo_mejora) {
        hubo_mejora = false;
        iteracion++;

        for (int activo = 0; activo < n && !hubo_mejora; activo++) {
            if (!solucion_actual[activo]) continue;

            for (int inactivo = 0; inactivo < n; inactivo++) {
                if (solucion_actual[inactivo]) continue;

                int nuevo_peso = peso_actual - pesos_conjuntos[activo] + pesos_conjuntos[inactivo];

                if (nuevo_peso > capacidad_maxima) continue;

                solucion_actual[activo] = false;
                solucion_actual[inactivo] = true;

                int nuevo_beneficio = evaluarSolucion(solucion_actual, m, n, beneficios_items, matriz_requisitos);

                if (nuevo_beneficio > beneficio_actual) {
                    beneficio_actual = nuevo_beneficio;
                    peso_actual = nuevo_peso;
                    hubo_mejora = true;
                    break; 
                }

                solucion_actual[activo] = true;
                solucion_actual[inactivo] = false;
            }
        }
    }

    cout << "\n=== RESULTADO FINAL DE HILL CLIMBING ===" << endl;
    cout << "Iteraciones de mejora realizadas: " << iteracion << endl;
    cout << "Peso consumido final: " << peso_actual << " / " << capacidad_maxima << endl;
    cout << "Beneficio máximo encontrado (Z): " << beneficio_actual << endl;

    return 0;
}
