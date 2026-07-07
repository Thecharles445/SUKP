# Práctica 1: Resolución del Set-Union Knapsack Problem (SUKP)
**Autor:** [Carlos Andrés Valenzuela Olivares]

---

## Descripción del Proyecto
Este repositorio contiene la implementación de la **Práctica 1**, enfocada en resolver el **Problema de la Mochila de la Unión de Conjuntos (SUKP)**, un problema de optimización combinatoria de clase NP-hard.

A diferencia del enfoque tradicional de la mochila, esta solución se aborda desde la **perspectiva de selección de combinaciones de conjuntos**.

### El Enfoque Utilizado
* **Los Conjuntos representan el Peso:** La mochila tiene una capacidad máxima. Activamos combinaciones de conjuntos base, donde cada conjunto tiene un peso único y fijo.
* **Los Ítems representan el Beneficio:** Cada ítem otorga un valor monetario o beneficio, pero solo se "desbloquea" y se suma a la ganancia si **todos** los conjuntos que requiere han sido activados en la combinación actual.

Este modelo optimiza la búsqueda explotando las sinergias y los "descuentos en peso" cuando múltiples ítems comparten los mismos conjuntos base.

Para resolver el problema del **SUKP (Set Union Knapsack Problem)** bajo el enfoque basado en conjuntos, se desarrollaron e implementaron estrategias algorítmicas con diferentes filosofías de diseño:

---

### 1. Enfoque Exacto: Bitmask DP (Programación Dinámica)
Este algoritmo busca encontrar la **solución óptima absoluta (máximo global)** mediante una búsqueda exhaustiva utilizando operaciones a nivel de bits.

* **¿Cómo funciona?** Representa la activación/desactivación de los $N$ conjuntos como un único número entero (una "máscara de bits"). Un bucle evalúa matemáticamente las $2^N$ combinaciones posibles en binario (donde `1` es activo y `0` es inactivo).
* **Optimización aplicada (Poda):** Para evitar retrasos en el procesador, el algoritmo calcula el peso en tiempo real mediante el operador `&`. Si una combinación rompe la restricción de capacidad, es descartada inmediatamente antes de calcular sus beneficios.
* **Inviabilidad en Instancias Reales:** Al tener una complejidad exponencial $\mathcal{O}(2^N)$, sufre de **explosión combinatoria**. Para una instancia real de $N=600$ conjuntos, requeriría evaluar $2^{600}$ estados (un número astronómico inviable en tiempo humano), por lo que se descartó su uso práctico para este tamaño de problema.

---

### 2. Enfoque Heurístico: Greedy Inteligente (Algoritmo Voraz)
Este algoritmo prioriza la **velocidad de ejecución**, construyendo una solución de alta calidad paso a paso sin necesidad de explorar todo el universo de combinaciones.

* **¿Cómo funciona?** En lugar de elegir a ciegas por el peso más bajo o el beneficio más alto, el algoritmo utiliza el concept económico de **Densidad de Beneficio**. En cada iteración calcula un ratio dinámico para cada conjunto disponible:
  
  $$\text{Prioridad} = \frac{\text{Suma de beneficios de ítems ayudados}}{\text{Peso del conjunto}}$$

* **Sinergias Dinámicas:** La puntuación se recalcula en cada paso. Al activar un conjunto, los ítems compartidos que quedan "a mitad de requisitos" aumentan la prioridad de los conjuntos restantes, forzando al algoritmo a cerrar "combos" de alto beneficio.
* **Complejidad:** Polinomial $\mathcal{O}(N^2 \cdot M)$. Ultra rápido y escalable para instancias masivas con miles de datos en la vida real.

---

### Comparativa de Enfoques Iniciales

| Característica | Bitmask DP | Greedy Inteligente |
| :--- | :--- | :--- |
| **Tipo de Solución** | **Exacta** (Garantiza el 100% de optimización) | **Aproximada** (Buena calidad en milisegundos) |
| **Manejo de Combos** | Perfecto (Revisa todas las sinergias) | Heurístico (Sigue la densidad del ratio) |
| **Escalabilidad** | Limitada (Sufre con más de 25 conjuntos) | Alta (Soporta miles de registros) |
| **Uso de Memoria** | Mínimo (Usa enteros como banderas de bits) | Bajo (Usa vectores dinámicos) |

---

### 3. Enfoque Exacto: Árbol Binario (Ramificación y Acotación)
Este algoritmo modela el espacio de soluciones como un **Árbol de Decisión Binario** recursivo. En cada nivel del árbol, toma una bifurcación: la rama izquierda asume que el conjunto se apaga (`false`) y la rama derecha que se enciende (`true`).

