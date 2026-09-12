[4] (3 puntos) Expliquen su algoritmo de procesamento de los datos de los sensores.
Deben ser capaces de explicarlo de forma clara, precisa, y sucinta, **sin usar IA**.
La explicación del algoritmo debe incluirse en el archivo "Report.md" o "Report.txt".
El profesor, a discreción suya, puede interrogarlos sobre el proyecto ***Macondian***.

Le pedi a la IA que hiciera el codigo para la siguiente manera de procesar los datos:

Basandome en: 

"Mr. X:
Así es, no se obtiene un flujo de datos separado para cada sensor.
Se obtiene un único flujo de lotes: cada uno con las lecturas de todos los sensores.
En nuestro sistema, es fundamental obtener lecturas simultáneas de todos los sensores."

Cada etiqueta es un sensor aparte cada uno debe procesarse aparte 

Basandome en: 

"Resulta ser que el sensor Macondiano es un dispositivo compuesto: contiene un arreglo de sensores [3].
A esos los llamamos microsensores. Los Macondos son el promedio de las lecturas de los microsensores."

"Mr. X:
Correcto. Y debo agregar que el sensor Macondiano no calcula el promedio: ¡eso lo computan Ustedes!"

Entonces esos arreglos de cada sensor individual o macro sensor son los datos de los microsensores y como indica Mr X hay que sacar el promedio o los macondos para empezar a procesar

Basandome en: 
"Mr. X:
En principio si, pero déjeme explicar un poco más.
La medida de los Macondos es, lógicamente, un estimado de los microsensores.
El modelo estadístico es un modelo de suavización que depende de varias cosas.
Principalmente de una medida de valor representativo (promedio, mediana, u otra), y ...
... la eliminación de valores atípicos (outliers), debidos a fallas de los microsensores.
El radio Macondiano de tolerancia es un margen de tolerancia para eliminar valores atípicos."

Tengo que crear un algoritmo de suavizacion par ala medida de los macondos final 
El algoritmo:
1. Sacar un promedio individual para cada Macrosensor para cada Lote.
2. Conseguir el promedio y la desviacion estandar en base al promedio individual Obtenido para cada lote
3. Mi criterio es el siguiente para eliminar outliers: Si con el promedio individual supera o es inferior a el promedio iniidual +/- dos veces la desviacion estandar entonces se elimina ese promedio individual del conjunto de datos
4. Se hace un promedio Global con los promedios individuales restantes 
5. Se presenta al final
Todo esto se hace en tiempo real
Se usa la deviacion estandar para suavizar el promedio porque entendiendoq ue las desviacion estandar es un calculo para medir la dispersion de los datos si hay algun lote que dio unos datos muy alejados(en este caso se considera muy alejado promedioglobal+- 2 veces la desviacion estandar) entonces se elimina y de esta manera se obtienen unos datos mas unidos.







