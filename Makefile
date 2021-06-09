CXX = g++ -std=c++17
CXXFLAGS = -Wall  
LDFLAGS = -pthread 
FF_ROOT		= fastflow

INCLUDES	= -I $(FF_ROOT) 
OPTFLAGS	= -O3 -finline-functions


utimer.o: utimer.cpp 
	$(CXX) $(CXXFLAGS) $(OPTFLAGS) -c $< 
utility.o: utility.cpp utility.h 
	$(CXX) $(CXXFLAGS) $(OPTFLAGS) -c $<

sequential_knn.o: sequential_knn.cpp 
	$(CXX) $(CXXFLAGS) $(OPTFLAGS) -c $< 

sequential: sequential_knn.o utility.o utimer.o 
	$(CXX) $(OPTFLAGS) $^ -o $@ 

parallel.o: parallel.cpp 
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OPTFLAGS) -c $< 

parallel: parallel.o utility.o utimer.o
	$(CXX) $(LDFLAGS) $(OPTFLAGS) $^ -o $@

generate_points: generate_points.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

parallel_fastflow.o: parallel_fastflow.cpp
	$(CXX) $(LDFLAGS) $(OPTFLAGS) $(INCLUDES) -c $<

parallel_fastflow: parallel_fastflow.o utility.o utimer.o
	$(CXX) $(LDFLAGS) $(INCLUDES) $(OPTFLAGS) $^ -o $@

.PHONY: clean 

clean: 
	-rm parallel.o parallel sequential sequential_knn.o utility.o utimer.o generate_points parallel_fastflow.o parallel_fastflow 
