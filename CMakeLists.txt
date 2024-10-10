cmake_minimum_required(VERSION 3.20)
project(Proyecto_Matematicas_Discretas C)

set(CMAKE_C_STANDARD 11)

# Añadir ejecutables
add_executable(Proyecto_Matematicas_Discretas src/main.c src/lectura_matriz_adyacente.c)
