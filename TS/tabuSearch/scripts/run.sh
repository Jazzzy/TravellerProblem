#!/usr/bin/env bash

cd ../bin
./TravellerProblem_TabuSearch ./arguments/distancias_100_2016.txt ./arguments/aleatorios_ts_2016.txt > ./ultimaTraza.txt
cat ./ultimaTraza.txt
echo "---------FIN DE LA SALIDA DEL PROGRAMA---------"
echo "Ejecutando diff entre la traza generada y la del campus virtual: "
diff ultimaTraza.txt ./arguments/traza_ts_2016.txt/traza_ts_2016.txt 
