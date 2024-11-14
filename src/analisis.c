#include <stdio.h>
#include <stdlib.h>  // Para malloc y free
#include "analisis.h"

#include <stdbool.h>

#include "lectura.h"

int gradoMin() {
    int gradoMin = vertices;
    for (int i = 0; i < vertices; i++) {
        int counter = 0;
        for (int j = 0; j < vertices; j++) {
            if (matriz_adyacente[i][j] == 1) {
                counter++;
            }
        }
        if (counter < gradoMin) {
            gradoMin = counter;
        }
    }
    return gradoMin;
}

int gradoMax() {
    int gradoMax = 0;
    for (int i = 0; i < vertices; i++) {
        int counter = 0;
        for (int j = 0; j < vertices; j++) {
            if (matriz_adyacente[i][j] == 1) {
                counter++;
            }
        }
        if (counter > gradoMax) {
            gradoMax = counter;
        }
    }
    return gradoMax;
}

int* aislados(int* contador) {
    int* filasconceros = (int*) malloc(vertices * sizeof(int));
    int contador_filasconceros = 0;

    for (int i = 0; i < vertices; ++i) {
        int ceros = 0;
        for (int j = 0; j < vertices; ++j) {
            if (matriz_adyacente[i][j] == 0) {
                ceros++;
            }
        }
        if (ceros == vertices) {
            filasconceros[contador_filasconceros] = i;
            contador_filasconceros++;
        }
    }

    *contador = contador_filasconceros;
    return filasconceros;
}

void multiplicarMatrices(int** resultado, int** A, int** B) {
    for (int i = 0; i < vertices; ++i) {
        for (int j = 0; j < vertices; ++j) {
            resultado[i][j] = 0;
            for (int k = 0; k < vertices; ++k) {
                resultado[i][j] = resultado[i][j] +  (A[i][k] * B[k][j]);
            }
        }
    }
}

//Suma las matrices
void sumarMatrices(int** resultado, int** A) {
    for (int i = 0; i < vertices; ++i) {
        for (int j = 0; j < vertices; ++j) {
            resultado[i][j] = resultado[i][j] + A[i][j];
        }
    }
}

int conexidad(int** matriz_adyacente) {
    int** matriz_suma = (int**)malloc(vertices * sizeof(int*));
    int** matriz_potencia = (int**)malloc(vertices * sizeof(int*));
    int** matriz_temp = (int**)malloc(vertices * sizeof(int*));

    for (int i = 0; i < vertices; i++) {
        matriz_suma[i] = (int*)malloc(vertices * sizeof(int));
        matriz_potencia[i] = (int*)malloc(vertices * sizeof(int));
        matriz_temp[i] = (int*)malloc(vertices * sizeof(int));

        for (int j = 0; j < vertices; j++) {
            matriz_suma[i][j] = 0;
            matriz_potencia[i][j] = matriz_adyacente[i][j];
        }
    }

    for (int k = 1; k < vertices; ++k) {
        multiplicarMatrices(matriz_temp, matriz_potencia, matriz_adyacente);

        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
                matriz_potencia[i][j] = matriz_temp[i][j];
            }
            sumarMatrices(matriz_suma, matriz_potencia);
        }
    }

    int conexo = 1;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (matriz_suma[i][j] == 0) {
                conexo = 0;
                break;
            }
        }
    }

    for (int i = 0; i < vertices; i++) {
        free(matriz_suma[i]);
        free(matriz_potencia[i]);
        free(matriz_temp[i]);
    }
    free(matriz_suma);
    free(matriz_potencia);
    free(matriz_temp);

    return conexo;
}

bool* nodoVisitado;

void inicializarVisitados() {
    nodoVisitado = (bool*)malloc(vertices * sizeof(bool));
    for (int i = 0; i < vertices; i++) {
        nodoVisitado[i] = false;
    }
}

void dfs(int s) {
    nodoVisitado[s] = true;
    for (int i = 0; i < vertices; i++) {

        if (matriz_adyacente[s][i] == 1 && !nodoVisitado[i]) {
            dfs(i);
        }
    }
}

int verificarConectividad() {
    inicializarVisitados();
    dfs(0);

    for (int i = 0; i < vertices; i++) {
        if (!nodoVisitado[i]) {
            free(nodoVisitado);
            return 0;
        }
    }

    free(nodoVisitado);
    return 1;
}




void dfsReducido(int nodo, bool *omitidos, bool *visitados) {
    visitados[nodo] = true;
    for (int i = 0; i < vertices; i++) {
        if (!omitidos[i] && matriz_adyacente[nodo][i] == 1 && !visitados[i]) {
            dfsReducido(i, omitidos, visitados);
        }
    }
}

bool esConexoReducido(bool *omitidos, bool *visitados) {
    for (int i = 0; i < vertices; i++) {
        visitados[i] = false;
    }

    int inicio = -1;
    for (int i = 0; i < vertices; i++) {
        if (!omitidos[i]) {
            inicio = i;
            break;
        }
    }

    if (inicio == -1) return false;

    dfsReducido(inicio, omitidos, visitados);

    for (int i = 0; i < vertices; i++) {
        if (!omitidos[i] && !visitados[i]) {
            return false;
        }
    }
    return true;
}

bool probarCombinaciones(int k, int nodoInicial, int contadorEliminados, bool *omitidos, bool *visitados) {
    if (contadorEliminados == k) {
        return esConexoReducido(omitidos, visitados);
    }
    for (int i = nodoInicial; i < vertices; i++) {
        omitidos[i] = true;
        if (!probarCombinaciones(k, i + 1, contadorEliminados + 1, omitidos, visitados)) {
            omitidos[i] = false;
            return false;
        }
        omitidos[i] = false;
    }
    return true;
}

int kConectividad() {
    bool *visitados = (bool*)malloc(vertices * sizeof(bool));
    bool *omitidos = (bool*)calloc(vertices, sizeof(bool));

    for (int k = 1; k < vertices-1; k++) {
        if (!probarCombinaciones(k, 0, 0, omitidos, visitados)) {
            free(visitados);
            free(omitidos);
            return k;
        }
    }
    free(visitados);
    free(omitidos);
    return vertices - 1;
}