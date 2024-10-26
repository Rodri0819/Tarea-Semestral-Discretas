#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int vertices;
int **matriz_adyacente;
int **matriz_transpuesta;

void inicializarmatriz() {
    matriz_adyacente = (int **)malloc(vertices * sizeof(int *));
    matriz_transpuesta = (int **)malloc(vertices * sizeof(int *));

    for (int i = 0; i < vertices; i++) {
        matriz_adyacente[i] = (int *)malloc(vertices * sizeof(int));
        matriz_transpuesta[i] = (int *)malloc(vertices * sizeof(int));
        for (int j = 0; j < vertices; j++) {
            matriz_adyacente[i][j] = 0;
            matriz_transpuesta[i][j] = 0;
        }
    }
}

void lectura_archivo(const char *file) {
    FILE *f = fopen(file, "r");

    // Caso error
    if (f == NULL) {
        perror("Error al abrir archivo");
        return;
    }

    //Cantidad de vertices
    if (fscanf(f, "%d", &vertices) != 1 || vertices <= 0) {
        printf("Error: número de vértices inválido.\n");
        fclose(f);
        return;
    }

    inicializarmatriz();

    int vertice, adyacente;

    //Leer el vertice principal, buscando d:
    while (fscanf(f, "%d:", &vertice) != EOF) {
        char h = fgetc(f);
        if (h == '\n' || h == EOF ) {
            continue;
        }

        // alidación del vértice en el rango permitido
        if (vertice < 1 || vertice > vertices) {
            printf("Advertencia: vértice %d fuera del rango válido.\n", vertice);
            continue;
        }

        //Leer los vertices adyacentes
        while (fscanf(f, "%d" , &adyacente) == 1) {
            // Verificación de que el vértice adyacente está en el rango permitido
            if (adyacente < 1 || adyacente > vertices) {
                printf("Advertencia: vértice adyacente %d para vértice %d fuera de rango.\n", adyacente, vertice);
            } else {
                // Marcar la conexion en la matriz, dandole valor 1
                matriz_adyacente[vertice - 1][adyacente - 1] = 1;
            }

            char c = fgetc(f);  // Leer el siguiente carácter
            if (c == '\n' || c == EOF) {
                break;
            }
        }
    }
    fclose(f);
}

void imprimir_matriz() {
    printf("Matriz de adyacencia:\n");
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            printf("%d ", matriz_adyacente[i][j]);
        }
        printf("\n");
    }
}

void liberar_matriz() {
    for (int i = 0; i < vertices; i++) {
        free(matriz_adyacente[i]);
        free(matriz_transpuesta[i]);
    }
    free(matriz_adyacente);
    free(matriz_transpuesta);
}

void transponermatriz() {
    int fila = vertices;
    int columna = vertices;
    for (int i = 0; i < fila; i++) {
        for (int j = 0; j < columna; j++) {
            matriz_transpuesta[i][j] = matriz_adyacente[j][i];

        }
    }
}

int revisarsimetria() {
    transponermatriz();
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (matriz_adyacente[i][j] != matriz_transpuesta[i][j]) {
                return 0;
            }
        }
    }
    return 1;
}
