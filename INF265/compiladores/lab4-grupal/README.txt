GRUPO 7:
LENGUAJE "OBSIDIAN"
===================================================================
INTEGRANTES
===================================================================
CODIGO             NOMBRE
-------------------------------------------------------------------
20172665           Christian Andre Carhuancho Rodríguez
...................................................................
INSTRUCCIONES:			DESCRIPCION
...................................................................
Dec			Permite decrementar en 1 la variable.
For Loop		Permite ejecutar n veces un grupo de instr.
Select			Permite elegir acciones en base a una var.
-------------------------------------------------------------------
20175488	   Angel Jesus Gonzales Aliaga
...................................................................
INSTRUCCIONES:			DESCRIPCION
...................................................................
Inc			Permite incrementar en 1 la variable.
While Loop		Permite ejecutar un bucle si cumple condic.
Condition		Permite ejecutar instr. si cumple condic.
-------------------------------------------------------------------
20142886	   Marco Antonio Bossio Principe
...................................................................
INSTRUCCIONES:			DESCRIPCION
...................................................................
Declaracion		Permite declarar variables en el lenguaje.
Asignacion		Permite asignar un numero a una variable.
Salidas			Permite mostrar datos en pantalla.
-------------------------------------------------------------------
20171878	   Carlos Santos Toro Vera
...................................................................
INSTRUCCIONES:			DESCRIPCION
...................................................................
showdate		Permite mostrar una fecha con formato.
showage			Permite mostrar la cantidad de años entre
			dos fechas.
toDate			Permite convertir una cadena a una fecha y
			asignarla a una variable.
===================================================================
Las pruebas del lenguaje se adjuntaran en el zip con el nombre de
prueba.txt. El lenguaje solo muestra la tabla cuando se encuentra
el EOF, es por eso que se necesita redireccionar la entrada de
datos al archivo txt.
Por ultimo, el archivo obsidian.y contiene las reglas del lenguaje,
este archivo debe compilarse con el comando yacc obsidian.y para
poder generar el archivo .c
Luego de haber compilado el archivo .c, debe redireccionar la
entrada y salida de datos de la siguiente manera.
./programa < prueba.txt > reporte.txt
De esta manera se podra apreciar mejor los datos de salida
obtenidos de ejecutar el programa prueba. La salida presenta
tres partes, la tabla de simbolos y codigo antes de interpretar
el codigo, la seccion de salida de datos despues de interpretar el
codigo y la tabla de simbolos luego de interpretar el codigo.
