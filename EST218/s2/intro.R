datos = read.csv("iris.csv")

head(datos)

datos$largo.petalo

summary(datos$largo.sepalo)

summary(as.factor(datos$variedad))