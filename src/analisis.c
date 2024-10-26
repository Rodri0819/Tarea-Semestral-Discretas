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

//Función que recibe  tres matrices por punteros, multiplicando A * B y la guarda en resultado
void multiplicarMatrices(int** resultado, int** A, int** B) {
    for (int i = 0; i < vertices; ++i) {
        for (int j = 0; j < vertices; ++j) {
            resultado[i][j] = 0;
            //La multiplicación de la matriz se guarda en resultado
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

int conexidad() {
    //Asignación de memoria dinamica para las matrices
    int** matriz_suma = (int**) malloc(vertices * sizeof(int*));
    int** matriz_potencia = (int**) malloc(vertices * sizeof(int*));
    int** matriz_temp = (int**) malloc(vertices * sizeof(int*));

    for (int i = 0; i < vertices; i++) {
        matriz_suma[i] = (int*) malloc(vertices * sizeof(int));
        matriz_potencia[i] = (int*) malloc(vertices * sizeof(int));
        matriz_temp[i] = (int*) malloc(vertices * sizeof(int));

        //Inicializamos la matriz suma en 0 y la potencia como la matriz adyacente
        for (int j = 0; j < vertices; j++) {
            matriz_suma[i][j] = 0;
            matriz_potencia[i][j] = matriz_adyacente[i][j];
        }
    }

    for (int k = 1; k < vertices; ++k) {
        //Multiplicamos la matriz potencia por la matriz adyacente la cantidad de vertices
        multiplicarMatrices(matriz_temp, matriz_potencia, matriz_adyacente);

        //Copiamos el resultado de la multiplicacion en la matriz potencia, asi iterando el resultado
        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
                matriz_potencia[i][j] = matriz_temp[i][j];
            }
            //Sumamos la matriz potencia la cantidad de vertices y la guardamos finalmente en la matriz suma
            sumarMatrices(matriz_suma, matriz_potencia);
        }
    }

    int conexo = 1;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            //Si encontramos un 0 en la matriz, es disconexo
            if (matriz_suma[i][j] == 0) {
                conexo = 0;
                break;
            }
        }
    }
    for (int i = 0; i < vertices; ++i) {
        for (int j = 0; j < vertices; ++j) {
            printf("%d",matriz_suma[i][j]);
            printf(",");
        }
        printf("\n");
    }
    //Liberación de la memoria
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
bool* nodoVisitado;  // Array para marcar los nodos visitados

// Función para inicializar el array de nodos visitados
void inicializarVisitados() {
    nodoVisitado = (bool*)malloc(vertices * sizeof(bool));
    for (int i = 0; i < vertices; i++) {
        nodoVisitado[i] = false;
    }
}
//Marca los nodos alcansables desde s
void dfs(int s) {
    nodoVisitado[s] = true;
    for (int i = 0; i < vertices; i++) {
        //Si hay conexión y el nodo no está visitado
        if (matriz_adyacente[s][i] == 1 && !nodoVisitado[i]) {
            dfs(i); //Se llama recursivamente
        }
    }
}

int dfsconexo() {
    inicializarVisitados();  // Inicializa el array de visitados
    dfs(0);                  // Realiza DFS desde el primer nodo (0)

    // Verifica si todos los nodos fueron visitados
    for (int i = 0; i < vertices; i++) {
        if (!nodoVisitado[i]) {
            free(nodoVisitado);  // Libera memoria antes de retornar
            return 0;  // Retorna 0 si el grafo es disconexo
        }
    }

    free(nodoVisitado);  // Libera memoria después de verificar
    return 1;  // Retorna 1 si el grafo es conexo
}

