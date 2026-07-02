# Práctica 1: Resolución del Set-Union Knapsack Problem (SUKP)
**Autor:** [Carlos Andrés Valenzuela Olivares]

---

##  Descripción del Proyecto
Este repositorio contiene la implementación de la **Práctica 1**, enfocada en resolver el **Problema de la Mochila de la Unión de Conjuntos (SUKP)**, un problema de optimización combinatoria de clase NP-hard.

A diferencia del enfoque tradicional de la mochila, esta solución se aborda desde la **perspectiva de selección de combinaciones de conjuntos**.

### El Enfoque Utilizado
* **Los Conjuntos representan el Peso:** La mochila tiene una capacidad máxima. Activamos combinaciones de conjuntos base, donde cada conjunto tiene un peso único y fijo.
* **Los Ítems representan el Beneficio:** Cada ítem otorga un valor monetario o beneficio, pero solo se "desbloquea" y se suma a la ganancia si **todos** los conjuntos que requiere han sido activados en la combinación actual.

Este modelo optimiza la búsqueda explotando las sinergias y los "descuentos en peso" cuando múltiples ítems comparten los mismos conjuntos base.

Para resolver el problema del **SUKP (Set Union Knapsack Problem)** bajo el enfoque basado en conjuntos, se desarrollaron e implementaron dos estrategias algorítmicas con filosofías de diseño opuestas:

---

### 1. Enfoque Exacto: Bitmask DP (Programación Dinámica)
Este algoritmo garantiza encontrar la **solución óptima absoluta (máximo global)** mediante una búsqueda exhaustiva inteligente utilizando operaciones a nivel de bits.

* **¿Cómo funciona?** Representa la activación/desactivación de los $N$ conjuntos como un único número entero (una "máscara de bits"). Un bucle evalúa matemáticamente las $2^N$ combinaciones posibles en binario (donde `1` es activo y `0` es inactivo).
* **Optimización aplicada (Poda):** Para evitar retrasos en el procesador, el algoritmo calcula el peso en tiempo real mediante el operador `&`. Si una combinación rompe la restricción de capacidad, es descartada inmediatamente antes de calcular sus beneficios.
* **Complejidad:** Exponencial $\mathcal{O}(2^N)$. Ideal para problemas de tamaño pequeño-mediano donde la precisión matemática es crítica.

---

### 2. Enfoque Heurístico: Greedy Inteligente (Algoritmo Voraz)
Este algoritmo prioriza la **velocidad de ejecución**, construyendo una solución de alta calidad paso a paso sin necesidad de explorar todo el universo de combinaciones.

* **¿Cómo funciona?** En lugar de elegir a ciegas por el peso más bajo o el beneficio más alto, el algoritmo utiliza el concepto económico de **Densidad de Beneficio**. En cada iteración calcula un ratio dinámico para cada conjunto disponible:
  
  $$\text{Prioridad} = \frac{\text{Suma de beneficios de ítems ayudados}}{\text{Peso del conjunto}}$$

* **Sinergias Dinámicas:** La puntuación se recalcula en cada paso. Al activar un conjunto, los ítems compartidos que quedan "a mitad de requisitos" aumentan la prioridad de los conjuntos restantes, forzando al algoritmo a cerrar "combos" de alto beneficio.
* **Complejidad:** Polinomial $\mathcal{O}(N^2 \cdot M)$. Ultra rápido y escalable para instancias masivas con miles de datos en la vida real.

---

### Comparativa de Enfoques

| Característica | Bitmask DP | Greedy Inteligente |
| :--- | :--- | :--- |
| **Tipo de Solución** | **Exacta** (Garantiza el 100% de optimización) | **Aproximada** (Buena calidad en milisegundos) |
| **Manejo de Combos** | Perfecto (Revisa todas las sinergias) | Heurístico (Sigue la densidad del ratio) |
| **Escalabilidad** | Limitada (Sufre con más de 25 conjuntos) | Alta (Soporta miles de registros) |
| **Uso de Memoria** | Mínimo (Usa enteros como banderas de bits) | Bajo (Usa vectores dinámicos) |

