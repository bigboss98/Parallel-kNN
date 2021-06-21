/*
 * Sequential version of KNN model
 */
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector> 
#include <cmath>
#include <fstream>
#include <functional>
#include "utimer.cpp"
#include "utility.h"
using std::string;
using std::tuple;
using std::vector;

int main(int argc, char** argv){
    /*
     * Compute the K Nearest Neighbors of all point in a sequential way
     */
    string input_path = argv[1];
    string output_path = argv[2];
    int num_neighbors = atoi(argv[3]);
    vector<tuple<int, double, double>> points {};

    read_points(input_path, points);
    if (points.size() < num_neighbors)
        num_neighbors = points.size() - 1;
    int num_points = points.size(); 
    vector<vector<int>> computed_neighbors (points.size());
    {
        utimer tpar("Sequential version");
        for(int index=0; index < num_points; ++index){
            computed_neighbors[index] = compute_knn(points[index], points, num_neighbors);
        }
    }
    write_points(output_path, computed_neighbors);
    
     
    std::cout << "Written Top " << num_neighbors << " for each " << points.size() 
              << " points in "   << output_path << std::endl;
}

