#!/usr/bin/env bash

cd ../bin
./TravellerProblem_Simulated_Annealing ./arguments/distancias_sa_100_2016.txt ./arguments/aleatorios_sa_2016_caso1.txt > ./ultimaTraza.txt
cat ./ultimaTraza.txt
echo "---------FIN DE LA SALIDA DEL PROGRAMA---------"
echo "Ejecutando diff entre la traza generada y la del campus virtual: "
diff ultimaTraza.txt ./arguments/traza_sa_2016_caso1.txt
