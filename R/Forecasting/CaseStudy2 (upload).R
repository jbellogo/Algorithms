#######################
## AirPassengers Data ##
######################

library(astsa)


# Calling AirPassengers data, making training and validation sets
data(AirPassengers)
modelling.data <- window(AirPassengers,1949,1959+11/12)
validation.data <- window(AirPassengers,1960,1960+11/12)

# plotting the data
par(mfrow=c(2,1))
plot(modelling.data)
plot(log(modelling.data))

#Finding optimum power transformation, see that log is there.
power.seq = seq(-2,2,by=0.1)
group = factor(rep(1:6,each=22))
filgner.p.value=c()
for(i in 1:length(power.seq)){
  if(power.seq[i]!=0){
    temp = modelling.data^power.seq[i]
    filgner.p.value[i] = fligner.test(temp , group)$p.value
  }else{
    temp = log(modelling.data)
    filgner.p.value[i] = fligner.test(temp , group)$p.value
  }
}
plot(filgner.p.value)
abline(h=0.1 , col="red")
power.seq[which(filgner.p.value>0.1)] #all these are acceptable, though you should plot to make sure


# transformation due to non-constant variance
log.training.data <- log(modelling.data)
par(mfrow=c(3,1))
plot(log.training.data)
acf(log.training.data)
pacf(log.training.data)

#Unlike the lecture, let's do regular differencing first
Bx <- diff(log.training.data)
par(mfrow=c(3,1))
plot(Bx)
acf(Bx,lag.max=36)
pacf(Bx,lag.max=36)


#LEt's do only seasonal differencing
B12x <- diff(log.training.data , lag = 12)
par(mfrow=c(2,1))
plot(B12x)
acf(B12x,lag.max=36)
pacf(B12x,lag.max=36)


# seasonal differencing in lag 12
BB12x <- diff(Bx,lag=12)
par(mfrow=c(3,1))
plot(BB12x)
acf(BB12x,lag.max=36)
pacf(BB12x,lag.max=36)

par(mfrow=c(1,1))
acf(BB12x^2 , lag.max=36 , main="ACF of The Differenced Data Squared")


BB12x <- diff(Bx,lag=12)
par(mfrow=c(4,1))
plot(BB12x)
acf(BB12x,lag.max=36)
pacf(BB12x,lag.max=36)
acf(BB12x^2 , lag.max=36 )



# fitting the proposed models
fit1 <- sarima(log.training.data, p=0,d=1,q=1,P=0,D=1,Q=1,S=12)

fit2 <- sarima(log.training.data, p=0,d=1,q=1,P=1,D=1,Q=0,S=12)

fit3 <- sarima(log.training.data, p=1,d=1,q=0,P=0,D=1,Q=1,S=12)

fit4 <- sarima(log.training.data, p=1,d=1,q=0,P=1,D=1,Q=0,S=12)

fit5 <- sarima(log.training.data, p=1,d=0,q=0,P=1,D=1,Q=0,S=12)

fit6 <- sarima(log.training.data, p=1,d=0,q=0,P=2,D=1,Q=0,S=12)

fit7 <- sarima(log.training.data, p=2,d=0,q=0,P=1,D=1,Q=0,S=12)

fit8 <- sarima(log.training.data, p=2,d=0,q=0,P=2,D=1,Q=0,S=12)

# AIC/BIC
c(fit1$AIC , fit1$AICc , fit1$BIC)
c(fit2$AIC , fit2$AICc , fit2$BIC)
c(fit3$AIC , fit3$AICc , fit3$BIC)
c(fit4$AIC , fit4$AICc , fit4$BIC)# this one was not a chosen model though
c(fit8$AIC , fit8$AICc , fit8$BIC)

# Forecasting based on the final 3 models
par(mfrow=c(2,2))
fore1 <- sarima.for(log.training.data, n.ahead=12, 
                    p=0,d=1,q=1,P=0,D=1,Q=1,S=12)
title("SARIMA(0,1,1)x(0,1,1)_12")
lines(log(validation.data),col='blue',type='b',pch=16)

fore2 <- sarima.for(log.training.data, n.ahead=12, 
                    p=0,d=1,q=1,P=1,D=1,Q=0,S=12)
title("SARIMA(0,1,1)x(1,1,0)_12")
lines(log(validation.data),col='blue',type='b',pch=16)

