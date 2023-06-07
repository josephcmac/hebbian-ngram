# the purpose of this script is to generate a random dataset to compare the
# difference between noise and signal

# Directory of the project
DIR <- "/home/caballero/Desktop/"

n <- 100 # number of files

library(tidyverse)

x <- lapply(1:n, function(i){
  paste0("categorematic-", i)
}) %>% unlist

x %>% 
  write.table(file=paste0(DIR, "hebbian-ngram/data/input/", 
                          "categorematic-random.csv"),
              row.names=FALSE,
              col.names=FALSE,
              sep="\t", 
              quote = FALSE)


y <- lapply(1:n, function(i){
  paste0("syncategorematic-", i)
}) %>% unlist

y %>% 
  write.table(file=paste0(DIR, "hebbian-ngram/data/input/", 
                          "syncategorematic-random.csv"),
              row.names=FALSE,
              col.names=FALSE,
              sep="\t", 
              quote = FALSE)

z <- c(x, y)
rm(x,y)

lapply(z, function(filename) {
  df <-data.frame(Year = 1500:2019, Count = sample(1000:1000000, 520))
  df %>% 
    write.csv(file = paste0(DIR, "hebbian-ngram/data/auxiliary/", filename, 
                            ".csv"),
              row.names=FALSE)
})
