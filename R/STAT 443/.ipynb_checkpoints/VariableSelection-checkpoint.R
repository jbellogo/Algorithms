##########
# plup data
###########

# loading the pulp price data and plotting it
PulpPrice <- read.csv(file="pulppric.csv",header=TRUE) # Reading the data into R
price <- PulpPrice$Price # assigning the prices to the price variable
shipments <-  PulpPrice$Shipments # assigning shipments to the shipment variable

# Change K from 1 to 6 to get polynomial fits up to degree K polynomial
plot(price, shipments , pch=16 , cex=1.2 , main="World Pulp Prices and Shipment" )
Colours = c("black" , "red" , "steelblue" , "green" , "grey" , "pink" , "purple")
K=6
for(i in 1:K){
  model = lm(shipments~poly(price,i,raw=TRUE)) #lm(shipments~price + I(price^2)+...)
  ToPlot = data.frame(price=seq(min(price),max(price),length=500))
  temp = predict(model , newdata = ToPlot)
  lines(ToPlot$price,temp,col=Colours[i] , lwd=2)
}
legend("topright", 
       paste("Degree ", 1:K),
       col = Colours,
       lwd = 2, box.lwd = 0)


# Graphical diagnostics and the residuals for the 6 polynomial models.
for(p in 1:6){
  model <- lm(shipments~poly(price,p,raw=FALSE)) # fitting a simple linear regression model
  ToPlot = data.frame(price=seq(min(price),max(price),length=500))
  print(summary(model)) # gives the parameter estimates, R^2, p-values, etc.
  
  par(mfrow=c(3,2)) # Dividing the plotting page into 4 panels
  plot(model$fitted, model$residuals , pch=16 , col=adjustcolor("black" , 0.7)) # plot of fitted values vs residuals 
  title(main = paste0("Polynomial Model - p=",as.character(p)))
  abline(h=0,lty=2 , lwd=2 , col="red") # plotting a horizontal line at 0
  car::qqPlot(model$residuals , pch=16)
  title(main = paste0("Polynomial Model - p=",as.character(p)))
  plot(model$residuals, pch=16 , col=adjustcolor("black" , 0.7)) # # plotting the residuals vs time
  title(main = paste0("Polynomial Model - p=",as.character(p)))
  abline(h=0,lty=2 , lwd=2 , col="red") # plotting a horizontal line at 0
  acf(model$residuals) #sample acf plot of residuals
  
  #data with the fitted model
  plot(price, shipments , pch=16)
  title(main = paste0("Polynomial Model - p=",as.character(p)))
  temp = predict(model , newdata = ToPlot)
  lines(ToPlot$price,temp,col="blue" , lwd=2)
  
  #plot of y vs. y.hat
  plot(shipments~model$fitted , ylab="Observed y (shipment)" , xlab = "Fitted value"
        , pch=16 , col=adjustcolor("black",0.7))
  abline(a=0,b=1 , lty=2 , lwd=2 , col="red")
  title(main = paste0("y vs. y.hat - p=",as.character(p)))
}



#variable selection for different polynomial models (R2, Adj.R2, SE of prediction, AIC, AICc, BIC)
output = data.frame(p = NA , R2=NA , Pred.SE=NA, AdjR2=NA , AIC=NA, AICc=NA, BIC=NA )
for(p in 1:6){
  model <- lm(shipments~poly(price,p))
  Pred <- predict.lm(model, newdata=data.frame(price=c(750)),  interval="prediction",level=0.95) #predicted value along with prediction interval for the new observation price=750
  output[p,] = c(p , #degree 
                 summary(model)$r.squared , #R2
                 (Pred[3]-Pred[2])/(2*qt(0.975,(length(shipments)-p-1))), #SE(pred. at x0=750)
                 summary(model)$adj.r.squared, #Adjusted R2
                 AIC(model), #AIC
                 MuMIn::AICc(model), #AICc
                 BIC = BIC(model) #BIC
  )
}
round(output , 4)

