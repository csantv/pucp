datos = read.csv("bike_sharing.csv")

barplot(datos$cnt)

summary(datos$cnt)

barplot()

median(datos$casual[datos$holiday == 0])
median(datos$casual[datos$holiday == 1])

mean(datos$casual[datos$holiday == 0])
mean(datos$casual[datos$holiday == 1])

var(datos$temp)
var(datos$windspeed)

sd(datos$temp)
sd(datos$windspeed)
