# Leer archivo de datos
# y asignarlo al objeto datos
# se debe colocar como argumento la ruta del archivo

datos = read.csv("D:/accidentes.csv")

# Tambi�n se puede leer 
# usando la funci�n file.choose() que abre
# una ventana de di�logo para buscar el archivo

# datos = read.csv(file.choose())

# Usamos la funci�n "head" para observar las primeras
# filas del archivo

head(datos)


# Distribuci�n de frecuencias
#################################################
# Usando librer�a DescTools

# Instalar la librer�a DescTools
# Si est� instalada no es necesario ejecutar esta l�nea
# install.packages("DescTools")

# Cargar librer�a DescTools
library(DescTools)

# Usamos la funci�n "as.factor()" para que al
# construir la tabla de frecuencias considere a los datos
# como cualitativos

Freq(as.factor(datos$accidentes))

# Gr�fico de bastones
# Calculamos las frecuencias relativas
f.j=prop.table(table(datos$accidentes))
f.j

# La funci�n plot usa como argumento
# las frecuencias no los datos!
plot(f.j,type="h",
     xlab="N�mero de accidentes",
     ylab="Frecuencia relativa",
     main="Distribuci�n de frecuencias del 
n�mero de accidentes",
     lwd=5
)






