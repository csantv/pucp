# Leer archivo de datos
# y asignarlo al objeto datos
# se debe colocar como argumento la ruta del archivo

datos = read.csv("D:/accidentes.csv")

# También se puede leer 
# usando la función file.choose() que abre
# una ventana de diálogo para buscar el archivo

# datos = read.csv(file.choose())

# Usamos la función "head" para observar las primeras
# filas del archivo

head(datos)


# Distribución de frecuencias
#################################################
# Usando librería DescTools

# Instalar la librería DescTools
# Si está instalada no es necesario ejecutar esta línea
# install.packages("DescTools")

# Cargar librería DescTools
library(DescTools)

# Usamos la función "as.factor()" para que al
# construir la tabla de frecuencias considere a los datos
# como cualitativos

Freq(as.factor(datos$accidentes))

# Gráfico de bastones
# Calculamos las frecuencias relativas
f.j=prop.table(table(datos$accidentes))
f.j

# La función plot usa como argumento
# las frecuencias no los datos!
plot(f.j,type="h",
     xlab="Número de accidentes",
     ylab="Frecuencia relativa",
     main="Distribución de frecuencias del 
número de accidentes",
     lwd=5
)






