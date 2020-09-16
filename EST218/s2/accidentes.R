datos = read.csv("accidentes.csv")

Freq(as.factor(datos$accidentes))

Freq(datos$accidentes)

f.j=prop.table(table(datos$accidentes))
f.j

plot(f.j,
     type = "h",
     lwd = 5,
     xlab = "Numero de accidentes",
     ylab = "Frecuencia relativa",
     main = "Distribucion de frecuencias
     del numero de accidentes")
