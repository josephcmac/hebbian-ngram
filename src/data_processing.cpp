#include "../include/data_processing.h"



std::vector<std::vector<double>> readDataFrame(const std::vector<std::string>& filenames) {
    std::vector<std::vector<double>> dataframe;

    // Read the first file to populate the first column
    if (!filenames.empty()) {
        std::ifstream firstFile(filenames[0]);
        if (!firstFile.is_open()) {
            std::cerr << "Error opening file: " << filenames[0] << std::endl;
            return dataframe;
        }

        std::vector<double> firstColumn;
        std::string line;

        // Skip the header line
        std::getline(firstFile, line);

        while (std::getline(firstFile, line)) {
            std::stringstream ss(line);
            std::string value1, value2;

            if (std::getline(ss, value1, ',') && std::getline(ss, value2, ',')) {
                try {
                    double year = std::stod(value1);
                    firstColumn.push_back(year);
                } catch (const std::exception& e) {
                    std::cerr << "Invalid file format: " << filenames[0] << std::endl;
                    return dataframe;
                }
            }
        }

        firstFile.close();
        dataframe.push_back(firstColumn);
    }

    // Read the second columns from the remaining files
    for (size_t i = 0; i < filenames.size(); ++i) {
        std::ifstream file(filenames[i]);
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << filenames[i] << std::endl;
            continue;
        }

        std::string line;
        std::vector<double> column;

        // Skip the header line
        std::getline(file, line);

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string value1, value2;

            if (std::getline(ss, value1, ',') && std::getline(ss, value2, ',')) {
                try {
                    double count = std::stod(value2);
                    column.push_back(count);
                } catch (const std::exception& e) {
                    std::cerr << "Invalid file format: " << filenames[i] << std::endl;
                    return dataframe;
                }
            }
        }

        file.close();
        dataframe.push_back(column);
    }

    return dataframe;
}
