#include "../include/model.h"
#include <cmath>
#define MINYEAR 1500


void Model::processJsonDocument()
{
    // Read the JSON document
    std::ifstream file(parameters);
    rapidjson::IStreamWrapper stream(file);
    rapidjson::Document document;
    document.ParseStream(stream);


    // Check if parsing succeeded
    if (document.HasParseError()) {
        // Handle parse error
    }


    // Extract the values from the JSON document
    yearStart = document["year_start"].GetInt() - MINYEAR;
    yearEnd = document["year_end"].GetInt() - MINYEAR;
    window = document["window"].GetInt();
    sampleSizeWords = document["sample_size_words"].GetInt();
    sampleSizeTime = document["sample_size_time"].GetInt();
    categorematicFile = document["categorematic_file"].GetString();
    syncategorematicFile = document["syncategorematic_file"].GetString();
}

void Model::readCsvDocuments()
{
    // Read the CSV documents
    const std::string& cat_filename = categorematicFile;
    const std::string& syn_filename = syncategorematicFile;

    cat = processor.readData(cat_filename);
    syn = processor.readData(syn_filename);

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
                if (w == -2.0)
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
    processJsonDocument();
    readCsvDocuments();
    generateSamples();
    tool.output(time_list, corr_list);
}
