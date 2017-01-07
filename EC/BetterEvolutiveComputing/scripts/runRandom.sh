#!/usr/bin/env bash

cd ../bin
./TravellerProblem_Evolutive_Computing ./arguments/distancias_ce_100_2016.txt > ./ultimaTraza.txt
echo "---------FIN DE LA EJECUCIÓN---------"
echo ""
tail ./ultimaTraza.txt
