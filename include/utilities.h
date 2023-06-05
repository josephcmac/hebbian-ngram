#ifndef UTILITIES_H
#define UTILITIES_H

#pragma once
#include <iostream>
#include <fstream>
#include <vector>

class Utilities
{
public:
    double findMedian(const std::vector<double>& list);
    double syncategorematic_median(const unsigned int &t, const std::vector<std::vector<double>> &syn);
    size_t mergeSubarraysAndCountInversions(std::vector<std::pair<double, double>>& arr, size_t start, size_t middle, size_t end);
    size_t countInversionsWithMergeSort(std::vector<std::pair<double, double>> &arr, size_t start, size_t end);
    double kendall_tau(const std::vector<double> &x, const std::vector<double> &y);
    double fire(const unsigned int &i, const unsigned int &j, const unsigned int &t,
                const std::vector<std::vector<double>> &cat, const double &mSq);
    double wire(const unsigned int &i, const unsigned int &j, const double &t,
                       const std::vector<std::vector<double>> &cat,
                       const std::vector<std::vector<double>> &syn,
                       const unsigned int &window);
    void output(const std::vector<double> &t, const std::vector<double> &correlation);

private:
    const char *outputFileName = "../data/output/output.csv";
};


#endif // UTILITIES_H
