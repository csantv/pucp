# cargar datos
datos = read.csv("bike_sharing.csv")
# convertir temperatura
datos$temp = datos$temp * 47 - 8

quantile(datos$temp, 0.95)
