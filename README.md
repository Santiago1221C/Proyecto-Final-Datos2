# Proyecto Final (Implementacion del Juego Pacman)
# Versions Usada
Sistema Operativo: Linux Ubuntu 24.04 Its / Windows 11
Compilador: g++ Ubuntu 24.04 
Lenguaje de progrmacion: C++

# Instrucciones para ejecutarlo

# Ejecucion con el MakeFile
 Es necesario que se utilice el compilador g++, de otra forma saldra error al correr el codigo. 
*Al momento de ejecucion:* Se debe abrir la terminal y escribir el comando "make". Luego de que termine la compilacion 
escribes "./ejecutable" para iniciar con la ejecución del programa. Luego de haber ejecutado
el programa puedes escribir en la terminal "make clean" para borrar los archivos
innecesarios.

# Ejecucion con comandos
 Para compilar el programa 
 g++ -o main.cpp cereza.cpp grafo.cpp  tablero.cpp

Para ver el resultado  copiar en la linea de comando 
./ejecuble
 
# Motivos de solucion
La solucion de este trabajo consiste en la creacion de un grafo de lista adyacente donde creamos aristas aleatoriamente para los fantasmas , uno para la cereza y otro para Pac-man , implementamos el algoritmo de dijkstra para encontrar le camino mas corto ademas el menos costoso y tambien la formula de Manhatan para encontrar los 3 primeros vertices mas cercanos de cada nodo , además utilizamos una como parte grafica un tablero que representa el camino mas corto primero llegando a la cereza para poder luego alcanzar al fantasma. 
