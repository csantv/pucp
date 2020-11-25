data = read.csv("auto-mpg.csv")
x = data$weight
y = data$mpg
reg = lm(y~x)
summary(reg)
