# Leer archivo de datos
# y asignarlo al objeto datos
# se debe colocar como argumento la ruta del archivo

datos = read.csv("D:/calidad.csv")

# También se puede leer 
# usando la función file.choose() que abre
# una ventana de diálogo para buscar el archivo

# d = read.csv(file.choose())

# Usamos la función "head" para observar las primeras
# filas del archivo

head(datos)


# Distribución de frecuencias

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

# Gráfico de barras
# La función barplot usa como argumento
# las frecuencias no los datos!
barplot(f.j,
        xlab="Calidad del aire",
        ylab="Frecuencia relativa",
        main="Distribución de frecuencias de la 
calidad del aire de una ciudad"
)

#Gráfico de sectores circulares
# La función  pie usa como argumento
# las frecuencias no los datos!
pie(f.j,
main="Distribución de frecuencias de la 
calidad del aire de una ciudad")

#################################################
# Usando librería DescTools

# Instalar la librería
# Si está instalada no es necesario ejecutar esta línea
install.packages("DescTools")

# Cargar librería
  library(DescTools)

Freq(datos$calidad)

