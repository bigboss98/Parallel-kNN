/**
 * \file parallel.cpp
 * \brief Parallel version of  k Nearest Neighbors using only c++ Threads 
 */
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <thread>
#include <string>
#include <functional>
#include "utimer.cpp"
#include "utility.h"
using std::string;
using std::vector;
using std::tuple;
using std::thread;
using std::pair;

int main(int argc, char** argv){
    /**
     * Main function where there is Parallel computation of K Nearest Neighbors, using 
     * only standard C++ thread 
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
    
    
    vector<thread> tids;
    vector<vector<int>> computed_neighbors(points.size());

    int points_for_worker = ceil(points.size() / num_workers);
    
    {
        utimer tpar("parallel");

        auto compute_knn_neighbors = [&](int start, int end){
            for(int index=start; index < end; ++index){
                computed_neighbors[index] = compute_knn(points[index], points, num_neighbors);
            }
        };

        vector<pair<int, int>> ranges(num_workers);
        for(int index=0; index < num_workers; ++index){
            ranges[index] = std::make_pair(index * points_for_worker,
                                           index != (num_workers - 1) ? 
                                            (index+1) * points_for_worker :
                                            points.size());

        }
    
        for(int index=0; index < num_workers; ++index){
            tids.push_back(thread(compute_knn_neighbors, std::get<0>(ranges[index]),  std::get<1>(ranges[index])));
        }

        for(auto& t : tids)
            t.join();
    }
    write_points(output_path, computed_neighbors);
    

    std::cout << "Written Top " << num_neighbors << " for each " << points.size() 
              << " points in "   << output_path << std::endl;
}
