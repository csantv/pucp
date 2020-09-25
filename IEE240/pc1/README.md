# Practica 1
Descripción de los archivos del repositorio:

## main.c
Este archivo contiene el programa principal donde se leen los parámetros que se ingresan por línea de comandos, se declara la función a integrar, los límites de la integral, se reserva el espacio de memoria necesario, y se llama a la función en lenguaje ensamblador de 32 bits para el cálculo de dicha integral. También se definen los prototipos de las funciones empleadas.

**NOTA: debe completar la función `void func (int a, int b, int *arr, int N)` según el enunciado de la pregunta**

## integral.asm
Este archivo contiene la función llamada desde el programa `main.c` y calcula la integral del arreglo generado en el programa en C. El prototipo de la función es:
`int integral(int *a, int N)` donde `a` es el puntero al arreglo a integrar y `N` es el tamaño del arreglo.

**NOTA: debe completar este archivo para implementar la función `int integral(int *a, int N)` en lenguaje ensamblador según el enunciado de la pregunta**

## pc1.sh
Este archivo contiene los comandos para ensamblar la función implementada en el archivo `integral.asm` y para linkear esa función con el programa principal en el archivo `main.c`. Finalmente muestra un caso de uso donde los límites son `a=2` y `b=8`. Este archivo lo puede ejecutar de la siguiente manera:
```
$ bash pc1.sh
```

**NOTA: la primera ejecución del bash, sin realizar codificación alguna, debería devolver como resultado de la integral el valor 0**

## Subir solución a GitHub para revisión
Ejecutar los siguientes pasos para realizar el `push` de su repositorio. **NOTA:** Los comandos a continuación debe ejecutarlos dentro de la carpeta del repositorio.

- Verificar con el siguiente comando que se han modificado los archivos correctos. Debería aparecer en rojo los archivos modificados (`integral.asm` y `main.c`).
```
$ git status
```
- Para añadir los archivos a git:
```
$ git add .
```
- Para subir sus códigos al repositorio remoto (GitHub):
```
$ git commit -m "<ponga-aqui-un-comentario-util>"
$ git push origin master
```
- Finalmente revisar su nota en la página web del repositorio.
