# Parallel-kNN
A Parallel implementation of K Nearest Neighbors models for Parallel Computing course at University of Pisa.
To parallelize the computation of K Nearest Neighbors for all points I use Map pattern and I have implemented two parallel version:
-an implementation using only C++ standard thread 
-an implementation using Fastflow library 

# Usage
To build and use this project I have defined a Makefile with the following commands:
- make generate_points: build generate_points program that will generate n 2D points randomly with a min and max value
- make sequential: build sequential program that compute k nearest neighbors for all 2D points  
- make parallel: build parallel C++ standard thread version 
- make parallel_fastflow: build parallel Fastflow version 

For generate_points program there are 4 arguments: name of file to save generated point, number of point to generate, min and max value 
For Sequential program there are only 3 arguments: Input file path, Output file path and number of Nearest neighbors
For Parallel and Parallel_Fastflow is added to arguments of Sequential the number of worker to use  

# Example 
./generate_points input_points.txt 100 -5 +6 
It creates 100 points with x and y values between -5 and +6 saved on input_points.txt file 

./sequential input_points.txt output_points.txt 10
It computes the 10 Nearest neighbors of points in input_points and save results on output_points.txt

./parallel input_points.txt output_points.txt 10 4
Parallel version of 10 Nearest Neighbors using 4 Threads 

./parallel_fastflow input_points.txt output_points.txt 10 4
Parallel Fastflow version of 10 Nearest Neighbors using 4 Threads
