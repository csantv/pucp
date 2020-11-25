# IEE240 - Laboratorio 3

## Instrucciones:
- Completar el archivo `preg1.c` con las indicaciones del enunciado del problema 1.

- Completar el archivo `preg2.c` con las indicaciones del enunciado del problema 2.

- **La prueba inicia a las 8:10 pm y termina a las 10:00 pm. El sistema (GitHub Classroom) cierra a las 10:10 p.m., no se calificarán entregas (`push`) luego de esa hora.**

- **En caso se detecte plagio en alguno de sus códigos, se iniciará el proceso correspondiente definido por la Facultad de Ciencias e Ingeniería.**

- **Las respuestas a las preguntas teóricas debe resolverlas en el archivo excel que se encuentra en PAIDEIA y subir el PDF al repositorio.**

## Consideraciones importantes:
- Para medir los tiempos de ejecución debe utilizar la función `clock_gettime`. Un ejemplo de uso se encuentra implementado en los archivos `preg1.c` y `preg2.c`.

- **Para reportar los tiempos de ejecución debe ejecutar la función analizada 15 veces y calcular la mediana de los tiempos calculados.**

- **Inicializar las matrices con valores aleatorios entre 0 y 150.**

- **Los tamaños de las matrices y el tamaño de bloque deben ser ingresados por el usuario.**

- **Para tamaños pequeños (N < 8) imprimir las matrices operandos y las matrices resultados para verificar el funcionamiento de su algoritmo.**

- **Cualquier programa no funcional (errores de compilación) tendrá una penalización de 3 puntos respecto a su nota final.** 

## Problema 1 (10 puntos):
Codificar un programa que realice la multiplicación matriz por matriz, ambas de dimensión `NxN`. Puede utilizar cualquier forma de declaración de matrices en lenguaje C. Completar lo siguiente:

- La función `matmulNaive` la cual realizará el producto punto de las filas de la matriz `A` con las columas de la matriz `B`.
- La función `matmulBlocking` la cual realizará el producto de las matrices `A` y `B` utilizando la técnica de blocking.
- Probar su algoritmo para las siguientes combinaciones:

a) 
  - Tamaño de bloque: `8`
  - Valor de `N = 64, 128, 256, 512, 1024` 

b) Realizar la gráfica del Speedup. vs el valor de N.

c) 
  - Tamaño de bloque: `4, 8, 64, 128, 256, 512`
  - Valor de `N = 1024`

d) Realizar la gráfica del Speedup vs. el valor del tamaño del bloque.
 
e) Explicar qué tipo de localidad explota la técnica de blocking y cómo afecta esto en los resultados obtenidos.

f) Explicar el comportamiento del Speedup cuando se varía el tamaño del bloque.

## Problema 2 (10 puntos):

Codificar dos funciones que calculen la transpuesta de una matriz. Para ello, debe considerar las matrices cuadradas `A` y `B` (`NxN`) en donde `B` será igual a la transpuesta de `A`. Para este problema, **debe declarar sus matrices de forma dinámica**. Para ello, puede usar puntero a variable o puntero a puntero.
Considerar lo siguiente:

a) Función 1: Calcular `B` si se asume que `A` sigue el ordenamiento en memoria por filas (**row-major**).

b) Función 2: Calcular `B` si se asume que `A` sigue el ordenamiento en memoria por columnas (**col-major**).

c) En un gráfico `Tiempo de ejecución vs. N`, realizar una comparación para `N = 128, 256,1024,2048, 4096`. La comparación es para cada una de las funciones.

d) Explicar si es que existe una relación entre el tiempo de ejecución de cada función y los valores de `N`.

e) Explicar qué implementación ha logrado mayor rapidez y cómo está relacionado con los conceptos de localidad.

 







