#include <iostream>
#include "../include/data_processing.h"

int main()
{

std::vector<std::vector<double>> cat = readData("categorematic-B.csv");
std::vector<std::vector<double>> syn = readData("syncategorematic.csv");

return 0;
}
