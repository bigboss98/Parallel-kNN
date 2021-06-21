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
#include <queue>
#include <tuple> 
#include <mutex>
using std::vector;
using std::tuple;
using std::string;
using std::priority_queue; 

double euclidean_distance(tuple<int, double, double> point, tuple<int, double, double> other){
    /*
     * Compute the Euclidean Distance between two points
     * For efficiency sqrt operation has been eliminated but it doesn't change order of points
     * since already the function is monotonic 
     */
     double x_difference = std::get<1>(point) - std::get<1>(other);
     double y_difference = std::get<2>(point) - std::get<2>(other);
     return x_difference * x_difference + y_difference * y_difference;
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

void write_points(string output_path, const vector<vector<int>> nearest_neighbors){
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
        int num_points = nearest_neighbors.size();
        for (int index = 0;index < num_points;index++){
            output_file << index + 1<< "\t\t\t";
            for (auto neighbor : nearest_neighbors[index]){
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
    priority_queue<tuple<double, int>> top_k_distances;
    int point_id = std::get<0>(point);
 
    for(auto other : points){
        int other_point_id = std::get<0>(other);
        if(other_point_id != point_id){
            double distance = euclidean_distance(point, other);
            if(top_k_distances.size() < num_neighbors)
                top_k_distances.push(std::make_tuple(distance, other_point_id));
            else if(distance < std::get<0>(top_k_distances.top())){
                top_k_distances.pop();
                top_k_distances.push(std::make_tuple(distance, other_point_id));
            }
        }

    }
    vector<int> nearest_neighbors(num_neighbors);

    for(int index=0; index < num_neighbors;++index){
        tuple<double, int> top_elem = top_k_distances.top();
        nearest_neighbors[num_neighbors - index - 1] = std::get<1>(top_elem);
        top_k_distances.pop();
    }

    return nearest_neighbors;    
    
}
