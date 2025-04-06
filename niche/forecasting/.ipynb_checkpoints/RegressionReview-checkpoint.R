

house.price <- read.table(file="housedata.txt", header=T)
house.price

#fit the model
model.fit <-  lm(Y ~ X1+X2+X3+X4+X5+X6+X7+X8+X9, data=house.price)
summary(model.fit)

# predict one data point
new <- data.frame(X1=3.634, X2=2 , X3=5.432 , X4=1.763 , X5=1.5 , X6=6, X7=3 , X8=29 , X9=0)
pre <- predict(model.fit, new, interval="prediction")
pre

# Testing if the reduced model would fit as well (has nothing to do with prediction power)
model.fit <-  lm(Y ~ X1+X2+X3+X4+X5+X6+X7+X8+X9, data=house.price)
model.fit.reduced <-  lm(Y ~ X1+X2, data=house.price)
anova(model.fit.reduced , model.fit)

summary(model.fit.reduced)

new.reduced <- data.frame(X1=3.634, X2=2)
pre.reduced <- predict(model.fit.reduced, new.reduced, interval="prediction")
pre.reduced

