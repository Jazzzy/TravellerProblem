#!/usr/bin/env bash

cd ../bin
./TravellerProblem_Evolutive_Computing ./arguments/distancias_ce_10_2016.txt ./arguments/aleatorios_ce_10_2016.txt > ./ultimaTraza.txt
cat ./ultimaTraza.txt
echo "---------FIN DE LA SALIDA DEL PROGRAMA---------"
echo "Ejecutando diff entre la traza generada y la del campus virtual: "
diff ultimaTraza.txt ./arguments/traza_ce_10_2016.txt
