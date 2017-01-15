#-----------------------------------------------------------------------
# Calibration of Genetic Algorithm
# Metodi e Modelli per l'Ottimizzazione Combinatoria - 2015
# Marco Zanella <marco.zanella.9@studenti.unipd.it>
#-----------------------------------------------------------------------

# This analysis requires the following packages to be installed
library(tree)


#-----------------------------------------------------------------------
# Preprocesses data
# Computes minimum cost and relative performance for each instance
data <- read.table("results.dat", header=T)
data$MinCost <- data$Cost
for (i in c(50, 60, 70, 80)) {
    for (j in 1:5) {
        data$MinCost[data$Size == i & data$ID == j] <- min(data$Cost[data$Size == i & data$ID == j])
    }
}
data$Performance = data$MinCost / data$Cost


#-----------------------------------------------------------------------
# Computes linear model and CART
formula <- Performance ~ Size + Crossover + Mutation + Threshold + Accept + Improvement + PopSize

linear <- lm(formula, data=data)
cart <- tree(formula, data=data)


#-----------------------------------------------------------------------
# Prints results to files and standard output
pdf("performance.pdf")
boxplot(data$Performance)
invisible(dev.off())

pdf("cart.pdf", width=10, height=7)
plot(cart); text(cart)
invisible(dev.off())

print(summary(linear))
