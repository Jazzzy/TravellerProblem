cmake_minimum_required(VERSION 3.6)
project(TravellerProblem_TabuSearch)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp FileParser.cpp RandomGanerator.cpp Solution.cpp ProblemManager.cpp ProblemManager.hpp TabuList.cpp TabuList.hpp)
add_executable(TravellerProblem_TabuSearch ${SOURCE_FILES})