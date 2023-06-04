#include "../include/model.h"

int main()
{
    try
    {
        Model model;
        model.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
