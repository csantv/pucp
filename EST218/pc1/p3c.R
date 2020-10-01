datos = read.csv("bike_sharing.csv")

#season = 1
#hr = 14

new_data = datos$casual[datos$season == 4 & datos$hr == 14]
barplot(new_data)
