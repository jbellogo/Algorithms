## Simulating a pure jump process: Discretized #################################
set.seed(1234)

lam <- 1
T <- 5
N <- 100
count  <- rep(0, N+1)
for(j in 1:N){
  U <- runif(1)
  if(U <= lam * T/ N){
    ## We had a jump
    count[j+1] <- count[j] + 1 
  } else {
    count[j+1] <- count[j]
  }
}

plot(T*(0:N)/N, count,   xlab = "Time t", ylab = "N(t)", pch = ".")


## Simulating a pure jump process: Exact #######################################

T <- 5
totaltime <- 0
jumptimes <- c() 
while(totaltime < T){
  next_jumptime <- rexp(1, rate = lam)
  jumptimes <- c(jumptimes, totaltime + next_jumptime)
  totaltime <- totaltime + next_jumptime 
}
## Remove jumptimes >T
jumptimes <- jumptimes[jumptimes <= T]

## Plot 
numjumps <- length(jumptimes)
jumptimes_w0T <- c(0, jumptimes, T)
plot(NA, xlim = c(0, T), ylim = c(0, numjumps), xlab = "Time t",
     ylab = "N(t)")
for(i in 1:(numjumps+1)){
  lines( c(jumptimes_w0T[i],  jumptimes_w0T[i+1]  ), c(i-1, i-1), pch = ".")
}
  
