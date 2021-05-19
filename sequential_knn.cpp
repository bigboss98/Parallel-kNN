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
#include "utility.h"
using std::string;
using std::tuple;
using std::vector;

int main(int argc, char** argv){
    string input_path = argv[1];
    string output_path = argv[2];
    int num_neighbors = atoi(argv[3]);
    vector<tuple<int, double, double>> points {};

    read_points(input_path, points);
    if (points.size() < num_neighbors)
        num_neighbors = points.size();

    vector<tuple<int, vector<int>>> computed_neighbors {};
    compute_knn(points, computed_neighbors, num_neighbors, 0, points.size());
    
    write_points(output_path, computed_neighbors);

    std::cout << "Written " << num_neighbors << " for each point in " 
              << output_path << std::endl;
    std::cout << num_neighbors << std::endl;
    std::cout << input_path << std::endl;
    std::cout << output_path << std::endl;
    std::cout << points.size() << std::endl;
}

