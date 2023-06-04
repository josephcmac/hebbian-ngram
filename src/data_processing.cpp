std::vector<std::string> readListOfStringsFromFile(const std::string &filename)
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

std::vector<std::string> fileNames(const std::string &filename)
{
    std::vector<std::string> names = readListOfStringsFromFile(std::string(commonPathInput) + filename);

    std::vector<std::string> filenames;

    for (const auto &name : names)
    {
        filenames.emplace_back(std::string(commonPathAuxiliary) + name + ".csv");
    }

    return filenames;
}

std::vector<std::vector<double>> readDataFrame(const std::vector<std::string> &filenames)
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

std::vector<std::vector<double>> readData(const std::string& filename) {
    return readDataFrame(fileNames(filename));
}
