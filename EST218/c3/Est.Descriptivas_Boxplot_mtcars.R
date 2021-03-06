# Ejecutar esta l�nea s� no ha instalado la librer�a EnvStats
# install.packages("EnvStats")

# Cargar la librer�a EnvStats
library(EnvStats)

# Estad�sticas descriptivas
summaryFull(mpg~vs,data=mtcars,
            stats=c("n","mean", "median",
                    "sd","iqr","range","cv",
                    "skew","kurtosis"))

# Diagrama de cajas
boxplot(mpg~vs,data=mtcars,
        main="Diagrama de cajas de la eficiencia en mpg 
seg�n tipo de motor",
        names=c("Motor en V", "Motor en l�nea"),
        xlab="Tipo de motor",
        ylab="Eficiencia en mpg")

