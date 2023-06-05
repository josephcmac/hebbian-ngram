#ifndef UTILITIES_H
#define UTILITIES_H

#pragma once
#include <iostream>
#include <fstream>
#include <vector>

class Utilities
{
public:
    void output(const std::vector<double> &t, const std::vector<double> &correlation);
    double kendall_tau(const std::vector<double> &x, const std::vector<double> &y);
    double syncategorematic_median(const unsigned int &t, const std::vector<std::vector<double>> &syn);
    double fire(const unsigned int &i, const unsigned int &j, const unsigned int &t,
                const std::vector<std::vector<double>> &cat, const double &mSq);
    double wire(const unsigned int &i, const unsigned int &j, const double &t,
                       const std::vector<std::vector<double>> &cat,
                       const std::vector<std::vector<double>> &syn,
                       const unsigned int &window);
    double findMedian(const std::vector<double>& list);


private:
    const char *outputFileName = "../data/output/output.csv";
    size_t mergeAndCount(std::vector<std::pair<double, double>>& arr, size_t low, size_t mid, size_t high);
    size_t countInversions(std::vector<std::pair<double, double>>& arr, size_t low, size_t high);
};


#endif // UTILITIES_H
