# Packages
required_packages <- c("tidyverse", "future.apply")
new_packages <- required_packages[!(required_packages %in% 
                                      installed.packages()[,"Package"])]
if(length(new_packages)) install.packages(new_packages)
lapply(required_packages, require, character.only = TRUE)

# To install this package, follow the instructions from the following GitHub 
# repository: https://github.com/seancarmody/ngramr
library("ngramr")

# For parallel processing
plan(multisession)

# Function to extract N-gram data
extract_ngram_data <- function(words, year_start, year_end, corpus, file_path) {
  future_lapply(words, function(word) {
    file_name <- paste(word, "csv", sep = ".") %>% 
      paste(file_path, ., sep = "/")
    if (file.exists(file_name)) {
      message(paste("Skipping", word, "- file already exists."))
      return(NULL)
    }
    tryCatch({
      # Extract N-gram data using the ngramr package
      ngram(word, year_start = year_start, year_end = year_end, 
            corpus = corpus,
            case_ins = TRUE, count = TRUE, smoothing = 0) %>%
        select(Year, Count) %>%
        aggregate(Count ~ Year, data = ., sum) %>%
        write.csv(file_name, row.names=FALSE)
      
    }, error = function(e) {
      message(paste("Error extracting N-gram data for", word, ":", e))
    })
  })
}

# Call the function to extract N-gram data for specific words
extract_ngram_data(words = c("France", "bon", "Angleterre", "d'accord"), 
                   year_start = 1500, 
                   year_end = 2019, 
                   corpus = "fr-2019",
                   # file_path is the path where the files will be saved
                   file_path = "/home/caballero/Desktop/hebbian-ngram/data/auxiliary")
