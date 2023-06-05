#include "../include/utilities.h"
#include <algorithm>
#include <vector>
#include <stdexcept>

// Helper function to merge sub-arrays and count inversions
size_t Utilities::mergeSubarraysAndCountInversions(std::vector<std::pair<double, double>> &arr, size_t start, size_t middle, size_t end)
{
    size_t inversionCount = 0;
    size_t i = start, j = middle, k = 0;
    std::vector<std::pair<double, double>> tempArr(end - start);

    // Merge two sorted sub-arrays and count inversions
    while (i < middle && j < end)
    {
        if (arr[i].second <= arr[j].second)
        {
            tempArr[k++] = arr[i++];
        }
        else
        {
            tempArr[k++] = arr[j++];
            inversionCount += middle - i;
        }
    }

    // Copy remaining elements from the first sub-array (if any)
    while (i < middle)
    {
        tempArr[k++] = arr[i++];
    }

    // Copy remaining elements from the second sub-array (if any)
    while (j < end)
    {
        tempArr[k++] = arr[j++];
    }

    // Copy the merged elements back into the original array
    std::copy(tempArr.begin(), tempArr.end(), arr.begin() + start);

    return inversionCount;
}

// Function to count inversions in the array using merge sort
size_t Utilities::countInversionsWithMergeSort(std::vector<std::pair<double, double>> &arr, size_t start, size_t end)
{
    if (end - start <= 1)
        return 0;

    size_t middle = start + (end - start) / 2;

    // Recursively count inversions in left and right halves
    size_t inversionCount = countInversionsWithMergeSort(arr, start, middle) +
                            countInversionsWithMergeSort(arr, middle, end);

    // Count inversions that span the two halves
    inversionCount += mergeSubarraysAndCountInversions(arr, start, middle, end);

    return inversionCount;
}

double Utilities::kendall_tau(const std::vector<double> &x, const std::vector<double> &y)
{
    if (x.size() != y.size())
    {
        throw std::invalid_argument("Lists must have the same length.");
    }

    size_t n = x.size();
    std::vector<std::pair<double, double>> arr(n);

    for (size_t i = 0; i < n; i++)
    {
        arr[i] = std::make_pair(x[i], y[i]);
    }

    // Sort by x values
    std::sort(arr.begin(), arr.end());

    // Count inversions in y
    size_t inversions = countInversionsWithMergeSort(arr, 0, n);

    // Calculate Kendall's Tau
    double tau = 1.0 - 2.0 * inversions / (n * (n - 1) / 2.0);

    return tau;
}

void Utilities::output(const std::vector<double> &t, const std::vector<double> &correlation)
{
    const std::string delimiter = ",";
    const size_t size = t.size();

    std::ofstream outputFile(outputFileName);
    if (!outputFile)
    {
        std::cerr << "Failed to open output file." << std::endl;
        return;
    }

    outputFile << "time" << delimiter << "correlation" << std::endl;

    for (unsigned int i = 0; i < size; ++i)
    {
        outputFile << 1500 + t[i] << delimiter << correlation[i] << std::endl;
    }

    outputFile.close();

    std::cout << "Output written to " << outputFileName << std::endl;
}

double Utilities::findMedian(const std::vector<double> &list)
{
    if (list.empty())
    {
        return 0.0;
    }

    // Create a copy of the list
    std::vector<double> sortedList = list;

    // Sort the list in ascending order
    std::sort(sortedList.begin(), sortedList.end());

    // Find the median based on the size of the list
    if (sortedList.size() % 2 == 0)
    {
        // If the size is even, average the two middle elements
        size_t mid = sortedList.size() / 2;
        return (sortedList[mid - 1] + sortedList[mid]) / 2.0;
    }
    else
    {
        // If the size is odd, return the middle element
        return sortedList[sortedList.size() / 2];
    }
}

double Utilities::syncategorematic_median(const unsigned int &t, const std::vector<std::vector<double>> &syn)
{
    std::vector<double> list = {};
    for (unsigned int k = 0; k < syn.size(); k++)
    {
        list.push_back(syn[k][t]);
    }
    return findMedian(list);
}

double Utilities::fire(const unsigned int &i, const unsigned int &j, const unsigned int &t,
                       const std::vector<std::vector<double>> &cat, const double &mSq)
{
    return cat[i][t] * cat[j][t] / mSq; // m is the squared median of syn[k, t] for all k
}

double Utilities::wire(const unsigned int &i, const unsigned int &j, const double &t,
                       const std::vector<std::vector<double>> &cat,
                       const std::vector<std::vector<double>> &syn,
                       const unsigned int &window)
{
    std::vector<double> tau = {};

    for (unsigned int k = 0; k < syn.size(); k++)
    {
        std::vector<double> x = {};
        std::vector<double> y = {};

        for (unsigned int tt = t; tt <= t + window; tt++)
        {
            if (syn[k][tt] == 0)
            {
                break;
            }
            else
            {
                x.push_back(cat[i][tt] / syn[k][tt]);
                y.push_back(cat[j][tt] / syn[k][tt]);
            }
        }
        if (x.size() == window)
        {
            tau.push_back(kendall_tau(x, y));
        }
    }
    if (tau.size() == 0)
    {
        return (-2);
    }
    else
    {
        return findMedian(tau);
    }
}
