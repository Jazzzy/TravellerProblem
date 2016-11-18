cmake_minimum_required(VERSION 3.6)
project(TravellerProblem_FirstBest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp DistanceFileParser.cpp RandomGanerator.cpp Solution.cpp ProblemManager.cpp ProblemManager.hpp)
add_executable(TravellerProblem_FirstBest ${SOURCE_FILES})