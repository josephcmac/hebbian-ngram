#include <iostream>
#include "data_processing.cpp"


int main()
{

std::string commonPath = "/home/caballero/Desktop/hebbian-ngram/data/auxiliary/";
    
    std::vector<std::string> names = {
        "France.csv",
        "Angleterre.csv",
        "bon.csv"
    };

    std::vector<std::string> filenames;

    for (const auto& name : names) {
        filenames.emplace_back(commonPath + name);
    }

    std::vector<std::vector<double>> dataframe = readDataFrame(filenames);

// Print the dataframe for testing
    for (size_t i = 0; i < dataframe.size(); ++i) {
        std::cout << "Column " << i + 1 << ": ";
        for (const auto& value : dataframe[i]) {
            std::cout << value << ' ';
        }
        std::cout << std::endl;
    }

    return 0;
}
