# IEE240 - Laboratorio 1

## Problema 1 (11 puntos):
- Los archivos necesarios para el desarrollo de esta pregunta se encuentran en la carpeta `pregunta1`. 
- Completar el archivo `myLCM.asm` en la sección entre comentarios. El código debe calcular el mímino común múltiplo de dos números positivos diferentes de cero. Tomar en cuenta las siguientes restricciones:
    - Los números debe ser ingresados por el usuario. Para ello, el programa debe mostrar en pantalla el mensaje **Ingrese los valores de a y b**.
    ```
    $ Ingrese los valores de a y b
    $ 10 5
    ```
    - Los números ingresados deben guardarse en memoria. Las variables **a** y **b** no deben ser inicializadas.
    - Su código debe verificar que los números ingresados sean positivos y diferentes de cero.
    - El resultado debe guardarse en la variable **r**. Esta variable no debe estar inicializada.
    - Mostrar el resultado en pantalla de la siguiente forma:

    ```
    $ El LCM de 10 y 5 es: 10
    ```
**NOTA: considerar todas las variables como datos de tipo int de 4 bytes.**

- Para clonar el repositorio y trabajar de forma local, realizar lo siguiente en un Terminal de Linux. Dentro de `<carpeta-del-repositorio>` encontrará todos los archivos necesarios para el desarrollo del laboratorio.
```
$ git clone <link-repositorio-alumno>
$ cd <carpeta-del-repositorio>
```
- Para verificar el funcionamiento de su código, ejecute lo siguiente lo siguiente en un Terminal de Linux.
```
$ nasm -f elf32 myLCM.asm -o myLCM.o
$ gcc -m32 myLCM.o -o lab1p1
```
**CALIFICACIÓN:**
Está pregunta será calificada de forma manual por cada JP. De no cumplir con las indicaciones mencionadas se **descontarán 3 puntos** a su nota final. 

**ALGORITMO:**
```
def myLCM(a,b):
    mymax <- max(a,b)
    mymin <- min(a,b)
    i <- mymax 
    while (1):
        if (i mod mymin == 0):
            return i
        i += mymax
    return i
```

## Problema 2 (9 puntos)
- Completar el archivo `imneg.asm` en la sección delimitada por los comentarios. El código debe calcular el negativo de una imagen.
- La imagen de entrada y salida se declaran en el archivo `testImneg.c`.
- Considerar que la imagen de entrada es una cadena de enteros de 1 byte por pixel en memoria RAM.
- Para verificar el funcionamiento de su código, ejecute lo siguiente en un Terminal de Linux. Puede verificar lo que se está realizando dentro del archivo. Se utilizan 3 imágenes que se encuentran en la carpeta `data` para validar su solución. **NOTA: solo se aceptan imágenes en escala de grises y en formato pgm P5.**
```
$ bash ./pregunta2/imneg.sh
```
- Si todo esta correcto no debería aparecer ningún mensaje de error en el Terminal.
- Si desea verificar/depurar sus programas puede utilizar los siguientes comandos. Puede verificar el correcto funcionamiento de forma visual (ver imagen `output.pgm`).
```
$ nasm -f elf32 -o imneg.o ./pregunta2/imneg.asm
$ gcc -m32 -march=i686 -g ./pregunta2/testImneg.c imneg.o -o labp2
$ ./labp2 ./data/goldhill_gray.pgm
```


**ALGORITMO:**
```
int output[N_data]
main(){
    for (each input value in the i position){
        output[i] = 255 - value 
    }
}
```

## Subir solución a GitHub Classroom para auto revisión.
Al terminar el laboratorio y luego de validar localmente la correcta ejecución de su programa, realizar un `push` de su solución a su laboratorio para su corrección. Para ello ejecute los siguientes comandos en un Terminal de Linux. **NOTA:** Los comandos a continuación debe ejecutarlos dentro de la carpeta `<carpeta-del-repositorio>`.

- Verificar con el siguiente comando que se han modificado los archivos correctos. Debería aparecer en rojo los archivos `asmMedia32.asm` y `asmMedia32womin.asm`.
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
- Finalmente revisar su nota en la página web del repositorio. Cualquier consulta comuníquese con su JP.
