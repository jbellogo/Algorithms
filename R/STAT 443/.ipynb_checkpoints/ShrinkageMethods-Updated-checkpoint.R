# Simulating the data used in the slides.
set.seed(443)
X = matrix(rnorm(50*30),nrow=50)
beta = c(5 , runif(10,2,3) , runif(20,0,1))
y = as.vector(cbind(1,X)%*%beta) + rnorm(50,sd=1) #y=X*beta+epsilon
head(data.frame(X,y)) #checking out the dataset to be used for analysis

# Fitting a simple linear regression model
LinearModel = lm(y~X)
summary(LinearModel)

#install.packages("glmnet") # If you do not have the package glmnet run this only once forever
library(glmnet) # calling the glmnet library
vignette("glmnet")
## https://glmnet.stanford.edu/articles/glmnet.html

#Fitting the Ridge model with lambda=0.5
fit.glment.0.5=glmnet(X , y , alpha=0 , lambda=0.5,
                  standardize=TRUE, intercept = TRUE ,  family = "gaussian")
fit.glment.0.5

#Fitting the Ridge model with lambda=1.5
fit.glment.1.5=glmnet(X , y , alpha=0 , lambda=1.5,
                  standardize=TRUE, intercept = TRUE ,  family = "gaussian")
fit.glment.1.5


# lm.ridge is another function (from the MASS package ) which 
# fits the ridge model. However, it is slightly different from 
# the glmnet function hence the lambdas are not the same. 
# We will use glmnet because it has  a cross-validation function associated with it.

#install.packages("MASS") # If you do not have the package MASS run this only once forever
library(MASS)
# Note that the lambda in the method below is not the same as the lambda in glmnet. See the note below.
fit.lm.ridge = lm.ridge(y~X , lambda=2.706817) #This is simply a different method, but it has a different result because it mnimizes MSE and also centralizes y
fit.lm.ridge

beta.glment.0.5 = matrix(predict(fit.glment.0.5,type="coef"),ncol=1)
# You may also use coef(fit.glment.0.5) to extract the coefficients.

Fitted.glment.0.5 = cbind(1,X)%*%beta.glment.0.5
#another way to get the fitted values from glmnet object in below. 
#Predicted = predict(fit.glment.0.5,newx=X,type="response") #This does not work on lm.rige object
beta.lm.ridge = coef(fit.lm.ridge)
Fitted.lm.ridge = cbind(1,X)%*%beta.lm.ridge

c(sum(beta.glment.0.5^2) , sum(beta.lm.ridge^2)) # Checking if the lambdas for the different methods are doing the same amount of shrinkage

data.frame(Fitted.glment.0.5 , Fitted.lm.ridge)#Comparing the fitted values of the two methods glmnet and lm.ridge when lambdas are adjusted

par(mfrow=c(1,1))

# checking the quality of the fit (plotting y vs. y.hat)
plot(y,Fitted.glment.0.5 , pch=16 , col=adjustcolor("black",0.5) , main="glmnet fit") # Fit of the glmnet
abline(a=0,b=1)

plot(y,Fitted.lm.ridge, pch=16 , col=adjustcolor("black",0.5),main="lm.ridge fit") # fit of the lm.ridge
abline(a=0,b=1)

plot(Fitted.lm.ridge , Fitted.glment.0.5, pch=16 , col=adjustcolor("black",0.5),
     xlab = "lm.ridge output with lambda=2.706817" , ylab = "glmnet output with lambda=0.5")
abline(a=0,b=1)

# note that in this case, the two functions glmnet and lm.ridge resulted in exactly the same fits
# all we needed to do was to find the two lambda values which are associated with each other between the two functions.

##### ##### ##### ##### ##### ##### ##### ##### ###
# Because we would like to use CV, we use glmnet. #
##### ##### ##### ##### ##### ##### ##### ##### ###

# Putting the coefficients (true parameter, OLS estimates, Ridge1(lambda=0.5) and Ridge2(lambda=1.5) in one dataframe)
# Note that since the model does not have an intercept, we are ok with fit.glment.0.5$beta 
Coef = data.frame(Truth = beta , 
                  LinearRegression = LinearModel$coef , 
                  Ridge.Lambda.0.5 = c(fit.glment.0.5$a0 , fit.glment.0.5$beta[,1]),
                  Ridge.Lambda.1.5 = predict(fit.glment.1.5,type="coef")[,1])
