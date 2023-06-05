#ifndef MODEL_H
#define MODEL_H

#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include "../include/rapidjson/document.h" // https://rapidjson.org/
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
    void processJsonDocument(const char* filename);
    void readCsvDocuments(const char* cat_name, const char* syn_name);
    void generateSamples();

    std::vector<double> corr_list = {};
    std::vector<double> time_list = {};

    unsigned int yearStart;
    unsigned int yearEnd;
    unsigned int window;
    unsigned int sampleSizeWords;
    unsigned int sampleSizeTime;

    const char* parameters = "../data/input/parameters.json";
    const char* categorematicFile = "categorematic-B.csv";
    const char* syncategorematicFile = "syncategorematic.csv";
    const unsigned int fail_max = 20;

};


#endif  // MODEL_H
