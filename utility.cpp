/*
 * Utility function for k Nearest Neighbors implementation
 * Used by sequential and parallel versions 
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
    /*
     * Compute the Euclidean Distance between two points
     */
    return sqrt(pow((std::get<1>(point) - std::get<1>(other)), 2) + 
                pow((std::get<2>(point) - std::get<2>(other)), 2));
}

void read_points(string input_path, vector<tuple<int, double, double>>& points){
    /*
     * Read Points from an input file where the point ID is the line of the file and 
     * x and y value are provided in every line of file separed by a comma.
     */
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
    /*
     * Write k Nearest neighbors of all 2D points with the following format
     * point_ID  ID of all k Nearest Neighbors
     */
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

vector<int> compute_knn(tuple<int, double, double> point,
                         const vector<tuple<int, double, double>>& points, 
                         const int num_neighbors){
    /*
     * Compute the k Nearest Neighbors of a 2D Point
     */

    vector<tuple<int, double>> point_distances {}; 
    int point_id = std::get<0>(point);

    for(auto other : points){
        int other_point_id = std::get<0>(other);
        if(other_point_id != point_id){
            point_distances.push_back({other_point_id, 
                                       euclidean_distance(point, other)});
        }
    }
    vector<int> nearest_neighbors = {};

    // Sort distance from a point to choose the k nearest point 
    std::sort(point_distances.begin(), point_distances.end(),
                [](tuple<int, double> first, tuple<int, double> second){
                        return std::get<1>(first) <= std::get<1>(second);
                    });
    for(int index=0; index < num_neighbors;++index){
            nearest_neighbors.push_back(std::get<0>(point_distances[index]));
    }
    return nearest_neighbors;    
    
}