* **Optimización aplicada (Poda por Peso):** Calcula el peso acumulado antes de abrir una rama. Si supera la capacidad de la mochila, la rama completa se corta (poda), ahorrando operaciones recursivas.
* **Inviabilidad en Instancias Reales:** Aunque reduce búsquedas mediante podas, en el peor de los casos mantiene su naturaleza exponencial $\mathcal{O}(2^N)$. Ante los 600 conjuntos de la instancia real, la profundidad del árbol desborda la pila de recursión (Stack Overflow) y congela el procesador, haciéndolo inviable frente a métodos heurísticos.

---

### 4. Enfoque Metaheurístico: Algoritmo Probabilístico con Lista Restringida de Candidatos (RCL)
Este algoritmo introduce **aleatoriedad controlada** (estocasticidad) sobre el enfoque basado en conjuntos para romper la rigidez del Greedy determinista, permitiendo explorar caminos alternativos en el espacio de soluciones y escapar de óptimos locales.

* **¿Cómo funciona?** Evalúa los conjuntos disponibles mediante una **Métrica de Selección Híbrida (Score)** regulada por un parámetro $\alpha$:
  
  $$\text{score}(j) = \alpha \cdot M(j) + (1 - \alpha) \cdot P(j)$$

  Donde $M(j)$ representa el beneficio marginal dinámico y $P(j)$ es el potencial estático absoluto del conjunto. 
* **La Lista Restringida de Candidatos (RCL):** Tras calcular los puntajes, aísla los $K$ mejores componentes en una lista selecta (RCL) y **elige un conjunto al azar dentro de este grupo (Top-$K$)** para ingresarlo a la mochila. Al ejecutarse múltiples veces, rompe la miopía del Greedy y descubre combinaciones altamente eficientes.
* **Complejidad:** Polinomial $\mathcal{O}(N^2 \cdot M)$ por cada iteración.

---

### 5. Enfoque Metaheurístico: GRASP con Reinicialización Aleatoria (Multi-Start)
Para romper con el estancamiento en óptimos locales planos característicos de las instancias grandes del SUKP, se implementó una metaheurística GRASP (*Greedy Randomized Adaptive Search Procedure*) basada en inicios múltiples.

* **¿Cómo funciona?** El algoritmo opera en dos fases repetitivas. Primero, ejecuta una **Fase Inductora de Caos** donde selecciona las primeras activaciones de conjuntos de manera 100% aleatoria. Segundo, aplica una **Fase Constructiva Inteligente** adaptativa (RCL) para rellenar la capacidad restante de la mochila.
* **Ventaja Principal:** Al forzar bases iniciales caóticas y distintas en cada iteración, obliga al programa a explorar "valles" y regiones completamente diferentes del espacio de soluciones que el criterio voraz tradicional ignoraría, permitiendo obtener configuraciones de peso y beneficios dinámicos alternativos.

---

### 6. Enfoque de Búsqueda Local: Hill Climbing (Ascenso de Colinas)
Este algoritmo implementa una estrategia de optimización iterativa enfocada en refinar y mejorar una solución ya existente a través de exploraciones en su vecindario inmediato.

* **¿Cómo funciona?** Comienza a partir de una solución constructiva base y entra en un bucle adaptativo de **operaciones de intercambio (Moves / Swaps)**. En cada paso, el algoritmo evalúa apagar un conjunto actualmente activo y encender uno inactivo.
* **Criterio de Aceptación:** El intercambio se consolida únicamente si la nueva configuración respeta la capacidad máxima de la mochila y genera un incremento estricto en el beneficio total ($Z$). El algoritmo se detiene inmediatamente cuando no encuentra ningún vecino capaz de mejorar la colina actual, garantizando un óptimo local de manera rápida y eficiente.

---

## Características
* **Estructura Invertida:** Mapeo de relaciones Conjunto ➔ Ítems para una evaluación rápida.
* **Cálculo Dinámico de Eficiencia:** Evaluación de combinaciones basada en la relación `Beneficio Nuevo / Peso del Conjunto`.
* **Validación de Restricciones:** Control estricto de la capacidad máxima de la mochila.

---

## Sobre el Autor

* **Nombre:** Carlos Andrés Valenzuela Olivares
* **Institución:** Universidad Diego Portales (UDP)
* **Académico:** Estudiante de 4to año de Ingeniería Civil en Informática y Telecomunicaciones
* **Áreas de Especialización e Interés:** Metaheurísticas de optimización combinatoria, análisis algorítmico, estructuras de datos avanzadas y desarrollo de software Fullstack.
