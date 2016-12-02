#!/usr/bin/env bash


cd ../src
g++ -static -g main.cpp FileParser.cpp RandomGanerator.cpp Solution.cpp ProblemManager.cpp ProblemManager.hpp TabuList.cpp TabuList.hpp SolutionHelper.cpp SolutionHelper.h -o ../bin/TravellerProblem_BetterTabuSearch
cd ../bin
/usr/bin/valgrind --leak-check=full --show-leak-kinds=all ./TravellerProblem_BetterTabuSearch ./arguments/distancias_100_2016.txt ./arguments/aleatorios_ts_2016.txt
echo "IMPORTANT NOTE: The error of conditional move or jump depends on non initialized values could be avoidable initializing all values with something that will never be used slowing down the program."
