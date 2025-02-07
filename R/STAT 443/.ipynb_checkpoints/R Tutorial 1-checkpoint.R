# This tutorial has two parts:
# part 1: regression analysis for AirPAssenger data including fitting the model, residual diagnostics, and prediction
# part 2: an optimization problem to help with assignment #1

#making a time series
x = as.vector(AirPassengers)
x
plot(x)
x.timeseries = ts(x , start=1949 , frequency = 12)
x.timeseries
plot(x.timeseries)

#if there is no periodicity, leave frequency=1

#################################################
#### Part 1 : analysis of AirPassengers Data #### 
#################################################

data(AirPassengers) # Calling the built-in R data


plot(AirPassengers) # plotting the time-series data. Notice that the data is already in the form of a time series. To check this type AirPassengers and hit enter.
plot(log(AirPassengers))  # Plotting the log-transform of data


tim <- time(AirPassengers) #extracting the time from a time series object
cycle(AirPassengers) #extracting seasons from a periodic time series object
month <- as.factor(cycle(AirPassengers)) #creating factor/categorical variable for season
reg1 <- lm(log(AirPassengers)~tim+month) #fitting the model with linear trend based on time and including season in the model
summary(reg1)

#plotting the log-transformed data and the fit
plot(log(AirPassengers))
points(tim,predict.lm(reg1),type='l',col='red')

#plotting the original data and the fit
plot(AirPassengers)
points(tim,exp(predict.lm(reg1)),type='l',col='red')

# Graphical model diagnostics 
par(mfrow=c(2,2)) # Dividing the plotting page into 4 panels
plot(reg1$fitted, reg1$residuals , pch=16 , col=adjustcolor("black",0.5)) # plot of fitted values vs residuals 
abline(h=0,col="red" , lty=2, lwd=2)
#qq-plot of residuals
car::qqPlot(reg1$residuals , pch=16 , col=adjustcolor("black",0.7),
            xlab = "Theoretical Quantiles (Normal)" , ylab = "Sample Quantiles (r.hat)",
            main = "Normal Q-Q Plot")
plot(reg1$residuals, pch=16 , col=adjustcolor("black",0.5)) # plotting the residuals vs time
abline(h=0,col="red" , lty=2, lwd=2)# plotting a horizontal line at 0
acf(reg1$residuals , main="ACF Plot of Residuals") #sample acf plot of residuals
 
# fitting a model with quadratic time
tim2 <- tim^2
reg2 <- lm(log(AirPassengers)~tim+tim2+month) #alternative to reg2 <- lm(log(AirPassengers)~tim+tim2+month)
reg2 <- lm(log(AirPassengers)~tim+I(tim^2)+month)

# We will use orthogonal polynomials
tim = as.vector(tim)
reg2 <- lm(log(AirPassengers)~poly(tim,2,raw=FALSE)+month) #alternative to reg2 <- lm(log(AirPassengers)~tim+tim2+month)
summary(reg2)

#plotting the data and the fit
par(mfrow=c(1,1)) # Dividing the plotting page into 1 panel
plot(log(AirPassengers)) #plotidng the original data
points(tim,predict.lm(reg2),type='l',col='red') #adding the fitted values to the plot
 
# Graphical model diagnostics
par(mfrow=c(2,2)) # Dividing the plotting page into 4 panels
plot(reg2$fitted, reg2$residuals , pch=16 , col=adjustcolor("black",0.5)) # plot of fitted values vs residuals 
abline(h=0,col="red" , lty=2, lwd=2)
#qq-plot of residuals
car::qqPlot(reg2$residuals , pch=16 , col=adjustcolor("black",0.7),
            xlab = "Theoretical Quantiles (Normal)" , ylab = "Sample Quantiles (r.hat)",
            main = "Normal Q-Q Plot")
plot(reg2$residuals, pch=16 , col=adjustcolor("black",0.5)) # plotting the residuals vs time
abline(h=0,col="red" , lty=2, lwd=2)# plotting a horizontal line at 0
acf(reg2$residuals , main="ACF Plot of Residuals") #sample acf plot of residuals

# Fitting regular or orthogonal polynomial should not affect residuals, unless X^TX is singular and the model is not fitted.
par(mfrow=c(1,1))
reg2.reglar <- lm(log(AirPassengers)~poly(tim,2,raw=TRUE)+month) #alternative to reg2 <- lm(log(AirPassengers)~tim+tim2+month)
reg2.orthogonal <- lm(log(AirPassengers)~poly(tim,2,raw=FALSE)+month) #alternative to reg2 <- lm(log(AirPassengers)~tim+tim2+month)
reg2.reglar.resid = residuals(reg2.reglar)
reg2.orthogonal.resid = residuals(reg2.orthogonal)
plot(reg2.reglar.resid,reg2.orthogonal.resid)
abline(a=0,b=1,col="red") #45-degree line

# Diagnostic Tests for Residuals

# Testing normality with Shapiro-Wilk
residuals.reg2 = residuals(reg2) #extracting the residuals
shapiro.test(residuals.reg2) #Shapiro-Wilk test of normality H0: residuals are normal

# Testing Constant variance with FLigner-Killeem
#First, 6 groups of 24 obs.
plot(reg2$residuals, pch=16 , col=adjustcolor("black",0.5)) # plotting the residuals vs time
abline(v=c(1:5)*24 , col="red" , lwd=2, lty=2)
segments = factor(rep(1:6,each=24)) #creating 6 chunks to test variance homogeneity
fligner.test(residuals.reg2 , segments) # Fligner's test for H0:sigma1=sigma2=...=sigma6 (note that we made 6 chunks)

#Next, 12 groups of 12 obs.
plot(reg2$residuals, pch=16 , col=adjustcolor("black",0.5)) # plotting the residuals vs time
abline(v=c(1:11)*12 , col="red" , lwd=2, lty=2)
segments = factor(rep(1:12,each=12)) #creating 6 chunks to test variance homogeneity
fligner.test(residuals.reg2 , segments) # Fligner's test for H0:sigma1=sigma2=...=sigma6 (note that we made 6 chunks)


# Testing randomness with difference sign test and runs test
randtests::difference.sign.test(residuals.reg2)
randtests::runs.test(residuals.reg2 , plot = TRUE)


# Prediction for AirPassengers data
 
tim <- time(AirPassengers) #introducing time (t) 
cycle(AirPassengers) # Getting values for season
month <- as.factor(cycle(AirPassengers)) # Intoroducing season for regression (11 binary variables)
reg2 <- lm(log(AirPassengers)~tim+I(tim^2)+month) # Fitting the regression model
tim.new <- seq(1961,1963,length=25)[1:24] # Intoducing new time for forecatsting 2 years 1961 and 1962 (notice that it is 1:24 because 1963 should not be included)
month.new <- factor(rep(1:12,2)) # Introducing the season value for forecasting

new <- data.frame(tim=tim.new,month=month.new) # Putting the values for forecasting into a dataframe
a <- predict.lm(reg2,new,interval='prediction') # Computing the prediction as well as prediction interval
a


par(mfrow=c(1,1))
plot(AirPassengers,xlim=c(1949,1963),ylim=c(0,900)) #plotting the data

abline(v=1961,col='blue',lty=2) # adding a vertical line at the point where prediction starts
lines(exp(a[,1])~tim.new,type='l',col='red')# plotting the predict
lines(exp(a[,2])~tim.new,col='green') # plotting lower limit of the prediction interval
lines(exp(a[,3])~tim.new,col='green') # plotting upper limit of the  prediction interval

