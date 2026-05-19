# Optimizacion del Set Union Knapsack Problem (SUKP)
Este repositorio contiene el marco conceptual y las estructuras base para el desarrollo de metaheuristicas aplicadas al problema de la mochila con union de conjuntos (SUKP).

## Proposito del Proyecto
A diferencia del problema de la mochila clásico, el SUKP modela escenarios donde los elementos del universo son compartidos por multiples subconjuntos de beneficio. Este proyecto desplaza el dominio de decision: en lugar de evaluar combinaciones de conjuntos, optimiza la activacion de elementos base. 

Al aislar el cálculo del peso en los elementos y delegar el beneficio a la satisfaccion completa de los conjuntos, se transforma una restriccion no lineal de union de conjuntos en un modelo de evaluacion directo, sentando las bases para operadores de busqueda local altamente eficientes.
