
## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ##
## Holt-Winters Algorithm ## 
## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ##


# Analysis of Inventory data
inventory <- read.table('invent15.csv')
inventory <- ts(inventory,frequency=12) #This is to introduce the monthly time-series data
par(mfrow=c(1,2))
plot(inventory , main="Time Series Plot of the Inventory Data")
acf(inventory , main="ACF: Inventory Data")


es <- HoltWinters(inventory, gamma = FALSE , beta = FALSE) # simple exponential smoothing
es
HW.predict = predict(es, n.ahead=5 , prediction.interval = TRUE , level=0.95)
HW.predict
plot(es, HW.predict, main="Exponential Smoothing")


hw <- HoltWinters(inventory, gamma = FALSE) #double exponential smoothing
hw
HW.predict = predict(hw, n.ahead=5 , prediction.interval = TRUE , level=0.95)
HW.predict
plot(hw, HW.predict, main="Double Exponential Smoothing")



# Analysis of wine data
wine <- read.table('wine.dat')
wine <- ts(wine,start=1980,frequency=12)
par(mfrow=c(1,2))
plot(wine , main="Time Series Plot of the Wine Data")
acf(wine , main="ACF: Wine Data")

hw.additive <- HoltWinters(wine,seasonal = "additive")
pred.additive = predict(hw.additive, n.ahead=5, prediction.interval = TRUE , level=0.95)
plot(hw.additive , pred.additive ,main="Holt-Winters Smoothing (Additive)")

hw.multiplicative <- HoltWinters(wine,seasonal = "multiplicative")
pred.multiplicative = predict(hw.multiplicative, n.ahead=5, prediction.interval = TRUE , level=0.95)
plot(hw.multiplicative,pred.multiplicative ,main="Holt-Winters Smoothing (Multiplicative)")


# Analysis of AirPassengers data
data(AirPassengers)

par(mfrow=c(2,1))
hw.ad <- HoltWinters(AirPassengers, seasonal = c("additive")) #Additive HW method
hw.ad
pred.ad = predict(hw.ad, n.ahead=12 , prediction.interval = TRUE , level=0.95)
pred.ad
plot(hw.ad, pred.ad,xlim=c(1949,1962), main="Additive Holt-Winters Smoothing")



hw.mul <- HoltWinters(AirPassengers, seasonal = c("multiplicative")) #Multiplicative HW method
hw.mul
pred.mul = predict(hw.mul, n.ahead=5 , prediction.interval = TRUE , level=0.95)
pred.mul
plot(hw.mul, pred.mul,xlim=c(1949,1962), main="Multiplicative Holt-Winters Smoothing")




