accAll <- read.csv("walking_running_niklas_20hz.csv", sep=";", dec=",")
str(accAll)

# 1. Remove earth gravity ----
accAll$acc <- accAll$acc - 1 # - 9.81m/s^2

acc <- accAll$acc

# 2. Smooth raw data ----
accAll$sAcc <- acc;
for(i in 3:(length(acc)-3))
{
  accAll$sAcc[i] <- sum(acc[(i-2):(i+2)])
}

acc <- accAll$sAcc

# 3. Calculate Min + Max over Window to get threshold ----
accAll$max <- -100
accAll$min <- 100

freq<-20
v <- seq(1,length(acc)-freq,freq)

for(i in v)
{
  rng <- i : (i+freq)
  maxV <- max(acc[rng])
  minV <- min(acc[rng])
  accAll$max[rng] <- maxV*1
  accAll$min[rng] <- minV*1
}

# 4. Actual Step detection ----

sample_old <- 0
sample_new <- -100
precision <- 0.05

accAll$isStep <- NA

for(i in 1:length(acc)){
  sample_result <- acc[i]
  thr <- (accAll$max[i] + accAll$min)/2
  if(abs(sample_result - sample_new)>precision){
    sample_old <- sample_new
    sample_new <- sample_result
  
    if(sample_old != -100 && sample_new < sample_old && sample_new< thr && sample_old > thr){
      accAll$isStep[i] <- thr
    }
  }
  
}

accAll$isStep

# 5. Calculate Step frequency ----
stepFreq = array()
f=0
stepCount=0
for(i in 1:length(accAll$isStep)){
  isStep <- accAll$isStep[i]
  if(is.na(isStep)==FALSE){
    stepFreq[length(stepFreq)+1] <- f
    f<-0
  }
  else{
    f<-f+accAll$Time[i+1]-accAll$Time[i]
  }
}

stepFreq

# 6. Filter Step frequency ----

stepFreqF <- stepFreq;
for(i in 3:(length(stepFreq)-3))
{
  stepFreqF[i] <- median(stepFreq[(i-3):(i+3)])
}

stepFreqF

# Plots ----

plot(stepFreqF, type="o")

plot(accAll$sAcc, type="o", pch='.') 
#lines(accAll$sAcc, pch=".", col="orange")
lines(accAll$max, pch=".", col="red")
lines(accAll$min, pch=".", col="green")
lines(accAll$isStep, type="p", col="blue")
