#include <stdio.h>
#include "analisis.h"
#include "lectura.h"  // Para usar la matriz de adyacencia global

int gradoMin() {
    int gradoMin = vertices;
    int vertice;
    int fila = vertices;
    int columna = vertices;

    for (int i=0; i<vertices; i++){
        int counter=0;
        for (int j=0; j<vertices; j++){
            if (matrix_adyacente[i][j]==1){
                counter++;
            }
        }
        if (counter<gradoMin){
            gradoMin=counter;
        }
    }
    return gradoMin;
}

int gradoMax() {
    int gradoMax = 0;
    int vertice;
    int fila = vertices;
    int columna = vertices;

    for (int i=0; i<vertices; i++){
        int counter=0;
        for (int j=0; j<vertices; j++){
            if (matrix_adyacente[i][j]==1){
                counter++;
            }
        }
        if (counter>gradoMax){
            gradoMax=counter;
        }
    }
    return gradoMax;
}

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

void transponermatriz() {
    int fila = vertices;
    int columna = vertices;
    int matrix_transpuesta[100][100];

    for (int i = 0; i < fila; i++) {
        for (int j = 0; j < columna; j++) {
            matrix_transpuesta[j][i] = matrix_adyacente[i][j];
        }
    }

    for (int i = 0; i < fila; i++) {
        for (int j = 0; j < columna; j++) {
            matrix_adyacente[i][j] = matrix_transpuesta[i][j];
        }
    }
}

int gradomaximodeentrada() {
    int max_grado = 0;
    int vertice;
    transponermatriz();
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
