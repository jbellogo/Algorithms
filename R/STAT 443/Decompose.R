# This file includes the codes for the decompose function

# Analysis of Denmark Birth data
Birth <- read.table('denmark.txt',header=TRUE)
Birth <- ts(Birth$birth,start=1900,frequency=12)
plot(Birth)

# Classical decomposition (Additive model)
Additive.Decomposition.BirthData = decompose(Birth , type = "additive")
plot(Additive.Decomposition.BirthData)

#Plotting the component of the classical decomposition one at a time
plot(Additive.Decomposition.BirthData$trend)
plot(Additive.Decomposition.BirthData$seasonal[1:12]) #Plotting one period
plot(Additive.Decomposition.BirthData$seasonal) #Plotting the seasonal component over the data window
plot(Additive.Decomposition.BirthData$random)


sum(Additive.Decomposition.BirthData$seasonal[1:12]) #checking that sum(st)=0


resid = decompose(Birth)$random
plot(resid)

Time = time(resid)[1:250]
plot(resid[1:250] ~ Time,type="l")

resid <- as.vector(na.omit(resid)) 
acf(resid,main="ACF random component Y[t]") 

acf(diff(resid,lag=12),
    main="ACF of (1-B12)Y[t] = Y[t]-Y[t-12]")
plot(diff(resid,lag=12) , type="l" , 
     main="Plot of (1-B12)Y[t] = Y[t]-Y[t-12]")


