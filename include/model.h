#ifndef MODEL_H
#define MODEL_H

#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <random>

// https://rapidjson.org/
#include "../include/rapidjson/document.h"
#include "../include/rapidjson/istreamwrapper.h"

#include "../include/data_processing.h"
#include "../include/utilities.h"

class Model {
public:
    void run();

private:
    std::vector<std::vector<double>> cat;
    std::vector<std::vector<double>> syn;
    DataProcessor processor;
    Utilities tool;
    void processJsonDocument();
    void readCsvDocuments();
    void generateSamples();

    std::vector<double> corr_list = {};
    std::vector<double> time_list = {};

    unsigned int yearStart;
    unsigned int yearEnd;
    unsigned int window;
    unsigned int sampleSizeWords;
    unsigned int sampleSizeTime;

    const char* parameters = "../data/input/parameters.json";
    const char* categorematicFile;
    const char* syncategorematicFile;
    const unsigned int fail_max = 20;

};


#endif  // MODEL_H
