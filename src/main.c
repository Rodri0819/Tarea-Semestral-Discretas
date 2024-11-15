#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "lectura.h"
#include "analisis.h"

extern int vertices;
char filename[100];

void seguir(int *continuar) {
    int opcion2;
    int seguir = 1;

    while (seguir) {
        printf("Desea realizar otra operación?\n");
        printf("1. Sí\n");
        printf("2. No\n");
        scanf("%d", &opcion2);

        if (opcion2 == 1) {
            seguir = 0;
        } else if (opcion2 == 2) {
            liberar_matriz();
            *continuar = 0;
            seguir = 0;
        } else {
            printf("Opción no válida. Intente de nuevo.\n");
        }
    }
}

    int main() {
        int continuar = 1;
        int opcion;

        //Lectura archivo rapida
        //lectura_archivo("../gafro");

        printf("Ingrese la ubicación del archivo\n");
        fgets(filename, sizeof(filename), stdin);
        filename[strcspn(filename, "\n")] = 0;

        if (!lectura_archivo(filename)) {
            printf("No se pudo cargar el archivo.\n");
            liberar_matriz();
            return 1;
        }

        if (revisarsimetria()) {
            printf("Grafo confirmado!\n");
        } else {
            printf("Lo ingresado no es un grafo no dirigido\n");
            liberar_matriz();
            return 1;
        }

        while (continuar) {
        printf("Ingresa una operación:\n");
        printf("1. Revisar grados\n");
        printf("2. Revisar conexidad (Matriz)\n");
        printf("3. Revisar conexidad (DFS)\n");
        printf("4. Revisar K-conexidad\n");
        printf("5. Revisar si posee vértices aislados\n");
        printf("6. Introducir otro archivo(grafo)\n");
        printf("7. Salir\n");

        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: {
                int min = gradoMin();
                int max = gradoMax();
                printf("--------------------------------------\n");
                printf("El grado máximo del grafo es %i\n", max);
                printf("El grado mínimo del grafo es %i\n", min);
                printf("--------------------------------------\n");
                seguir(&continuar);
                break;
            }
            case 2: {
                printf("--------------------------------------\n");
                if (conexidad(matriz_adyacente)) {
                    printf("El grafo es conexo.\n");
                } else {
                    printf("El grafo es disconexo.\n");
                }
                printf("--------------------------------------\n");

                seguir(&continuar);
                break;
            }
            case 3: {
                printf("--------------------------------------\n");
                for (int i = 0; i < vertices; i++) {
                    printf("\n");
                    for (int j = 0; j < vertices; j++) {
                        printf("%i", matriz_adyacente[i][j]);
                    }
                }
                printf("--------------------------------------\n");

                printf("\n");
                printf("--------------------------------------\n");
                if (verificarConectividad(matriz_adyacente)) {
                    printf("El grafo es conexo.\n");
                } else {
                    printf("El grafo es disconexo.\n");
                }
                printf("--------------------------------------\n");

                seguir(&continuar);
                break;
            }
            case 4: {

                int k = kConectividad();
                printf("La k-conectividad del grafo es: %d\n", k);

                seguir(&continuar);
                break;
            }
            case 5: {
                int contador;
                int *filasconceros = aislados(&contador);
                printf("--------------------------------------\n");
                if (filasconceros == NULL) {
                    printf("Error al revisar la conexidad.\n");
                } else {
                    if (contador == 0) {
                        printf("Sin vértices aislados.\n");
                    } else {
                        printf("El grafo tiene los siguientes vértices aislados:\n");
                        for (int i = 0; i < contador; i++) {
                            printf("Vértice %d está aislado.\n", filasconceros[i] + 1);
                        }
                    }
                    free(filasconceros);
                }
                printf("--------------------------------------\n");
                seguir(&continuar);
                break;
            }
            case 6:
                printf("Ingrese la ubicación del archivo\n");
                getchar();
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = '\0';
                liberar_matriz();

                lectura_archivo(filename);

                imprimir_matriz();
                if (revisarsimetria()) {
                    printf("Grafo confirmado!\n");
                } else {
                    printf("Lo ingresado no es un grafo!\n");
                    continuar = 0;
                }
                if (continuar) {
                    seguir(&continuar);
                }
                break;
            case 7:
                continuar = 0;
                liberar_matriz();
                break;
            default:
                printf("Opción inválida.\n");
        }
    }
}