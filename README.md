# Optimización del Set Union Knapsack Problem (SUKP) mediante Inversión de Dominio

Este proyecto implementa y analiza el Problema de la Mochila con Unión de Conjuntos (SUKP, por sus siglas en inglés), un desafío de optimización combinatoria NP-hard. A diferencia del problema de la mochila clásico, aquí los elementos del universo confieren beneficios solo cuando se completan los subconjuntos específicos que los requieren, modelando escenarios reales de presupuestos compartidos y sinergia de recursos.

---

## El Núcleo del Problema: La Trampa del Peso Compartido

En el SUKP, el universo está compuesto por elementos base (herramientas, infraestructura, etc.), cada uno con un peso asociado. Los beneficios, en cambio, pertenecen a conjuntos compuestos (proyectos o servicios). El desafío principal radica en que **múltiples conjuntos pueden requerir el mismo elemento base**.

### La Analogía del Mundo Real
Imagine que debe realizar dos proyectos en un jardín:
* **Proyecto A:** Requiere un destornillador, un alicate y un rollo de cinta aisladora (15 gramos).
* **Proyecto B:** Requiere un pelacables y **el mismo rollo de cinta aisladora** (15 gramos).

Al empacar las herramientas en la mochila, el rollo de cinta se introduce **una sola vez**. Por lo tanto, la mochila incrementa su peso por el valor neto de esa herramienta (15g), independientemente de que sirva para activar uno, ambos o ningún proyecto. El peso es una propiedad física lineal de los elementos, mientras que el beneficio es una propiedad condicional de los conjuntos.

---

## Evolución de la Solución Algorítmica

El repositorio analiza esta lógica a través de dos fases de abstracción algorítmica:

### Fase 1: El Modelo Conceptual (Evaluación Directa)
Este primer enfoque traduce la analogía física a código utilizando variables primitivas aisladas. Su propósito es demostrar de forma explícita que el cálculo del peso y la validación de los beneficios deben ocurrir en canales de flujo completamente desacoplados.

* **Gestión del Peso:** Se evalúa de manera lineal mediante condicionales directos sobre cada herramienta. Al no existir estructuras anidadas, el peso del elemento compartido se computa una única vez.
* **Gestión del Beneficio:** Se valida mediante lógica booleana estricta (`&&`). Si un solo elemento requerido por el conjunto está ausente (valor `0`), la condición completa falla y el beneficio no se adjudica, reflejando fielmente la restricción del problema.

### Fase 2: El Modelo Indexado Optimizado (Mapa Inverso y Contadores)
Para escalar el problema a instancias masivas, la verificación booleana directa genera un cuello de botella de complejidad O(n * m) al tener que inspeccionar los requisitos de cada conjunto repetidamente. La Fase 2 introduce dos estructuras de datos avanzadas:

1.  **El Mapa Inverso:** Un vector de vectores que invierte la jerarquía de los datos. En lugar de que el conjunto conozca sus elementos, **el elemento conoce a qué conjuntos pertenece**. Esto se calcula una sola vez en una fase de pre-procesamiento.
2.  **El Vector de Faltantes:** Un arreglo dinámico que almacena cuántos elementos le faltan a cada conjunto para ser completado.

Cuando la metaheurística activa un elemento, el algoritmo realiza una **propagación activa por eventos**: consulta la fila de ese elemento en el mapa inverso y decrementa de forma instantánea O(1) los contadores de los conjuntos afectados. Si un contador llega a cero, el beneficio se reclama inmediatamente. El algoritmo de evaluación se reduce a un único ciclo principal de orden de complejidad lineal O(m).

---

## Análisis Comparativo de Complejidad

| Dimensión | Enfoque Tradicional (Por Conjuntos) | Nuestro Enfoque (Inversión de Dominio) |
| :--- | :--- | :--- |
| **Variable de Decisión** | Selección de Conjuntos ($2^n$ estados) | Activación de Elementos ($2^m$ estados) |
| **Operación de Peso** | Unión de conjuntos con filtrado de duplicados. | Suma aritmética lineal directa. |
| **Evaluación de Fitness** | Complejidad alta y dependiente del tamaño de los conjuntos. | Complejidad optimizada a nivel de ciclo único O(m). |

---

## Sobre el Autor

* **Nombre:** Carlos Andrés Valenzuela Olivares
* **Institución:** Universidad Diego Portales (UDP)
* **Académico:** Estudiante de 4to año de Ingeniería Civil en Informática y Telecomunicaciones
* **Áreas de Especialización:** Metaheurísticas de optimización combinatoria, análisis algorítmico, estructuras de datos avanzadas y desarrollo de software Fullstack.
