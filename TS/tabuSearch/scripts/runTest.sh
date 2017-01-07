#!/usr/bin/env bash

cd ../bin
./TravellerProblem_TabuSearch ./arguments/cuestionario/distancias_100_2016.txt ./arguments/cuestionario/aleatorios_ts_2016.txt > ./ultimaTrazaCUESTIONARIO.txt
cat ./ultimaTrazaCUESTIONARIO.txt
