#!/usr/bin/env bash

cd ../bin
./TravellerProblem_BetterTabuSearch ./arguments/distancias_100_2016.txt ./arguments/aleatorios_ts_2016.txt > ./ultimaTraza.txt
cat ./ultimaTraza.txt

