#!/usr/bin/env bash

cd ../bin
/usr/bin/valgrind --leak-check=full --show-leak-kinds=all ./TravellerProblem_FirstBest ./arguments/distancias_10.txt ./arguments/aleatorios_ls_2016.txt