Coef

#Plotting the coefficients
#Note below that beta0.hat is not part of the penalty, but we have plotted it.
par(mar=c(8.5,5,2,2))
plot(NA , ylim=c(-.5,5), xlim=c(0.75,4.75) , axes = FALSE,xlab="",ylab="Parameter Velues" , cex.lab=1.2)
axis(1 , cex.axis=1.2 , at = 1:4 , 
     labels = c("Truth" , "OLS" , "Ridge (lam=0.5)" , "Ridge (lam=2)"),
     las=2)
axis(2 , cex.axis=1.2)
for(i in 1:30){
  points(1:4,Coef[i,],col=adjustcolor(1:4 , .5) , pch=16)
  lines(1:4,Coef[i,],col="grey",lty=2)
}

text( 1:4 , 3.9 , round(apply(Coef , 2 , function(x) sum(x[-1]^2)),2) )
text(4.7, 3.9 ,expression(sum(hat(beta[j])^2)))


#########################
## House Price Example ##
#########################

house.price <- read.table(file="housedata.txt",header = TRUE) # Reading the data into R
X = as.matrix(house.price[,1:9]) #Note that X does NOT include a column of 1s
Y = house.price[,10]

# It turns out that a model without an intercept provides a better fit (check this yourself!)
fit.lm <- lm(Y~., data=house.price)
summary(fit.lm)
fit.lm <- lm(Y~-1+., data=house.price)
summary(fit.lm)

#Note that at lambda=0 all are the same (lm, lm.ridge, and glmnet), though glmnet is off by round-off error
fit.ridge1=glmnet(X , Y , alpha=0 , lambda=0,
                  standardize=TRUE, intercept = FALSE ,  family = "gaussian")
fit.ridge2=lm.ridge(Y~-1+X,lambda=0) #Note that lm.ridge for lamb=0 given lm result

# Note that glmnet for lambda=0 does not output exactly the same coefficients as the lm function
data.frame(GLMNET = predict(fit.ridge1,type="coef")[,1],
           LMRIDGE = c(NA,coef(fit.ridge2)),
           OLS = c(NA,coef(fit.lm)))


# plotting the SSE as a function of lambda to find the best lambda (WITHOUT cross-validation).
lambda.list <- seq(0, 0.1,length=1000)
rss.lam <- c()
for(lambda in lambda.list){
  # if you want to use lm.ridge function instead of glmnet,
  # then activate the next two lines, and comment out the fit.ridge, COEF and res based on glmnet
  #fit.ridge <-  lm.ridge(Y ~., lambda=lambda.list[i], data=house.price )	
  #res <- Y- X%*%(coef(fit.ridge))
  fit.ridge=glmnet(X , Y , alpha=0 , lambda=lambda,
                   standardize=TRUE, intercept = FALSE ,  family = "gaussian")
  COEF=predict(fit.ridge,type="coef")[,1]
  # res = Y - predict(fit.ridge)
  res <- Y- cbind(1,X)%*%t(t(COEF))
  rss.lam <- c(rss.lam , sum(res^2))
}
plot(lambda.list,rss.lam, type='l' )


# RIDGE path WITHOUT intercept
# It turns out that a model without an intercept provides a better fit (check this yourself!)
fit.ridge.range=glmnet(X , Y , alpha=0 , lambda=seq(0,15,length=100),
                       standardize=TRUE, intercept = FALSE ,  family = "gaussian")
Y.lim = extendrange(coefficients(fit.ridge.range))
plot(1:15, main="Shrinkage of parameters (Ridge)",xlab="lambda", ylab="beta", xlim=c(0,20), ylim=Y.lim, type="n")
for(i in 1:10){
  lines( fit.ridge.range$lambda , predict(fit.ridge.range,type="coef")[i,], lty=i, col=i)
}
legend("topright", legend= paste0("beta",0:9), 
       lty=1:10, col=1:10,bty = "n")

#extracting all beta values for lambda=0.3030303
predict(fit.ridge.range,type="coef")[,3]
 
## CV for finding lambda
## You can provide the vector argument lambda as well. Note that you provide lambda and NOT log(lambda)
CV = cv.glmnet(X , Y, alpha=0 ) #alpha=0 for Ridge and 1 for LASSO
CV
plot(CV)

