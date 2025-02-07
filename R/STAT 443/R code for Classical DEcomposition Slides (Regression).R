
# look up function ts: in particular: start, end, and frequency

data(AirPassengers) # Calling the built-in R data

plot(AirPassengers) # plotting the time-series data. Notice that the data is already in the form of a time series. To check this, type AirPassengers and hit enter.
plot(log(AirPassengers))  # Plotting the log-transform of data

tim <- time(AirPassengers) # Extracting time as the explanatory variate from the time series framework of data
cycle(AirPassengers) # Introducing month as the season
month <- as.factor(cycle(AirPassengers)) # Introducing month as the season
reg1 <- lm(log(AirPassengers)~tim+month) # Fitting the model reg1 with linear trend and seasonal effect
summary(reg1) # Details of the fit for model reg1

#Year=floor(tim) # You don't have to do this, but I have done it to totally seperate the effect of t and month
#reg1 <- lm(log(AirPassengers)~Year+month) # Fitting the model reg1 with linear trend and seasonal effect
#summary(reg1) # Details of the fit for model reg1

plot(log(AirPassengers))
points(tim,predict.lm(reg1),type='l',col='red') # superimpose the fit of model reg1 on the plot of the data
#points(tim,fitted.values(reg1),type='l',col='red') # superimpose the fit of model reg1 on the plot of the data
# Exponentiating the fitted values to reverse the log transformation
plot(AirPassengers)
points(tim,exp(predict.lm(reg1)),type='l',col='red') # superimpose the fit of model reg1 on the plot of the data

# Diagnostic plots for reg1 model
par(mfrow=c(2,2)) # Dividing the plotting page into 4 panels
plot(reg1$fitted, reg1$residuals) # plot of fitted values vs residuals
abline(h=0,lty=2,col='red') # plotting a horizontal line at 0
qqnorm(reg1$residuals) #qq-plot of residuals
qqline(reg1$residuals) # plotting the line, along which the dots in qq-plot should lie
plot(reg1$residuals) # plotting the residuals vs time
abline(h=0,lty=2,col='red') # plotting a horizontal line at 0
acf(reg1$residuals) #sample acf plot of residuals

# Testing normality and the homogeneity of the variance
residuals.reg1 = residuals(reg1) #extracting the residuals
shapiro.test(residuals.reg1) #Shapiro-Wilk test of normality H0: residuals are normal

indx = factor(rep(1:6,each=24)) #creating 6 chunks to test variance homogeneity
fligner.test(residuals.reg1 , indx) # Fligner's test for H0:sigma1=sigma2=...=sigma6 (note that we made 6 chunks)


tim2 = tim^2
reg2 <- lm(log(AirPassengers)~tim+tim2+month)
# The following alternative for reg2 helps with prediction. You will just need to provide tim, not tim^2 in the new data to predict.
#reg2 <- lm(log(AirPassengers)~tim+I(tim^2)+month) 

#Year2 <- Year^2
#reg2 <- lm(log(AirPassengers)~Year+Year2+month)

summary(reg2) # Details of the fit for model reg2

par(mfrow=c(1,1))
plot(log(AirPassengers))
points(tim,predict.lm(reg2),type='l',col='red') # superimpose the fit of model reg2 on the plot of the data

# Exponentiating the fitted values to reverse the log transformation
plot(AirPassengers)
points(tim,exp(predict.lm(reg2)),type='l',col='red') # superimpose the fit of model reg2 on the plot of the data


# Diagnostic plots for reg2 model
par(mfrow=c(2,2)) # Dividing the plotting page into 4 panels
plot(reg2$fitted, reg2$residuals) # plot of fitted values vs residuals
abline(h=0,lty=2,col="red") # plotting a horizontal line at 0
qqnorm(reg2$residuals) #qq-plot of residuals
qqline(reg2$residuals) # plotting the line, along which the dots in qq-plot should lie
plot(reg2$residuals) # plotting the residuals vs time
abline(h=0,lty=2,col="red") # plotting a horizontal line at 0
acf(reg2$residuals) #sample acf plot of residuals

# If you want a nicer qqplot
library(car)
qqPlot(reg2$residuals , pch=16) # plotting the line, along which the dots in qq-plot should lie


# Testing normality and the homogeneity of the variance
residuals.reg2 = residuals(reg2) #extracting the residuals
shapiro.test(residuals.reg2)

indx = factor(rep(1:6,each=24)) #creating 6 chunks to test variance homogeneity
fligner.test(residuals.reg2 , indx) # Fligner's test for H0:sigma1=sigma2=...=sigma6 (note that we made 6 chunks)


# Predicting the next 6 month
tim.new <- seq(1960,1960+5/12,length=6)
month.new <- factor(1:6)
data.new <- data.frame(tim=tim.new , month=month.new)
predict.lm(reg1 , data.new , interval='prediction')
predict.lm(reg2 , data.new , interval='prediction')

