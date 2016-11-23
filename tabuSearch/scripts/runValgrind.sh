#!/usr/bin/env bash

cd ../bin
/usr/bin/valgrind --leak-check=full --show-leak-kinds=all ./TravellerProblem_TabuSearch ./arguments/distancias_100_2016.txt ./arguments/aleatorios_ts_2016.txt
