#include "../include/rapidjson/document.h"
#include "../include/data_processing.h"

std::vector<std::string> DataProcessor::readListOfStringsFromFile(const std::string &filename)
{
    std::vector<std::string> strings;
    std::ifstream file(filename);
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            strings.push_back(line);
        }
        file.close();
    }
    else
    {
        std::cerr << "Error opening file: " << filename << std::endl;
    }
    return strings;
}

std::vector<std::string> DataProcessor::fileNames(const std::string &filename)
{
    std::vector<std::string> names = readListOfStringsFromFile(std::string(COMMON_PATH_INPUT) + filename);

    std::vector<std::string> filenames;

    for (const auto &name : names)
    {
        filenames.emplace_back(std::string(COMMON_PATH_AUXILIARY) + name + ".csv");
    }

    return filenames;
}

std::vector<std::vector<double>> DataProcessor::readDataFrame(const std::vector<std::string> &filenames)
{
    std::vector<std::vector<double>> dataframe;

    // Read the second columns from the files
    for (size_t i = 0; i < filenames.size(); ++i)
    {
        std::ifstream file(filenames[i]);
        if (!file.is_open())
        {
            std::cerr << "Error opening file: " << filenames[i] << std::endl;
            continue;
        }

        std::string line;
        std::vector<double> column;

        // Skip the header line
        std::getline(file, line);

        while (std::getline(file, line))
        {
            std::stringstream ss(line);
            std::string value1, value2;

            if (std::getline(ss, value1, ',') && std::getline(ss, value2, ','))
            {
                try
                {
                    double count = std::stod(value2);
                    column.push_back(count);
                }
                catch (const std::exception &e)
                {
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

std::vector<std::vector<double>> DataProcessor::readData(const std::string& filename) {
    return readDataFrame(fileNames(filename));
}

rapidjson::Document DataProcessor::readJson(const std::string &filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        std::cout << "Failed to open file." << std::endl;
        // You might want to handle this error case differently
        throw std::runtime_error("Failed to open file: " + filePath);
    }

    // Read the file content into a string
    std::string jsonData((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    // Parse the JSON string
    rapidjson::Document document;
    document.Parse(jsonData.c_str());

    // Check if parsing succeeded
    if (document.HasParseError())
    {
        std::cout << "Failed to parse JSON." << std::endl;
        // You might want to handle this error case differently
        throw std::runtime_error("Failed to parse JSON: " + filePath);
    }

    return document;
}
