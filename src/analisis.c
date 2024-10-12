#include <stdio.h>
#include "analisis.h"
#include "lectura.h"  // Para usar la matriz de adyacencia global

int gradomaximodesalida() {
    int max_grado = 0;
    int vertice;
    int fila = vertices;
    int columna = vertices;

    for (int i = 0; i < fila; i++) {
        int grado_actual = 0;
        for (int j = 0; j < columna; j++) {
            if (matrix_adyacente[i][j] == 1) {
                grado_actual++;
            }
        }
        if (grado_actual > max_grado) {
            max_grado = grado_actual;
            vertice = i;
        }
    }
    return max_grado;
}
int gradomaximodeentrada() {
    int max_grado = 0;
    int vertice;


    return max_grado;
}