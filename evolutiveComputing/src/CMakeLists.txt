cmake_minimum_required(VERSION 3.6)
project(TravellerProblem_Evolutive_Computing)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp FileParser.cpp RandomGanerator.cpp Solution.cpp ProblemManager.cpp ProblemManager.hpp SolutionHelper.cpp SolutionHelper.h PairList.cpp PairList.hpp)
add_executable(TravellerProblem_Evolutive_Computing ${SOURCE_FILES})