fore3 <- sarima.for(log.training.data, n.ahead=12, 
                    p=1,d=1,q=0,P=0,D=1,Q=1,S=12)
title("SARIMA(1,1,0)x(0,1,1)_12")
lines(log(validation.data),col='blue',type='b',pch=16)

fore8 <- sarima.for(log.training.data, n.ahead=12, 
                    p=2,d=0,q=0,P=2,D=1,Q=0,S=12)
title("SARIMA(2,0,0)x(2,1,0)_12")
lines(log(validation.data),col='blue',type='b',pch=16)

# forecasting based on SARIMA(0,1,1)x(0,1,1)_12
lower <- fore1$pred-1.96*fore1$se
upper <- fore1$pred+1.96*fore1$se
fit <- fore1$pred
yband <- c(50,800)
plot(AirPassengers,xlim=c(1949,1961),ylim=yband,
        ylab='Air Passengers',main='SARIMA(0,1,1)x(0,1,1)_12')
lines(exp(fit),col='red',type='b',pch='*') 
lines(exp(lower),col='blue',lty=2)
lines(exp(upper),col='blue',lty=2)

# forecasting based on SARIMA(0,1,1)x(1,1,0)_12
lower <- fore2$pred-1.96*fore2$se
upper <- fore2$pred+1.96*fore2$se
fit <- fore2$pred
yband <- c(0,1000)
ts.plot(AirPassengers,xlim=c(1949,1961),ylim=yband,
        ylab='Air Passengers',main='SARIMA(0,1,1)x(1,1,0)_12')
lines(exp(fit),col='red',type='b',pch='*') 
lines(exp(lower),col='blue',lty=2)
lines(exp(upper),col='blue',lty=2)

# forecasting based on SARIMA(1,1,0)x(0,1,1)_12
lower <- fore3$pred-1.96*fore3$se
upper <- fore3$pred+1.96*fore3$se
fit <- fore3$pred
yband <- c(0,1000)
ts.plot(AirPassengers,xlim=c(1949,1961),ylim=yband,
        ylab='Air Passengers',main='SARIMA(1,1,0)x(0,1,1)_12')
lines(exp(fit),col='red',type='b',pch='*') 
lines(exp(lower),col='blue',lty=2)
lines(exp(upper),col='blue',lty=2)

#Complete this
# forecasting based on SARIMA(1,1,0)x(0,1,1)_12
p=2,d=0,q=0,P=2,D=1,Q=0,S=12
lower <- fore3$pred-1.96*fore3$se
upper <- fore3$pred+1.96*fore3$se
fit <- fore3$pred
yband <- c(0,1000)
ts.plot(AirPassengers,xlim=c(1949,1961),ylim=yband,
        ylab='Air Passengers',main='SARIMA(1,1,0)x(0,1,1)_12')
lines(exp(fit),col='red',type='b',pch='*') 
lines(exp(lower),col='blue',lty=2)
lines(exp(upper),col='blue',lty=2)



# Calculating PRESS for the final 3 models
mean((exp(fore1$pred)-validation.data)^2)
mean((exp(fore2$pred)-validation.data)^2)
mean((exp(fore3$pred)-validation.data)^2)
mean((exp(fore8$pred)-validation.data)^2)

#Forecasting the future 2 years. Notice that we are using the whole dataset this time.
FinalFit <- sarima(log(AirPassengers),p=0,d=1,q=1,P=1,D=1,Q=0,S=12)
future.forecast <- sarima.for(log(AirPassengers), n.ahead=24, 
                              p=0,d=1,q=1,P=1,D=1,Q=0,S=12)
lower <- future.forecast$pred-1.96*future.forecast$se
upper <- future.forecast$pred+1.96*future.forecast$se
fit <- future.forecast$pred
yband <- c(0,1000)
ts.plot(AirPassengers,xlim=c(1949,1963),ylim=yband,
        ylab='Air Passengers',main='SARIMA(0,1,1)x(1,1,0)_12')

x = c(time(upper) , rev(time(upper)))
y = c(exp(upper) , rev(exp(lower)))
polygon(x, y, col = "grey" , border =NA)

lines(exp(fit),col='red',type='b',pch=16 , cex=0.5) 
lines(exp(lower),col='black',lty=2)
lines(exp(upper),col='black',lty=2)


