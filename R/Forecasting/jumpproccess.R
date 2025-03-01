## Simulating a pure jump process: Discretized #################################
set.seed(1234)

sampleLogJump <- function(p_d, p_u, M_u, M_d){
  u = runif(1)
  ans = 0
  if (u>=p_d){
    ans = (-1/M_u)* log(abs(1- (u-p_d)/p_u))
  } else {
    ans = (1/M_d)*log(abs(u/p_d))
  }
  return(ans)
}

computeButterflyPay = function(ST, K1, K2, K3){
  pay = 0
  if (ST <= K1){
    pay = 0
  } else if (ST <= K2) {
    pay = ST-K1
  } else if (ST <= K3) {
    pay = K3-ST
  } 
  return(pay)
}


##############
# parameters #
r = 0.05
sigma = 0.15
T=1
S0 = 1
M_u = 3.04
M_d = 3.08
p_u = 0.34
p_d = 1-p_u
lam = 0.1
N = 1000 # timesteps
n = 50000 # 000 # simulations
k = p_u*M_u/(M_u-1) + (1-p_u)*M_d/(M_d+1) -1
delta_t = T/N
##############
## Sample path
priceButterfly = function(K1){
  K3 = 2*S0-K1
  K2 = (K1+K3)/2
  avPay = 0
  for (i in 1:n){
    St = S0
    for(j in 1:N){
      U <- runif(1)
      J = 1
      if(U <= lam * T/ N){
        # JUMP
        logJ = sampleLogJump(p_d, p_u, M_u, M_d)
        J = exp(logJ)
      } 
      Z <- rnorm(1)
      dynamics = (1 + (r - lam*k)*delta_t + sigma*sqrt(delta_t)*Z + (J-1))
      St = St*dynamics # the last St will be S_T
    }
    pay = computeButterflyPay(St, K1, K2, K3)
    avPay = avPay + pay/n
  }
  return(exp(-r*delta_t)*avPay)
}

x <- c()
y <- c()
for (k1 in seq(0.6, 0.9, 0.05)){
  y <- c(y, priceButterfly(k1))
  k3 = 2*S0 - k1
  x <- c(x, k3-k1)
}

plot(x,y, xlab = "(K3-K1)/2", ylab = "payout(S_T)")

# How does the computed option value depend on (K3-K1)/2? The payout depends on the three strikeprice, which are all dependent on K1
# Why is your observation reasonable. (K3 -K1)/2 = S0 -K1 This is just a function of K1 since S0 is a specified constant. 



#### ATTEMPT AT SECOND EXACT JUMP TIME SAMPLING
# 
# grid <- T*(0:N)/N
# delta_t = T/N
# S <- c(S0)
# k = p_u*M_u/(M_u-1) + (1-p_u)*M_d/(M_d+1) -1
# # Sample path
# current_time = delta_t
# for (t in grid[2:N+1]){
#   Z <- rnorm(1)
#   dynamics = (r - lam*k)*delta_t + sigma*sqrt(delta_t)*Z
#   print(dynamics)
#   if (length(jumptimes) >= 1) {
#     print("JUMP")
#     if (current_time >= jumptimes[1]){
#       logJ = sampleLogJump(p_d, p_u, M_u, M_d)
#       dynamics = dynamics + exp(logJ)-1
#       jumptimes = jumptimes[-1]
#     }
#   }
#   Sprior = S[length(S)]
#   Scurr = Sprior*dynamics
#   S = c(S, Scurr)
#   current_time = current_time + delta_t
# }
# 
# plot(grid, S)
