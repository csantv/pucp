library(EnvStats)

summaryFull(mpg~vs, data=mtcars,
            stats=c("n", "mean", "median",
                    "sd", "iqr", "range",
                    "cv", "skew", "kurtosis"))

boxplot(mpg~vs, data=mtcars,
        main="Diagrama de cajas de la eficiencia en mpg")
