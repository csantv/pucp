# Leer archivo de datos
# y asignarlo al objeto datos
# se debe colocar como argumento la ruta del archivo

datos = read.csv("D:/calidad.csv")

# Tambi�n se puede leer 
# usando la funci�n file.choose() que abre
# una ventana de di�logo para buscar el archivo

# d = read.csv(file.choose())

# Usamos la funci�n "head" para observar las primeras
# filas del archivo

head(datos)


# Distribuci�n de frecuencias

# Frecuencias absolutas
n.j=table(datos$calidad)
n.j

# Frecuencias relativas
n=length(datos$calidad)
f.j=n.j/n
f.j

# Porcentajes
p.j=100*f.j
p.j

# Tabla
tab=cbind(n.j,f.j,p.j)
tab

# Gr�fico de barras
# La funci�n barplot usa como argumento
# las frecuencias no los datos!
barplot(f.j,
        xlab="Calidad del aire",
        ylab="Frecuencia relativa",
        main="Distribuci�n de frecuencias de la 
calidad del aire de una ciudad"
)

#Gr�fico de sectores circulares
# La funci�n  pie usa como argumento
# las frecuencias no los datos!
pie(f.j,
main="Distribuci�n de frecuencias de la 
calidad del aire de una ciudad")

#################################################
# Usando librer�a DescTools

# Instalar la librer�a
# Si est� instalada no es necesario ejecutar esta l�nea
install.packages("DescTools")

# Cargar librer�a
  library(DescTools)

Freq(datos$calidad)

