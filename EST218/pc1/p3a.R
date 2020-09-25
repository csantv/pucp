library("DescTools")
# cargar datos
datos = read.csv("bike_sharing.csv")
# sumar numero de usuarios casuales y registrados
datos$total_users = rowSums(datos[,c("registered", "casual")])
# obtener subset del arreglo
arr = datos[,c("hr", "total_users")]
# combinar todos los datos
datacomb = aggregate(arr$total_users, by = list(hr=arr$hr), FUN=sum)
# generar grafico
barplot(datacomb$x,
        main = "Uso del servicio por clientes registrados y casuales
        durante una hora del dia",
        ylab = "Cantidad de clientes",
        xlab = "Hora del dia",
        names.arg = datacomb$hr,
        cex.names = .9)