# Stepwise model selection based on AIC/BIC for house price data
library(MASS)
house.price <- read.table(file="housedata.txt",header = TRUE) # Reading the data into R
model <- lm(Y~. , data=house.price)
stepAIC(model)


# Stepwise model selection based on AIC/BIC for shipment  data
X = poly(price,6,raw=FALSE)
for(i in 1:6) { #-- Create objects  'r.1', 'r.2', ... 'r.6' --
  nam <- paste("price", i, sep = "")
  assign(nam, X[,i])
}
model <- lm(shipments~price1+price2+price3+price4+price5+price6)

stepAIC(model , direction="both") #Stepwise model selection baded on AIC
step(model , k=2) #Stepwise model selection baded on AIC
step(model , k=log(dim(house.price)[1])) #Stepwise model selection baded on BIC

#manual calculation of AIC and BIC
BIC(model) #BIC
AIC(model) # AIC: note that this is different from that of the stepAIC (explain why)
-2*logLik(model)[1]+2*(model$rank+1) #AIC
MuMIn::AICc(model) # AICCc
AIC(model) + 2*(model$rank+1)*(model$rank+2)/(length(shipments)-(model$rank+1)-1) # AICCc


#Average Prediction Error (APSE)


# Prediction sum of squares
#set.seed(123)
#pred.indx = sample(1:25,5,replace = FALSE)
pred.indx = c(15 ,19 ,14 , 3 ,10)
#> pred.indx
#[1] 15 19 14  3 10

shipments.training = shipments[-pred.indx]
price.training = price[-pred.indx]

APSE = c()
for(p in 1:6){
  model <- lm(shipments.training~poly(price.training,p)) # including up to degree 6
  pred = predict(model, newdata=data.frame(price.training=price[pred.indx])) # prediction with the degree 6 model
  APSE[p] = mean((pred-shipments[pred.indx])^2)
}
round(APSE,2)
which.min(APSE)
plot(APSE , pch=16 , type="b")
points(which.min(APSE) , APSE[which.min(APSE)] , col=adjustcolor("red",0.5) , cex=1.5 , pch=16)


# k-fold CV
Shuffle = sample(1:length(shipments) , length(shipments) , replace = FALSE)
shipments.shuffled = shipments[Shuffle]
price.shuffled = price[Shuffle]

#Making the test sets (indices for the units) for the k folds for the CV process
number.of.folds=5
Size.Per.Fold = round(length(price.shuffled)/number.of.folds)
Folds=list()
for(i in 1:number.of.folds){
  START = Size.Per.Fold*(i-1)+1 
  END = min(Size.Per.Fold*i , length(price.shuffled))
  Folds[[i]] = c(START:END)
}
Folds

# Cross-validaiton calculations
cross.valid <- matrix(0, nrow = number.of.folds, ncol=6) #5-fold
for(k in 1:number.of.folds){
  x <- price.shuffled[-Folds[[k]]]
  y <- shipments.shuffled[-Folds[[k]]]
  for(i in 1:p){
    fitmod <- lm(y~poly(x,i))
    Pred = predict(fitmod , newdata = data.frame(x = price.shuffled[Folds[[k]]]))
    cross.valid[k,i] <-  sum((shipments.shuffled[Folds[[k]]] - Pred)^2/length(shipments.shuffled[Folds[[k]]]))
  }
}
CV.Err = apply(cross.valid, 2, mean)
plot(CV.Err, pch=16 , type='b',
     ylab="Estimated C.V. error (mean A.P.E)", xlab="p : polynomial degree", 
     main=paste0(as.character(number.of.folds),"-fold Cross-validation")
)
indx = which.min(CV.Err)
points(indx,CV.Err[indx] , pch=16 , col=adjustcolor("red" , 0.5), cex=1.5)

# And the final table for model selection is:
cbind(output , APSE , CV.Err = CV.Err)




