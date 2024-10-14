#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int vertices;
int **matrix_adyacente;

void inicializarmatriz() {
    matrix_adyacente = (int **)malloc(vertices * sizeof(int *));
    for (int i = 0; i < vertices; i++) {
        matrix_adyacente[i] = (int *)malloc(vertices * sizeof(int));
        for (int j = 0; j < vertices; j++) {
            matrix_adyacente[i][j] = 0;
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
    fscanf(f, "%d", &vertices);

    inicializarmatriz();

    int vertice, adyacente;

    //Leer el vertice principal, buscando d:
    while (fscanf(f, "%d:", &vertice) != EOF) {
        char h = fgetc(f);
        if (h == '\n' || h == EOF ) {
        continue;
        }
        //Leer los vertices adyacentes
        while (fscanf(f, "%d" , &adyacente)==1) {
            //Marcar la conexion en la matriz, dandole valor 1
            matrix_adyacente[vertice - 1][adyacente - 1] = 1;

            char c = fgetc(f);  //Leer el siguiente carácter
              if (c == '\n' || c == EOF ) {
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
            printf("%d ", matrix_adyacente[i][j]);
        }
        printf("\n");
    }
}

void liberar_matriz() {
    for (int i = 0; i < vertices; i++) {
        free(matrix_adyacente[i]);
    }
    free(matrix_adyacente);
}
