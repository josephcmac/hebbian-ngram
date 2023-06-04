#ifndef DATA_PROCESSING_H
#define DATA_PROCESSING_H


#define commonPathInput "../data/input/"
#define commonPathAuxiliary "../data/auxiliary/"


#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "../src/data_processing.cpp"

class DataProcessor {
public:
    std::vector<std::vector<double>> readData(const std::string& filename);

private:
    std::vector<std::string> readListOfStringsFromFile(const std::string& filename);
    std::vector<std::string> fileNames(const std::string& filename);
    std::vector<std::vector<double>> readDataFrame(const std::vector<std::string>& filenames);
};

#endif // DATA_PROCESSING_H
