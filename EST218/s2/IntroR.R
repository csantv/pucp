# Lectura de datos
datos = read.csv("D:/iris.csv")

# Revisar primeras filas
head(datos)

# Acceder a la variable largo.sepalo
datos$largo.sepalo

# Estadisticas resumen de largo.sepalo
summary(datos$largo.sepalo)

# Frecuencias de variedad
summary(as.factor(datos$variedad))
