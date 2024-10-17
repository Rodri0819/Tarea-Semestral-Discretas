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

    lectura_archivo("../grafo");


    while (continuar) {
        printf("Ingresa una operación:\n");
        printf("1. Revisar grados\n");
        printf("2. Revisar conexidad \n");
        //printf("3. Revisar si posee vértices aislados\n");
        printf("4. Salir\n");

        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: {

                int min = gradoMin();
                int max = gradoMax();

                printf("El grado máximo del grafo es %i\n", max);
                printf("El grado mínimo del grafo es %i\n", min);
                continuar = 0;
                break;

            }

            case 2: {
                if (conexidad()) {
                    printf("El grafo es conexo.\n");
                } else {
                    printf("El grafo es disconexo.\n");
                }
                continuar = 0;
                break;
            }

            case 3: {
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
                continuar = 0;
                break;
            }

            case 4:
                continuar = 0;
                break;

            default:
                printf("Opción inválida.\n");
        }
    }

    return 0;
}
