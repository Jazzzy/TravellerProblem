cmake_minimum_required(VERSION 3.6)
project(TravellerProblem_FirstBest)

find_program(MEMORYCHECK_COMMAND valgrind)
set(MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes --leak-check=full")
set(MEMORYCHECK_SUPPRESSIONS_FILE "${PROJECT_SOURCE_DIR}/valgrind_suppress.txt")


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp FileParser.cpp RandomGanerator.cpp Solution.cpp ProblemManager.cpp ProblemManager.hpp)
add_executable(TravellerProblem_FirstBest ${SOURCE_FILES})