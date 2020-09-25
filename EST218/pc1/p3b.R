library("DescTools")
# cargar datos
datos = read.csv("bike_sharing.csv")
# obtener subset de datos
arr = datos[,c("hr", "casual")]
# combinar todos los datos a partir de la hora
datacomb = aggregate(arr$casual, by = list(hr=arr$hr), FUN=sum)
# generar grafico
barplot(datacomb$x,
        main = "Uso del servicio por clientes casuales
        durante una hora del dia",
        ylab = "Cantidad de clientes",
        xlab = "Hora del dia",
        names.arg = datacomb$hr,
        cex.names = .9)
