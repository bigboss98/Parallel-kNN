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
std::vector<int> compute_knn(std::tuple<int, double, double> point,
                         const std::vector<std::tuple<int, double, double>>& points, 
                         const int num_neighbors);
#endif
