datos = read.csv("electricidad.csv")

library(DescTools)

Freq(datos$electricidad)

hist(datos$electricidad,
     xlab = "Consumo en kWh",
     ylab = "Frecuencia",
     main = "Historigrama del consumo mensual en kWh
     en 50 hogares del distrito")

h=hist(datos$electricidad, plot = FALSE)
x.pol = c(min(h$breaks),h$mids,max(h$breaks))
y.pol = c(0, h$counts, 0)

plot(x.pol, y.pol, type = "b", col=2, lwd=2,pch=16,
     xlab="Consumo en kWh", ylab="Frecuencia",
     main="Poligono de Frecuencias del consumo
     mensual en kWh en 50 hogares del distrito")

h=hist(datos$electricidad,plot = FALSE)
x.pol=c(min(h$breaks),h$mids,max(h$breaks))
y.pol=c(0,h$counts,0)

plot(x.pol,y.pol,
     type = "b",col=2,lwd=2,pch=16,
     xlab="Consumo en kWh",
     ylab="Frecuencia",
     main="Pol?gono de Frecuencias del consumo mensual 
     en kWh en 50 hogares del distrito")
