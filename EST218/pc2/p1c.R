data = read.csv("auto-mpg.csv")
x = data$displacement
y = data$mpg
cor(x, y)^2

data = read.csv("auto-mpg.csv")
x = data$weight
y = data$mpg
cor(x, y)^2
