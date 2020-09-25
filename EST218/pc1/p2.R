library("DescTools")
# cargar datos
datos = read.csv("bike_sharing.csv")

casual = datos$casual[datos$hr == 8]
k = 9
A = max(casual) - min(casual)
c = ceiling(A/k)
b = seq(from = min(casual), by = c, length.out = k + 1)
Freq(casual, breaks = b)
ceiling(quantile(casual, 0.90))

registered = datos$registered[datos$hr == 8]
k = 9
A = max(registered) - min(registered)
c = ceiling(A/k)
b = seq(from = min(registered), by = c, length.out = k + 1)
Freq(registered, breaks = b)
ceiling(quantile(registered, 0.90))
