#include <stdio.h>
#include <stdlib.h>

#include "lectura_matriz_adyacente.h"

void lectura_archivo(const char *file) {

    FILE *f;
    f = fopen(file, "r");

    //Caso error
    if (f == NULL) {
        perror("Error al abrir archivo");
        return;
    }



    fclose(f);
}
