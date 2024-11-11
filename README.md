# Proyecto Final (Implementacion del Juego Pacman)
# Versions Usada
Sistema Operativo: Linux Ubuntu 24.04 Its / Windows 11
Compilador: g++ Ubuntu 24.04 
Lenguaje de progrmacion: C++

# Instrucciones para ejecutarlo

# Ejecucion con el MakeFile
 Es necesario que se utilice el compilador g++, de otra forma saldra error al correr el codigo. 
*Al momento de ejecucion:* Se debe abrir la terminal y escribir el comando "make". Luego de que termine la compilacion 
escribes "make run" para iniciar con la ejecución del programa. Luego de haber ejecutado
el programa puedes escribir en la terminal "make clean" para borrar los archivos
innecesarios.

# Ejecucion con comandos
 Para compilar el programa 
 g++ -o main.cpp Archivo.cpp Ticket.cpp

Para ver el resultado  copiar en la linea de comando 
./main
 
# Motivos de solucion
La solucion de este trabajo consiste en la creacion de un grafo de lista adyacente donde creamos aristas aleatoriamente para los fantasmas , uno para la cereza y otro para pacman , implementamos el algoritmo de distra y tambien Manhatan para encontrar los 3 primeros vertices mas cercanos de cada nodo , además utilizamos una cola de prioridad para contener estos tres primeros nodos  y como parte grafica tenemos  un tablero que representara el camino mas corto pasando por la cereza para alcanzar al fantasma. 