# It turns out that a model without an intercept provides a better fit (check this yourself!)
fit.ridge.range=glmnet(X  , Y , alpha=0 , lambda=CV$lambda.min,
                       standardize=TRUE, intercept = FALSE ,  family = "gaussian")
Fitted.lamMin = predict(fit.ridge.range,newx = X,type="response") 

fit.ridge.range2=glmnet(X , Y , alpha=0 , lambda=CV$lambda.1se,
                       standardize=TRUE, intercept = FALSE ,  family = "gaussian")
Fitted.lam1SE = predict(fit.ridge.range2,newx = X,type="response") 
#Fitted2 = cbind(1,X)%*%matrix(predict(fit.ridge.range2,type="coef") , nrow=10) This is the smae thing as the line above

#Checking the difference between the two lambda values
data.frame(Y=Y , Fit.Lambda.min = Fitted.lamMin[,1] , Fit.Lambda.1se = Fitted.lam1SE[,1])
plot(Fitted.lamMin,Fitted.lam1SE , pch=16, col=adjustcolor("steelblue",0.7))

plot(Y~Fitted.lamMin , pch=16 , col=adjustcolor("steelblue",0.7),
     main = paste0("lambda.min=",as.character(round(CV$lambda.min,3))))
abline(a=0,b=1 , lty=2, lwd=2)

plot(Y~Fitted.lam1SE , pch=16 , col=adjustcolor("steelblue",0.7),
     main = paste0("lambda.1se=",as.character(round(CV$lambda.1se,3))))
abline(a=0,b=1 , lty=2, lwd=2)

# Lets check MSE and see which model performs better.
c(mean((Y-Fitted.lamMin)^2) , mean((Y-Fitted.lam1SE)^2))
# It seems (as expected) the model with lamMin performs better 


###########
## LASSO ##
###########

# This is the same simulated data from the beginning of this code file
set.seed(443)
X = matrix(rnorm(50*30),nrow=50)
beta = c(5 , runif(10,2,3) , runif(20,0,1))
y = as.vector(cbind(1,X)%*%beta) + rnorm(50,sd=1)
LinearModel = lm(y~X)

# We just refit the ridge models just in case they ahve been overwritten with something else.
fit.ridge1=glmnet(X , y , alpha=0 , lambda=0.5,
                  standardize=TRUE, intercept = TRUE ,  family = "gaussian")
fit.ridge2=glmnet(X , y , alpha=0 , lambda=1.5,
                  standardize=TRUE, intercept = TRUE ,  family = "gaussian")

# Fitting LASSO models with two values of lambda: 0.5 and 1.5
fit.LASSO1=glmnet(X , y , alpha=1 , lambda=0.5,
                  standardize=TRUE, intercept = TRUE ,  family = "gaussian")
fit.LASSO2=glmnet(X , y , alpha=1 , lambda=1.5,
                  standardize=TRUE, intercept = TRUE ,  family = "gaussian")

# Putting all coefficients from the true model, Ridge models, and LASSO models all in one data-frame
Coef = data.frame(LASSO.large = predict(fit.LASSO2,type="coef")[,1],
                  LASSO.Small = predict(fit.LASSO1,type="coef")[,1],
                  LinearRegression = LinearModel$coef , 
                  Truth = beta , 
                  LinearRegression = LinearModel$coef , 
                  Ridge.Small = predict(fit.ridge1,type="coef")[,1],
                  Ridge.large = predict(fit.ridge2,type="coef")[,1])
Coef

# Plotting the coefficient estimates
par(mar=c(9,5,2,2))
plot(NA , ylim=c(-.5,5), xlim=c(0.75,7.75) , axes = FALSE,xlab="",ylab="Parameter Velues" , cex.lab=1.2)
axis(1 , cex.axis=1.2 , at = 1:7 , 
     labels = c( "LASSO(lam=2)", "LASSO(lam=0.5)", "OLS", "Truth" , "OLS" , "Ridge(lam=0.5)" , "Ridge(lam=2)"  ),
     las=2)
axis(2 , cex.axis=1.2)
for(i in 1:30){
  points(1:7,Coef[i,],col=adjustcolor(c(4:2,1:4) , .5) , pch=16)
  lines(1:7,Coef[i,],col="grey",lty=2)
}
abline(h=0)

