#include <iostream>
#include <vector>
#include <ff/ff.hpp>
#include <ff/map.hpp>
#include <ff/parallel_for.hpp>
#include "utility.h"
#include "utimer.cpp"
using ff::ParallelFor;
using std::string;
using std::tuple;
using std::vector;

int main(int argc, char** argv){
    /*
     * Compute k Nearest neighbors of all points in parallel using Fastflow library
     * It uses Parallel for pattern to implement Map pattern 
     */
    if(argc <= 4)
        std::cout << "Not Provided enough arguments" << std::endl;
    string input_path = argv[1];
    string output_path = argv[2];
    int num_neighbors = atoi(argv[3]);
    int num_workers = atoi(argv[4]);

    vector<tuple<int, double, double>> points {};
    read_points(input_path, points);

    if (points.size() < num_neighbors)
        num_neighbors = points.size() - 1;
    
    vector<tuple<int, vector<int>>> computed_neighbors(points.size());
    
    ParallelFor pf(num_workers);
    {
        utimer tpar("Fastflow Parallel version");
        
        ff::parallel_for(0, points.size(), 1, 1000, [&](const long index){
        computed_neighbors[index] = std::make_tuple(std::get<0>(points[index]),
                                                    compute_knn(points[index], points, num_neighbors));
            }, num_workers);
    }
        write_points(output_path, computed_neighbors);


    
    
    std::cout << "Written Top " << num_neighbors << " for each " << points.size() 
              << " points in "   << output_path << std::endl;

}