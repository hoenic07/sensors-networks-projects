library(caret)

accAll <- read.csv("walking_running_niklas_20hz.csv", sep=";", dec=",")
str(accAll)

accAll$acc <- accAll$acc - 1 # - 9.81m/s^2

acc <- accAll$acc
accAll$max <- -100
accAll$min <- 100
isStep = 0

freq<-20

v <- seq(1,length(acc)-freq,freq)

accAll$sAcc <- acc;
for(i in 6:(length(acc)-6))
{
  accAll$sAcc[i] <- sum(acc[(i-2):(i+2)])
}

plot(accAll$sAcc, type="o", pch='.') 

acc <- accAll$sAcc

for(i in v)
{
  rng <- i : (i+freq)
  maxV <- max(acc[rng])
  minV <- min(acc[rng])
  accAll$max[rng] <- maxV*1
  accAll$min[rng] <- minV*1
}

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

warnings()

accAll$isStep

accAll$sAcc

plot(accAll$sAcc, type="o", pch='.') 
#lines(accAll$sAcc, pch=".", col="orange")
lines(accAll$max, pch=".", col="red")
lines(accAll$min, pch=".", col="green")
lines(accAll$isStep, type="p", col="blue")


stepFreq = list()
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

accAll$Time

stepFreq <- unlist(stepFreq)

plot(stepFreq, type="o")

stepFreqF <- stepFreq;
for(i in 3:(length(stepFreq)-3))
{
  stepFreqF[i] <- median(stepFreq[(i-3):(i+3)])
}

stepFreqF

plot(stepFreqF, type="o")
