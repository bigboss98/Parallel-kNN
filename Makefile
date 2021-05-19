CXX = g++
CXXFLAGS = -Wall -O3 
LDFLAGS = -pthread 

utimer.o: utimer.cpp 
	$(CXX) $(CXXFLAGS) -c $< 
utility.o: utility.cpp utility.h 
	$(CXX) $(CXXFLAGS) -c $<

sequential_knn.o: sequential_knn.cpp 
	$(CXX) $(CXXFLAGS) -c $< 

sequential: sequential_knn.o utility.o
	$(CXX) $(LDFLAGS) $^ -o $@ 

parallel.o: parallel.cpp 
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -c $< 

parallel: parallel.o utility.o utimer.o
	$(CXX) $(LDFLAGS) $^ -o $@

generate_points: generate_points.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

.PHONY: clean 

clean: 
	-rm parallel.o parallel sequential sequential_knn.o utility.o utimer.o generate_points 
