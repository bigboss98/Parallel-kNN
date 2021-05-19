/*
 * Utility function for k Nearest Neighbors implementation
 * Used by sequantial and parallel version 
 */
#include <algorithm>
#include "utility.h"
#include <cmath>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <tuple> 
#include <mutex>
using std::vector;
using std::tuple;
using std::string;

double euclidean_distance(tuple<int, double, double> point, tuple<int, double, double> other){
    return sqrt((std::get<1>(point) - std::get<1>(other)) + 
                (std::get<2>(point) - std::get<2>(other)));
}

void read_points(string input_path, vector<tuple<int, double, double>>& points){
    std::ifstream input_points;
    tuple<int, double, double> point {}; 


    input_points.open(input_path);
    if(!input_points)
        std::cout << "File not found" << std::endl;
    else{
        string line;
        int point_id = 1;

        while(getline(input_points, line)){
            std::stringstream tokenized_line(line);
            string first_num, second_num;
            getline(tokenized_line, first_num, ',');
            getline(tokenized_line, second_num);
            point = std::make_tuple(point_id, std::stod(first_num), std::stod(second_num));
            points.push_back(point);
            point_id++;
        }
    }
    input_points.close();
}

void write_points(string output_path, const vector<tuple<int, vector<int>>> nearest_neighbors){
    std::ofstream output_file;

    output_file.open(output_path);
    if(!output_file)
        std::cout << "File not opened" << std::endl;
    else{
        output_file << "Point ID\tNearest Neighbors Points ID" << std::endl;
        for (auto elem : nearest_neighbors){
            output_file << std::get<0>(elem) << "\t\t\t";
            for (auto neighbor : std::get<1>(elem)){
                output_file << neighbor << ", ";
            } 
            output_file << std::endl;
        }       
    }
    output_file.close();
}

void compute_knn(const vector<tuple<int, double, double>>& points, 
                 vector<tuple<int, vector<int>>>& computed_neighbors,
                 const int num_neighbors, int start, int end){
    auto first = points.cbegin() + start;
    auto second = points.cbegin() + end;
    vector<tuple<int, double, double>> computed_point(first, second);
    std::mutex mutex_obj;

    for (auto const& point : computed_point){
        vector<tuple<int, double>> point_distances {}; 
        for(auto other : points){
            if(std::get<0>(other) != std::get<0>(point)){
                point_distances.push_back({std::get<0>(other), 
                                           euclidean_distance(point, other)});
            }
        }
        vector<int> nearest_neighbors = {};

        std::sort(point_distances.begin(), point_distances.end(),
                    [](tuple<int, double> first, tuple<int, double> second){
                        return std::get<1>(first) <= std::get<1>(second);
                    });
        for(int index=0; index < num_neighbors;++index){
            nearest_neighbors.push_back(std::get<0>(point_distances[index]));
        }
        
        computed_neighbors.push_back({std::get<0>(point), 
                                      nearest_neighbors});    
        
    }
    
}
