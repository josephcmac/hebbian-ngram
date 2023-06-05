#ifndef DATA_PROCESSING_H
#define DATA_PROCESSING_H


#define COMMON_PATH_INPUT "../data/input/"
#define COMMON_PATH_AUXILIARY "../data/auxiliary/"

#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "../include/rapidjson/document.h"

class DataProcessor {
public:
    std::vector<std::vector<double>> readData(const std::string& filename);
    rapidjson::Document readJson(const std::string &filePath);

private:
    std::vector<std::string> readListOfStringsFromFile(const std::string& filename);
    std::vector<std::string> fileNames(const std::string& filename);
    std::vector<std::vector<double>> readDataFrame(const std::vector<std::string>& filenames);
};


#endif // DATA_PROCESSING_H
