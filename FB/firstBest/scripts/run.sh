#!/usr/bin/env bash

cd ../bin
./TravellerProblem_FirstBest ./arguments/distancias_10.txt ./arguments/aleatorios_ls_2016.txt > ./ultimaTraza.txt
cat ./ultimaTraza.txt
echo "---------FIN DE LA SALIDA DEL PROGRAMA---------"
echo "Ejecutando diff entre la traza generada y la del campus virtual: "
diff ultimaTraza.txt ./arguments/traza_ls_2016.txt