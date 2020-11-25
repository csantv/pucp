# Ejecutar esta línea sí no ha instalado la librería EnvStats
# install.packages("EnvStats")

# Cargar la librería EnvStats
library(EnvStats)

# Estadísticas descriptivas
summaryFull(mpg~vs,data=mtcars,
            stats=c("n","mean", "median",
                    "sd","iqr","range","cv",
                    "skew","kurtosis"))

# Diagrama de cajas
boxplot(mpg~vs,data=mtcars,
        main="Diagrama de cajas de la eficiencia en mpg 
según tipo de motor",
        names=c("Motor en V", "Motor en línea"),
        xlab="Tipo de motor",
        ylab="Eficiencia en mpg")

