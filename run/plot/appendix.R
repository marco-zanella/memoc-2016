#-----------------------------------------------------------------------
# Computes statistics about CPLEX
data <- read.table("cplex.dat", header=F)
Size = unique(data$V1)

df <- data.frame(Size)
for (i in Size) {
    df$Cost[df$Size == i] <- mean(data$V3[data$V1 == i])
    df$WallclockTime[df$Size == i] <- mean(data$V4[data$V1 == i])
}

write.table(df, file="cplex_mean.dat", row.names=F)



#-----------------------------------------------------------------------
# Computes statistics about Genetic Algorithm
data <- read.table("ga.dat", header=F)
cplex_data <- read.table("cplex.dat", header=F)

Size = unique(data$V1)
data <- data[!(data$V4 == -1), ]

df <- data.frame(Size)
for (i in Size) {
    Instances <- unique(data$V2[data$V1 == i])

    costs        <- c()
    performances <- c()
    variances    <- c()
    times        <- c()
    maxP         <- c()
    minP         <- c()
    for (j in Instances) {
        exact_cost <- cplex_data$V3[cplex_data$V1 == i & cplex_data$V2 == j]
        c          <- data$V4[data$V1 == i & data$V2 == j]
        costs[j]   <- mean(c)

        p               <- exact_cost / c
        maxP[j]         <- max(p)
        minP[j]         <- min(p)
        performances[j] <- mean(p)
        variances[j]    <- var(p)
        times[j]        <- mean(data$V5[data$V1 == i & data$V2 == j])
    }

    df$Cost[df$Size == i]           <- mean(costs)
    df$Performance[df$Size == i]    <- mean(performances)
    df$MinPerformance[df$Size == i] <- min(minP)
    df$MaxPerformance[df$Size == i] <- max(maxP)
    df$Variance[df$Size == i]       <- mean(variances)
    df$WallclockTime[df$Size == i]  <- mean(times)

}
df$StandardDeviation <- sqrt(df$Variance)

write.table(df, file="ga_mean.dat", row.names=F)
