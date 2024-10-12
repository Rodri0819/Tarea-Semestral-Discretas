#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "lectura.h"
#include "analisis.h"

int main() {
    char filename[100];
    int vertices;
    int continuar = 1;
    int continuar2 = 1;
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
        printf("1. Revisar grado máximo\n");
        printf("n. Salir\n");

        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        if (!isdigit(opcion)) {
            continuar = 0;
        }
        switch (opcion) {
            case 1:
                int s= gradomaximodesalida();
                int e = gradomaximodeentrada();
                printf("Grado máximo de entrada es %i\n", e);
                printf("Grado máximo de salida es %i\n", s);
                printf("El grado máximo es %i\n", e+s);
                break;
            case 2:
            break;
            case 3:
                printf("ADio\n");
                continuar = 0;
            break;

            default:

                    printf("Invalido.\n");
        }
    }


    return 0;
}
