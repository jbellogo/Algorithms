
############################################################## 
##### An optimization example to help with Assignment #1 #####
############################################################## 

# Suppose, interest is in minimizing the function f(x,y) = 5*x1+(x^4-16*(x^2)+5*x)+(y^4-16*(y^2)+5*y)

f = function(x,y) { 
  temp = 5*x+(x^4-16*(x^2)+5*x)+(y^4-16*(y^2)+5*y)
  return(temp)
}
x = y = seq(-4,4,length=75)
z = outer(x , y , FUN="f")
par(mfrow=c(1,2))
persp(x,y,z, theta = -30, phi = 10,col='yellow',expand=0.7,ticktype='detailed')
image(x,y,z,col = heat.colors(100))
contour(x,y,z,add=T)


f.to.minimize=function(theta){
  x = theta[1]
  y = theta[2]
  return(f(x,y))
}

# Minimizing f.to.minimize with different initial values for the optimizer
nlminb(c(2,3) , f.to.minimize)
nlminb(c(2,-2) , f.to.minimize)
nlminb(c(-2,-2) , f.to.minimize) 
nlminb(c(-2,1) , f.to.minimize)
nlminb(c(0,0) , f.to.minimize)

# Note the objective function value at the optimized parameters. 
# Convergence=0 means that the numerical optimization has successfully converged.



