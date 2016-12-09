# Mejoras Aplicadas sobre la implementación original

Sobre la implementación realizada para la versión original de la práctica hemos hecho una serie de modificaciones que hacen que se obtengan mejores resultados y se aprovechen más las iteraciones que realizará el programa.

Consideramos un factor importante la mejora por iteración por que no solo buscamos que se encuentre un resultado bueno para este caso concreto, sino que para otros casos también sea capaz de encontrar soluciones y si requerimos mejores soluciones que las que obtenemos con 10000 iteraciones las podamos obtener simplemente con aumentar el número de iteraciones. Para nosotros, el hecho de que el algoritmo mejore significativamente con las iteraciones es un indicativo de su utilidad y flexibilidad. Las mejoras aplicadas han sido:

- **Implementación de una matriz de frecuencias** para obtener costes contrapesados con la frecuencia con la que viajamos entre un par de ciudades dado. De esta forma podemos diversificar con más facilidad ya que uno de los problemas de la implementación original era la falta de diversificación. Usaremos los costes contrapesados en las inicializaciones de las soluciones para realizar soluciones nuevas sobre las que visitaremos vecindarios nuevos.
- **Inicialización Greedy (Voraz) de soluciones**: Cuando obtenemos una solución inicial nueva simplemente construimos la solución de forma voraz, buscando la ciudad más cercana a la última introducida. Para buscar la ciudad más cercana obtenemos el peso contrapesado aprovechándonos de la estrategia anterior para así no realizar una y otra vez la misma solución inicial pues esto no tendría sentido, cada vez que se diversificará en un reinicio estaríamos repitiendo una y otra vez el mismo recorrido en el espacio de búsqueda.
- **Variación entre intensificación y diversificación**: Siempre que llegamos a la situación en la que tenemos que realizar un reinicio decidiremos si vamos a intensificar o diversificar en el espacio de soluciones teniendo en cuenta la desviación estándar de la matriz de frecuencias entre pares. Para ello estableceremos un límite tal que si lo superamos es que la matriz tiene una desviación grande (se está explorando un espacio de soluciones concreto muchas veces) y por lo tanto deberemos diversificar para explorar otras soluciones y si por otra parte la desviación es menor que el límite es que estamos explorando de forma bastante homogénea y debemos intensificar sobre una solución actualmente considerada buena para intentar mejorarla. Esta intensificación la realizaremos escogiendo la mejor solución hasta el momento.
- **Modificación de parámetros existentes**: Hemos realizado alguna modificación sobre los tamaños de la lista tabú y hemos experimentado con el número de iteraciones necesarias para el reseteo pues ambos parámetros parecían pequeños para el tamaño del problema. Los valores finales se pueden ver al final de este documento.

##Otra información relacionada

- **Optimización de la obtención del coste**: Esto no es una mejora sobre el algoritmo en sí mismo pero si afecta a la lógica y comportamiento del programa (sobre todo a su eficiencia). La mencionaremos en este documento ya que fuimos los que se lo sugerimos originalmente al profesor de la asignatura (Pablo Tomico Pérez y yo) y al parecer se ha ido comentando por las diferentes clases de prácticas y lo ha implementado mucha gente. La mejora consiste en no recalcular el coste de una solución cuando está siendo generada como vecino de otra ya que tenemos prácticamente toda la información necesaria heredada de la solución "padre". Lo que hacemos es restar el coste relacionado con las ciudades que se van a intercambiar (el coste hacia y desde ellas) y después sumar el coste relacionado una vez realizado el intercambio de forma que solo calculamos 4 costes nuevos y no repasamos la matriz de costes iterando sobre todas las ciudades.

Los parámetros y fórmulas usados para la versión del programa entregada son los siguientes:

- Iteraciones sin mejora antes del reseteo: 100
- Límite de desviación estándar para intensificar/diversificar: 500
- Tamaño de la lista tabú: 500
- Constante MU usada en la fórmula de coste contrapesado con la frecuencia: 0.005
- Fórmula usada para calcular el peso con las frecuencias:

```c++
double coste_contrapesado = coste_real + (MU * diff_max_distancias * ((frec / frec_max)));
```