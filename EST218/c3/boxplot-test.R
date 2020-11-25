data = c(126, 130, 130, 133, 136, 148, 148, 157, 189,199)
me = median(data)
q1 = 130
q3 = 157
ric = q3 - q1
li = q1 - 1.5 * ric
ls = q3 + 1.5 * ric

boxplot(data)
