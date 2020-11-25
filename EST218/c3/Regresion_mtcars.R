
# Decripci?n del conjunto de datos 
?mtcars

# Diagrama de dispersi?n
x = mtcars$hp
y = mtcars$mpg
plot(x,y, xlab="x (Potencia en hp)", 
     ylab = "y (Eficiencia en millas por gal?n)",
     main = "Diagrama de dispersi?n
     entre la potencia y la eficiencia")

# Covarianza
cov(x,y)

# Correlaci?n
cor(x,y)

###########
# Recta de regresi?n estimada

y.bar=mean(y)
x.bar=mean(x)

s.x=sd(x)
s.y=sd(y)

r.xy=cor(x,y)

b=r.xy*s.y/s.x
a=y.bar-b*x.bar

a
b

# El intercepto en este caso no tiene interpretaci?n pr?ctica
# Se espera que la eficiencia disminuya en 0.07mpg cuando la
# potencia del motor se incremente en 1 hp

# Coeficiente de determinaci?n

R.2=r.xy**2
R.2

# El 60.24% de la variabilidad de la eficiencia es explicada por 
# su relaci?n lineal con la potencia del motor.

#Estimaci?n para x=140
a+b*140

# Se espera que un auto con potencia del motor de 140 hp
# tenga una eficiencia de 20.55 mpg


#Diagrama de dispersi?n
#con recta estimada

plot(x,y,main=
       "Diagrama de dispersi?n entre la potencia 
y la eficiencia",xlab="Potencia en hp",
     ylab="Eficiencia en millas por gal?n")

abline(a,b,col=2)
# 
########################
# Recta de regresion estimada usando lm
lm(y~x)

reg=lm(y~x)
summary(reg)

coef(reg)

a=coef(reg)[1]
b=coef(reg)[2]

#Estimaci?n para x=140
a+b*140

#Diagrama de dispersi?n
#con recta estimada
plot(x,y, xlab="x (Potencia en hp)", 
     ylab = "y (Eficiencia en millas por gal?n)",
     main = "Diagrama de dispersi?n
     entre la potencia y la eficiencia")
abline(reg,col="red",lwd=2)

