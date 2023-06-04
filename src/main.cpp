#include <iostream>
#include "../include/data_processing.h"
#include "../include/rapidjson/document.h" //from https://rapidjson.org/

#define PARAMETERS "../data/input/parameters.json"

int main()
{

    std::vector<std::vector<double>> cat = readData("categorematic-B.csv");
    std::vector<std::vector<double>> syn = readData("syncategorematic.csv");


    std::ifstream file(PARAMETERS);
    if (!file.is_open()) {
        std::cout << "Failed to open file." << std::endl;
        return 1;
    }

    // Read the file content into a string
    std::string jsonData((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    // Parse the JSON string
    rapidjson::Document document;
    document.Parse(jsonData.c_str());

    // Check if parsing succeeded
    if (document.HasParseError()) {
        std::cout << "Failed to parse JSON." << std::endl;
        return 1;
    }

    // Extract the values from the JSON document
    int yearStart = document["year_start"].GetInt();
    int yearEnd = document["year_end"].GetInt();
    int window = document["window"].GetInt();
    int sampleSize = document["sample_size"].GetInt();


    return 0;
}
