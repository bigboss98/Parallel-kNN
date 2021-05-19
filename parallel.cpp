/*
 * Parallel version of  k Nearest Neighbors using only c++ Threads 
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
    if(argc <= 4)
        std::cout << "Not Provided enough arguments" << std::endl;
    string input_path = argv[1];
    string output_path = argv[2];
    int num_neighbors = atoi(argv[3]);
    int num_workers = atoi(argv[4]);

    vector<tuple<int, double, double>> points {};
    vector<pair<int, int>> ranges(num_workers);
    vector<thread> tids;
    vector<vector<tuple<int, vector<int>>>> list_computed_neighbors(num_workers);

    read_points(input_path, points);

    if (points.size() < num_neighbors)
        num_neighbors = points.size() - 1;
    
    int points_for_worker = ceil(points.size() / num_workers);
    std::cout << "Points for worker: " << points_for_worker << std::endl;

    for(int index=0; index < num_workers; ++index){
        ranges[index] = std::make_pair(index * points_for_worker,
                                       index != (num_workers - 1) ? 
                                            (index+1) * points_for_worker :
                                            points.size());
        std::cout << "Start: " << std::get<0>(ranges[index]) 
                  << " End: "  << std::get<1>(ranges[index]) << std::endl;
    }
    
    {
        utimer tpar("parallel");
        for(int index=0; index < num_workers; ++index){
            tids.push_back(thread(compute_knn, std::ref(points), std::ref(list_computed_neighbors[index]), 
                                  num_neighbors, std::get<0>(ranges[index]),  std::get<1>(ranges[index])));
        }

        for(auto& t : tids)
            t.join();
    

        vector<tuple<int, vector<int>>> computed_neighbors {list_computed_neighbors[0]};


        for(int index=1; index < num_workers; ++index){
            computed_neighbors.insert(computed_neighbors.end(), 
                                      list_computed_neighbors[index].begin(),
                                      list_computed_neighbors[index].end());

        }

        write_points(output_path, computed_neighbors);
    }

    
    
    std::cout << "Written " << num_neighbors << " for each point in " 
              << output_path << std::endl;
    std::cout << num_neighbors << std::endl;
    std::cout << input_path << std::endl;
    std::cout << output_path << std::endl;
    std::cout << points.size() << std::endl;
}
