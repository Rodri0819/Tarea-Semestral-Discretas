//
// Created by rodrigo on 10/12/24.
//

#ifndef ANALISIS_H
#define ANALISIS_H

extern int vertices;
extern int **matriz_adyacente;
extern int **matriz_temporal;
extern int *visitado;
extern int *padre;

int gradoMax();
int gradoMin();
int *aislados(int *contador);
int conexidad(int **matriz_adyacente);
int dfsconexo();
int kConectividad();


#endif // ANALISIS_H
