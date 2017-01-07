#!/usr/bin/env bash

if [ $1 = "C" ]  
then  
    /usr/bin/clang -ggdb  -include *.h *.c -Wall -o program && /usr/bin/valgrind --leak-check=full --show-leak-kinds=all  ./program /home/jazzzy/GitProjects/TravellerProblem/firstBest/bin/arguments/distancias_10.txt   /home/jazzzy/GitProjects/TravellerProblem/firstBest/bin/arguments/aleatorios_ls_2016.txt
elif [ $1 = "Cpp" ]  
then  
    /usr/bin/clang++ -std=c++11 -stdlib=libc++ main.cpp FileParser.cpp RandomGanerator.cpp Solution.cpp ProblemManager.cpp -include ProblemManager.hpp -Wall -Werror -o program && /usr/bin/valgrind --leak-check=full --show-leak-kinds=all  ./program /home/jazzzy/GitProjects/TravellerProblem/firstBest/bin/arguments/distancias_10.txt   /home/jazzzy/GitProjects/TravellerProblem/firstBest/bin/arguments/aleatorios_ls_2016.txt
fi

rm program