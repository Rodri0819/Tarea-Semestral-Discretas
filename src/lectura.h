#ifndef LECTURA_MATRIZ_ADYACENTE_H
#define LECTURA_MATRIZ_ADYACENTE_H
extern int vertices;
extern int **matriz_adyacente;
extern int **matriz_transpuesta;
extern int **matriz_temporal;

// Declaración de la función que implementará la lógica para leer el archivo
void lectura_archivo();
void inicializar_matriz();
void imprimir_matriz();
void liberar_matriz();
int revisarsimetria();
#endif
