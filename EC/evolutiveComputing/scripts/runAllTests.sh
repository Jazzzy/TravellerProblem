#!/usr/bin/env bash

cd ../bin
./TravellerProblem_Evolutive_Computing ./arguments/distancias_ce_10_2016.txt ./arguments/aleatorios_ce_10_2016.txt > ./ultimaTraza.txt
cat ./ultimaTraza.txt
echo "---------FIN DE LA SALIDA DEL PROGRAMA---------"

./TravellerProblem_Evolutive_Computing ./arguments/distancias_ce_10_2016.txt ./arguments/aleatorios_ce_10_2016_caso2.txt > ./ultimaTraza_caso2.txt
cat ./ultimaTraza_caso2.txt
echo "---------FIN DE LA SALIDA DEL PROGRAMA---------"




echo "Ejecutando diff entre la traza generada y la del campus virtual para el caso 1: "
diff ultimaTraza.txt ./arguments/traza_ce_10_2016.txt > ultimoDiff.txt
head -n100 ultimoDiff.txt

echo "Ejecutando diff entre la traza generada y la del campus virtual para el caso 2: "
diff ultimaTraza_caso2.txt ./arguments/traza_ce_10_2016_caso2.txt > ultimoDiff_caso2.txt
head -n100 ultimoDiff_caso2.txt
