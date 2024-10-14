#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "lectura.h"
#include "analisis.h"

int main() {
    char filename[100];
    int vertices;
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

    imprimir_matriz();

    while (continuar) {

        printf("Ingresa una operación:\n");
        printf("1. Revisar grados\n");
        printf("2. Salir\n");

        printf("Seleccione una opción:");
        scanf("%d", &opcion);

        if (!isdigit(opcion)) {
            continuar = 0;
        }
        switch (opcion) {
            case 1:
                int s = gradomaximodesalida();
                int e = gradomaximodeentrada();
                int min = gradoMin();
                int max = gradoMax();
                printf("Grado máximo de salida es %i\n", s);
                printf("Grado máximo de entrada es %i\n", e);
                printf("El grado máximo es %i\n", e+s);
                printf("El grado máximo del grafo es %i\n", max);
                printf("El grado mínimo del grado es %i\n", min);
            break;

            case 2:
                printf("ADio\n");
                continuar = 0;
            break;

            default:
                    printf("eso tilin");
                    printf("Invalido.\n");
        }
    }
    return 0;
}
