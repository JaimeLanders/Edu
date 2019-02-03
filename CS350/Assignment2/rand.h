#include <iostream> // Debug statments
#include <random>

int rand(int min, int max) // Source: https://stackoverflow.com/questions/19665818/generate-random-numbers-using-c11-random-library
{
//    std::cout << "\nrand " << std::endl;
//    std::cout << "min = " << min << std::endl;
//    std::cout << "max = " << max << std::endl;

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(min, max);

//    for (int i=0; i<16; ++i)
//        std::cout << dist(mt) << "\n";

    return dist(mt);
}
