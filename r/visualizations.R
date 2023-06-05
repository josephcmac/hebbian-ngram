# Directory of the project
DIR <- "/home/caballero/Desktop/"

library(tidyverse)
df <- read.csv( paste0(DIR, "hebbian-ngram/data/output/output.csv") )

png("simulation-3.png")
df %>%
  ggplot(aes(x=time, y=correlation))+
  geom_point()+
  geom_hline(yintercept = c(-1, 1), linetype='dashed', col = 'gray', lwd = 2)+
  theme_linedraw()
dev.off()

