library("DescTools")
# cargar datos
datos = read.csv("bike_sharing.csv")
# convertir temperatura
datos$temp = datos$temp * 47 - 8

# numero de intervalos
k = 8
# amplitud
A = max(datos$temp) - min(datos$temp)
# ancho de clase
c = ceiling(10^2 * A/k) / 10^2
# limites
b = seq(from = min(datos$temp), by = c, length.out = k + 1)
# frecuencia
Freq(datos$temp, breaks = b)
# grafico de ojiva
h = hist(datos$temp,
         plot = FALSE,
         breaks = b)
x.oj = c(h$breaks)
y.oj = c(0, cumsum(h$counts))
plot(x.oj, y.oj,
     type = "b",
     col = 2,
     pch = 16,
     xlab = "Temperatura en Celsius",
     ylab = "Frecuencia Acumulada",
     main = "Grafica de Ojiva de la Temperatura
     en la ciudad de Washington D.C. medida en 17379 periodos
     de una hora en el 2011 y 2012")
