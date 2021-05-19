/*
 * Header for utility functions used in k Nearest Neighbors 
 */
#ifndef UTILITY_H
#define UTILITY_H
#include <iostream>
#include <vector>
#include <string> 

void read_points(std::string input_path, std::vector<std::tuple<int, double, double>>& points);
void write_points(std::string output_path, const std::vector<std::tuple<int, std::vector<int>>> nearest_neighbors);
double euclidean_distance(std::tuple<int, double, double> point, std::tuple<int, double, double> other);
void compute_knn(const std::vector<std::tuple<int, double, double>>& points, 
                 std::vector<std::tuple<int, std::vector<int>>>& computed_neighbors,
                 const int num_neighbors, int start, int end);
#endif
