datos = read.csv("calidad.csv")

head(datos)

n.j = table(datos$calidad)
n.j

n = length(datos$calidad)
n
f.j = n.j/n
f.j

p.j=100*f.j
p.j
tab=cbind(n.j,f.j,p.j)
tab
round(tab,2)

barplot(f.j,
        xlab = "calidad del aire",
        ylab = "frecuencia relativa",
        main = "Distribucion de frecuencias de la
        calidad del air de una ciudad")

library(DescTools)

Freq(datos$calidad)
