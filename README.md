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

---

## Características
* **Estructura Invertida:** Mapeo de relaciones Conjunto ➔ Ítems para una evaluación rápida.
* **Cálculo Dinámico de Eficiencia:** Evaluación de combinaciones basada en la relación `Beneficio Nuevo / Peso del Conjunto`.
* **Validación de Restricciones:** Control estricto de la capacidad máxima de la mochila.

---

## 🛠️ Requisitos e Instalación
*(Nota: Modifica esta sección según el lenguaje que uses, por ejemplo, Python)*

## Sobre el Autor

* **Nombre:** Carlos Andrés Valenzuela Olivares
* **Institución:** Universidad Diego Portales (UDP)
* **Académico:** Estudiante de 4to año de Ingeniería Civil en Informática y Telecomunicaciones
* **Áreas de Especialización e Interés:** Metaheurísticas de optimización combinatoria, análisis algorítmico, estructuras de datos avanzadas y desarrollo de software Fullstack.