text( 4:7 , 3.9 , round(apply(Coef[,4:7] , 2 , function(x) sum(x[-1]^2)),2) )
text(3, 3.9 ,expression(sum(hat(beta[j])^2)))

text(1:4 , 3.5 , round(apply(Coef[,c(1:4)] , 2 , function(x) sum(abs(x[-1]))),2) )
text(5, 3.5 ,expression(sum(abs(hat(beta[j])))))


################
## LASSO Path ##
################
# Here we generate the LASSO model for many vallues of lambda for variable selection purposes
X = as.matrix(house.price[,1:9])
Y = house.price[,10]

# It turns out that a model without an intercept provides a better fit (check this yourself!)
fit.LASSO.range=glmnet(X , Y , alpha=1 , lambda=seq(0,10, length =200),
                       standardize=TRUE, intercept = FALSE ,  family = "gaussian")

# Extending the range of the vertical axis so the plot is nicer
Y.lim = extendrange(coefficients(fit.LASSO.range))
plot(1:15, main="Shrinkage of parameters (LASSO)",xlab="lambda", 
     ylab="beta", xlim=c(0,12), ylim=Y.lim, type="n")

for(i in 1:10){
  lines( fit.LASSO.range$lambda, predict(fit.LASSO.range,type="coef")[i,] , lty=(i), col=(i))
}
legend("topright", legend= paste0("beta",0:9), 
       lty=1:10, col=1:10,bty = "n")


## CV for finding lambda
## Similar to ridge, you can provide the vector of lambda here in the cv.glmnet function
CV = cv.glmnet(X , Y, alpha=1 ) #alpha=0 for Ridge and 1 for LASSO
CV
plot(CV)

# Predicting the price of a new house with X=(3.634 , 2, 5.432, 1.763, 1.5, 6, 3, 29, 0) variables

X = as.matrix(house.price[,1:9]) #Note that X does NOT include a column of 1s
Y = house.price[,10]
LASSO.CV.Model=glmnet(X , Y , alpha=1 , lambda=CV$lambda.1se,
                  standardize=TRUE, intercept = TRUE ,  family = "gaussian")

predict(LASSO.CV.Model,type="nonzero")# the variables left in the model with the given penalty
LASSO.CV.Model$beta #the non-zero betas
predict(LASSO.CV.Model,type="response",newx=c(3.634 , 2, 5.432, 1.763, 1.5, 6, 3, 29, 0))


# Variable selection 
# if you don't have this package, run install.packages("lars")
library(lars)
par(mfcol=c(1,2)) # to divide the plot to a 1x2 panel

house.lasso <- lars(X, Y, type="lasso" , trace=TRUE)
house.lasso
plot(house.lasso)

house.step <- lars(X, Y, type="stepwise", trace=TRUE)
house.step
plot(house.step)

# Compare the best LASSO model with the best Ridge model in terms of prediction
# As an exercise, put aside 3 random properties, and use OLS, ridge, and lasso to 
# find the best model interms of prediction power. 


#####################
## Elastic Net Fit ##
#####################

fit.ElasticNet.range=glmnet(X , Y , alpha=0.5 , lambda=seq(0,10, length =200),
                       standardize=TRUE, intercept = FALSE ,  family = "gaussian")

# Extending the range of the vertical axis so the plot is nicer
Y.lim = extendrange(coefficients(fit.ElasticNet.range))
plot(1:15, main="Shrinkage of parameters (Elastic Net)",xlab="lambda", 
     ylab="beta", xlim=c(0,12), ylim=Y.lim, type="n")

for(i in 1:10){
  lines( fit.ElasticNet.range$lambda, predict(fit.ElasticNet.range,type="coef")[i,] , lty=(i), col=(i))
}
legend("topright", legend= paste0("beta",0:9), 
       lty=1:10, col=1:10,bty = "n")


## CV for finding lambda
## Similar to ridge, you can provide the vector of lambda here in the cv.glmnet function
CV = cv.glmnet(X , Y, alpha=0.5 ) #alpha=0.5 for elastic net with alpha=0.5
CV
plot(CV)

# In practice, you can try alpha = c(0,0.25,0.5,0.75,1). Put this in a loop and decide which 
# model for Elastic Net is the best.