---
---

### 3. Enfoque Híbrido: (Ramificación y Acotación)
Este algoritmo combina lo mejor de los dos mundos: garantiza una **solución exacta** (como el Bitmask) pero con una **velocidad ultra rápida** (cercana al Greedy), convirtiéndose en la opción más eficiente para escalar el problema de forma determinista.

* **¿Cómo funciona?** Modela el espacio de soluciones como un **Árbol de Decisión Binario** recursivo. En cada nivel del árbol, el algoritmo toma una bifurcación: la rama izquierda asume que el conjunto actual se apaga (`false`) y la rama derecha asume que se enciende (`true`).
* **Optimización aplicada (Poda por Peso):** A diferencia del Bitmask que explora todo a ciegas, este enfoque calcula el peso acumulado antes de abrir una rama. Si el peso supera la capacidad de la mochila, **la rama completa se corta (poda)**, ahorrándole a la computadora millones de operaciones recursivas en subárboles inválidos.
* **Complejidad:** En el peor de los casos es $\mathcal{O}(2^N)$, pero en la práctica resuelve instancias grandes en milisegundos debido a la alta tasa de poda.

---

## Características
* **Estructura Invertida:** Mapeo de relaciones Conjunto ➔ Ítems para una evaluación rápida.
* **Cálculo Dinámico de Eficiencia:** Evaluación de combinaciones basada en la relación `Beneficio Nuevo / Peso del Conjunto`.
* **Validación de Restricciones:** Control estricto de la capacidad máxima de la mochila.

---

### 4. Enfoque Metaheurístico: Algoritmo Probabilístico con Lista Restringida de Candidatos (RCL)
Este algoritmo introduce **aleatoriedad controlada** (estocasticidad) sobre el enfoque basado en conjuntos para romper la rigidez del Greedy determinista, permitiendo explorar caminos alternativos en el espacio de soluciones y escapar de óptimos locales.

* **¿Cómo funciona?** En lugar de activar directamente el "mejor" conjunto de forma automática, el algoritmo evalúa los conjuntos disponibles mediante una **Métrica de Selección Híbrida (Score)** regulada por un parámetro $\alpha$:
  
  $$\text{score}(j) = \alpha \cdot M(j) + (1 - \alpha) \cdot P(j)$$

  Donde $M(j)$ representa el beneficio marginal dinámico (rentabilidad inmediata en el peso) y $P(j)$ es el potencial estático absoluto del conjunto a largo plazo. 
* **La Lista Restringida de Candidatos (RCL):** Tras calcular los puntajes, el algoritmo ordena los conjuntos de mayor a menor y aísla los $K$ mejores componentes en una lista selecta (RCL). Finalmente, el programa **elige un conjunto al azar dentro de este grupo (Top-$K$)** para activarlo e ingresarlo a la mochila.
* **¿Por qué se implementó?** El Greedy inteligente clásico siempre tomará la misma decisión ante los mismos datos (es miope). Al añadir la RCL, si el programa se ejecuta múltiples veces sobre una instancia masiva, descubrirá combinaciones y "combos" de conjuntos altamente eficientes que un criterio puramente voraz habría ignorado por completo.
* **Complejidad:** Polinomial $\mathcal{O}(N^2 \cdot M)$ por cada iteración. Es una solución de alta fidelidad, ideal para esquemas de inicialización en metaheurísticas avanzadas.


## Sobre el Autor

* **Nombre:** Carlos Andrés Valenzuela Olivares
* **Institución:** Universidad Diego Portales (UDP)
* **Académico:** Estudiante de 4to año de Ingeniería Civil en Informática y Telecomunicaciones
* **Áreas de Especialización e Interés:** Metaheurísticas de optimización combinatoria, análisis algorítmico, estructuras de datos avanzadas y desarrollo de software Fullstack.
