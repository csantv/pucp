# cargar datos
datos = read.csv("bike_sharing.csv")
# pagos de usuarios casuales
num_casual = sum(datos$casual)
usd_casual = 2500000
# pagos de usuarios registrados
num_reg = sum(datos$registered)
usd_reg = num_reg * 3
# hallar promedio
usd_total = usd_casual + usd_reg
num_total = sum(datos$cnt)
prom_pagos = usd_total / num_total
