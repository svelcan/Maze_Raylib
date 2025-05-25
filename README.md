# InvisibleMaze
Juego de laberintos invisibles.
Recolecta monedas, atraviesa laberintos cada vez más grandes y aumenta tu puntaje.

## Estructura de archivos
main.cpp: El código empieza a correr aquí

Constants.cpp: Constantes útiles que se utilizan en diferentes archivos y no planeabamos cambiar
Game.cpp: Actualiza y dibuja el juego

Cell.cpp: Cada celda de la cuadrícula del laberinto
CellGrid.cpp: La cuadrícula del laberinto
Player.cpp: El jugador
Flare.cpp: La bengala que puede lanzar el jugador

Menu.cpp: Menú de opciones
ClickableObject.cpp: Botones de los menú

## Instalación en Linux
Para correr el juego:
1. Entrar a la carpeta `InvisibleMaze`
2. Escribir en la terminal `./InvisibleMaze`
3. ¡Listo!

Nuestro juego incluye el archivo .so de Raylib por lo que no es necesario ningún paso extra para jugar

Para compilar el juego:
1. Recomendamos mucho descargar Raylib para que no haya problemas, hay diferentes formas de hacerlo dependiendo de la distribución.
Para más información: https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux
2. Hemos incluido un archivo `Makefile` y uno `build.bash` para facilitar la compilación y ejecución del proyecto, se puede usar entonces tanto `make run` así como `bash build.bash` para compilar.
