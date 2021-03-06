# Leer archivo de datos
# y asignarlo al objeto datos
# se debe colocar como argumento la ruta del archivo

datos = read.csv("D:/electricidad.csv")

# Tambi�n se puede leer 
# usando la funci�n file.choose() que abre
# una ventana de di�logo para buscar el archivo

# d = read.csv(file.choose())

# Usamos la funci�n "head" para observar las primeras
# filas del archivo

head(datos)


# Distribuci�n de frecuencias

#########################################
# tabla de frecuencias 7 categorias
# en este caso es el default del R

# Instalar la librer�a DescTools
# Si est� instalada no es necesario ejecutar esta l�nea
# install.packages("DescTools")

# Cargar librer�a DescTools
library(DescTools)

# Tabla de frecuencias
Freq(datos$electricidad)

# Histograma
# La funci�n histograma usa como argumento
# los datos!
hist(datos$electricidad,
     xlab="Consumo en kWh",
     ylab="Frecuencia",
     main="Histograma del consumo mensual en kWh
     en 50 hogares del distrito"
     )

# Pol�gono de Frecuencias
h=hist(datos$electricidad,plot = FALSE)
x.pol=c(min(h$breaks),h$mids,max(h$breaks))
y.pol=c(0,h$counts,0)

plot(x.pol,y.pol,
     type = "b",col=2,lwd=2,pch=16,
     xlab="Consumo en kWh",
     ylab="Frecuencia",
     main="Pol�gono de Frecuencias del consumo mensual 
     en kWh en 50 hogares del distrito")


# Gr�fico de Ojiva
h=hist(datos$electricidad,plot=FALSE)
x.oj=c(h$breaks)
y.oj=c(0,cumsum(h$counts))

plot(x.oj,y.oj,type = "b",col=2,lwd=2,pch=16,
     xlab="Consumo en kWh",
     ylab="Frecuencia",
     main="Gr�fico de Ojiva del consumo mensual 
     en kWh en 50 hogares del distrito")


#################################################
# Consideremos ahora construir la tabla de frecuencias
# y el histograma usando 6 intervalos

# Numero de intervalos
k=6
# Amplitud
A=max(datos$electricidad)-min(datos$electricidad)
# Ancho de clase
c=ceiling(A/k)

# Esta �ltima l�nea solo redondea a enteros, en caso se requiera, 
# por ejemplo, a dos decimales puede usar
# c=ceiling(10^2*A/k)/10^2

# Limites
b = seq(from=min(datos$electricidad),
    by =c,
    length.out=k+1)

Freq(datos$electricidad,breaks = b)

hist(datos$electricidad, breaks = b,
     xlab="Consumo en kWh",
     ylab="Frecuencia",
     main="Histograma del consumo mensual en kWh
     en 50 hogares del distrito"
)

