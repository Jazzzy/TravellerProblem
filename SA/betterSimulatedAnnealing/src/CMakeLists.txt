cmake_minimum_required(VERSION 3.6)
project(TravellerProblem_Simulated_Annealing_Better)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp FileParser.cpp RandomGanerator.cpp Solution.cpp ProblemManager.cpp ProblemManager.hpp SolutionHelper.cpp SolutionHelper.h DistanceMatrixWrapper.cpp DistanceMatrixWrapper.h PairList.cpp PairList.hpp ListOfNeighbours.cpp ListOfNeighbours.hpp)
add_executable(TravellerProblem_Simulated_Annealing_Better ${SOURCE_FILES})