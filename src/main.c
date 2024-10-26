#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lectura.h"
#include "analisis.h"

extern int vertices;

int main() {
    int continuar = 1;
    int opcion;

    /*
    printf("Ingrese la ubicación del archivo\n");
    fgets(filename, sizeof(filename), stdin);

    //eliminar n
    filename[strcspn(filename, "\n")] = 0;

    lectura_archivo(filename);
    */


    lectura_archivo("../grafo");

    while (continuar) {
        printf("Ingresa una operación:\n");
        printf("1. Revisar grados\n");
        printf("2. Revisar conexidad (Matriz)\n");
        printf("3. Revisar conexidad (DFS)\n");
        printf("4. Revisar K-conexidad\n");
        printf("5. Revisar si posee vértices aislados\n");
        printf("6. Salir\n");

        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: {
                int min = gradoMin();
                int max = gradoMax();
                printf("El grado máximo del grafo es %i\n", max);
                printf("El grado mínimo del grafo es %i\n", min);
                liberar_matriz();
                continuar = 0;
                break;
            }
            case 2: {
                if (conexidad()) {
                    printf("El grafo es conexo.\n");
                } else {
                    printf("El grafo es disconexo.\n");
                }
                liberar_matriz();
                continuar = 0;
                break;
            }

            case 3: {
                for (int i = 0; i < vertices; i++) {
                    printf("\n");
                    for (int j = 0; j < vertices; j++) {
                        printf("%i", matriz_adyacente[i][j]);
                    }
                }
                printf("\n");

                if (dfsconexo(matriz_adyacente)) {
                    printf("El grafo es conexo.\n");
                } else {
                    printf("El grafo es disconexo.\n");
                }
                liberar_matriz();
                continuar = 0;
                break;
            }

            case 4: {
                printf("Función de K-conexidad aún no implementada.\n");
                liberar_matriz();
                continuar = 0;
                break;
            }
            case 5: {
                int contador;
                int *filasconceros = aislados(&contador);

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
                liberar_matriz();
                continuar = 0;
                break;
            }
            case 6:
                continuar = 0;
                liberar_matriz();
                break;
            default:
                printf("Opción inválida.\n");
        }
    }

    return 0;
}
