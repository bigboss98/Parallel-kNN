/*
 * Generate 2D Points to use for KNN and saved on an input file 
 */
#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include <string>
using std::string;

int main(int argc, char** argv){
    if(argc <= 4)
        std::cout << "Not Provided enough arguments" << std::endl;
    string output_path = argv[1];
    int num_points = atoi(argv[2]);
    double min_value = std::stod(argv[3]);
    double max_value = std::stod(argv[4]);

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);

    std::uniform_real_distribution<double> distribution (min_value, max_value);

    std::ofstream write_file;

    write_file.open(output_path);
    if(!write_file){
        std::cout << "File not opened" << std::endl;
        return -1;
    }
    for (int index=0; index < num_points; ++index){
        write_file << distribution(generator) << ", " << distribution(generator) << std::endl;
    }
    write_file.close();
    std::cout << "Written " << num_points << " points on " << output_path << std::endl;

    return 0;
}