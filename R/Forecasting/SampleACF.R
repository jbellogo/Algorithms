
# sample ACF for iid noise [N(0,1)]
X <- rnorm(100) # generating (independently) 100 realizations of N(0,1)
par(mfrow=c(2,1)) #dividing the page into 2 rows and one column
plot(X,type='l',main='iid noise') #plotting the data
acf(X,main='sample ACF for iid noise') # plotting the acf


# sample ACF for data with trend
a <- seq(1,100,length=200)
X <- 22-15*a+0.3*a^2+rnorm(200,500,50) #simulating data
par(mfrow=c(2,1)) #dividing the page into 2 rows and one column
ts.plot(X) # time series plot of the data
acf(X) #sample acf of the data

# sample ACF for data with trend and seasonal component
a <- seq(1,10,length=200)
X <- 22-15*a+a^2+5*sin(20*a)+rnorm(200,20,2)
par(mfrow=c(2,1)) #dividing the page into 2 rows and one column
ts.plot(X)
acf(X)

# sample ACF for US Accidental Deaths data
data(USAccDeaths) #calling the data
par(mfrow=c(2,1)) #dividing the page into 2 rows and one column
plot(USAccDeaths,type='l',main='# of Accidental deaths in US') #plotting the data
acf(USAccDeaths,main='sample ACF for US accidental deaths data',lag.max=24) # plotting the acf


# a simulation example with substantial deterministic periodicity
X <- sin(1:200) #generating purely periodic data
par(mfrow=c(2,1))
plot(X,type='l')
acf(X)


# Introducing noise to the previous case
sigma  = 3 #standard deviation of the noise term. Change and see the effect on sample ACF
X <- sin(1:200)+rnorm(200,0,sigma) 
par(mfrow=c(2,1))
plot(X,type='l')
title(main=expression(sigma==3))
acf(X)


# a simulation example with substantial deterministic periodicity
X <- 1:500+100*sin(1:500) #generating data with trend and periodic component
par(mfrow=c(2,1))
plot(X,type='l')
acf(X)

# AR(1) : X(t)=phi*X(t-1)+Z(t). Note that for |phi|=1 you ahve a random walk.
phi= 1
Z = rnorm(1) #the first value of Z, i.e. Z(1)
X=rep(NA,100) # making a vector of size 100 for realizations of X(t) to fill it
X[1] = Z # the first observation in X, i.e. X(1) is, simply Z(1)
for(i in 2:200){
  Z=rnorm(1)
  X[i] = phi*X[(i-1)]+Z
}
plot(X,type="l")


