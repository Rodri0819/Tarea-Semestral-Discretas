# Proyecto Semestral Matemáticas Discretas 
## Análisis de la k-conexidad en grafos para redes eléctricas

### Instrucciones de compilación 

El código está hecho con CLion así que es recomendable usar ese IDE y ejecutar ahi, en caso de usar otro IDE (VS Code, Sublime Text, etc).

1.- Para clonar el respositorio usar
```bash
git clone https://github.com/Rodri0819/Tarea-Semestral-Discretas/`
```
o en su defecto descargarlo.

2.- Ejecutar en la ubicación del proyecto por via terminal escribiendo `make run` en ...\Tarea-Semestral-Discretas\ (Windows)

En caso de que no sirva el make run:

Ejecutar por la terminal `gcc -o main src/main.c src/lectura.c src/analisis.c` en ...\Tarea-Semestral-Discretas\

Despues de compilarlo, ejecutar `main.exe` (Windows), o `./main` (Linux)

## Uso
Para usar el programa ya compilado, asegúrese de tener un archivo en el formato adecuado (sin extensión). Cuando se pida la ubicación del archivo, ingrese la ruta completa, como en el siguiente ejemplo:

`...\Tarea-Semestral-Discretas\grafos`

Se desplegara un menú de opciones para ver que se puede hacer con el grafo (verificar k-conexidad, conexidad, grado min, grado max, leer otro grafo, etc)

Para finalizar el programa seleccionar la opción `Salir`
