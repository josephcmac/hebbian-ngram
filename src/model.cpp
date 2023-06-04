#include "../include/model.h"
#include <cmath>
#define MINYEAR 1500

void Model::processJsonDocument(const char *filename)
{
    // Read the JSON document
    rapidjson::Document document = processor.readJson(filename);

    // Extract the values from the JSON document
    yearStart = document["year_start"].GetInt() - MINYEAR;
    yearEnd = document["year_end"].GetInt() - MINYEAR;
    window = document["window"].GetInt();
    sampleSizeWords = document["sample_size_words"].GetInt();
    sampleSizeTime = document["sample_size_time"].GetInt();
}

void Model::readCsvDocuments(const char *cat_name, const char *syn_name)
{
    // Read the CSV documents
    cat = processor.readData(cat_name);
    syn = processor.readData(syn_name);
}

void Model::generateSamples()
{
    // Vectors for fire and wire
    std::vector<double> fire_list = {}, wire_list = {};
    corr_list = {};
    time_list = {};

    // Create a random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    // Create a distribution for the categorematic expressions
    std::uniform_int_distribution<int> dist_cat(0, cat.size() - 1);

    // Create a distribution for the year
    std::uniform_int_distribution<int> dist_year(yearStart, yearEnd);

    // Count the number of valid samples (problematic samples are ignored)
    unsigned int samples_time = 0, samples_words, i, j;

    // random year
    unsigned int t, fail;
    double mSq, f, w;

    // std::cout << "Year: " << 1500 + t << std::endl;
    while (samples_time < sampleSizeTime)
    {
        t = dist_year(gen);
        samples_words = 0;
        mSq = std::pow(tool.syncategorematic_median(t, syn), 2); // median squared
        if (mSq != 0)
        {
            fail = 0;
            while ((samples_words < sampleSizeWords) & (fail < fail_max))
            {
                i = dist_cat(gen); // first categorematic expression
                do
                {
                    j = dist_cat(gen); // second categorematic expression
                } while (i == j);

                f = tool.fire(i, j, t, cat, mSq);
                w = tool.wire(i, j, t, cat, syn, window);
                if (w == -2)
                {
                    fail++;
                }
                else
                {
                    fire_list.push_back(f);
                    wire_list.push_back(w);
                    samples_words++;
                }
            }
            if (samples_words == sampleSizeWords)
            {
                corr_list.push_back(tool.kendall_tau(fire_list, wire_list));
                time_list.push_back(t);
                samples_time++;
            }
        }
    }
}

void Model::run()
{
    processJsonDocument(parameters);
    readCsvDocuments(categorematicFile, syncategorematicFile);
    generateSamples();
    tool.output(time_list, corr_list);
}
