#!/usr/bin/env bash


cd ../bin
./TravellerProblem_Simulated_Annealing ./arguments/distancias_sa_100_2016.txt ./arguments/aleatorios_sa_2016_caso1.txt > ./traza_caso1.txt
cat ./traza_caso1.txt
echo "---------FIN DE LA SALIDA DEL PROGRAMA 1---------"

./TravellerProblem_Simulated_Annealing ./arguments/distancias_sa_100_2016.txt ./arguments/aleatorios_sa_2016_caso2.txt > ./traza_caso2.txt
cat ./traza_caso2.txt
echo "---------FIN DE LA SALIDA DEL PROGRAMA 1---------"

./TravellerProblem_Simulated_Annealing ./arguments/distancias_sa_100_2016.txt ./arguments/aleatorios_sa_2016_caso3.txt > ./traza_caso3.txt
cat ./traza_caso3.txt
echo "---------FIN DE LA SALIDA DEL PROGRAMA 1---------"






echo "Ejecutando diff entre la traza generada y la del campus virtual para el caso 1: "
diff traza_caso1.txt ./arguments/traza_sa_2016_caso1.txt

echo "Ejecutando diff entre la traza generada y la del campus virtual para el caso 2: "
diff traza_caso2.txt ./arguments/traza_sa_2016_caso2.txt

echo "Ejecutando diff entre la traza generada y la del campus virtual para el caso 3: "
diff traza_caso3.txt ./arguments/traza_sa_2016_caso3.txt

