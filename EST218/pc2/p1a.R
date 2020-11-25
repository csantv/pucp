data = read.csv("auto-mpg.csv")
x = data$displacement
y = data$mpg
reg = lm(y~x)
summary(reg)