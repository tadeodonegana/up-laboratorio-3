# TP Procesos

1) Realizar un programa que obtenga números aleatorios diferentes (no repetitivos):

- Indicar el motivo por el cual el programa desarrollado es (o no) el óptimo.

* No es optimo ya que cuantos mas numeros unicos se generen, mas tiempo se tardara en encontrar uno nuevo que no este repetido. Esto hace que se recorra el array mas veces, disminuyendo la eficiencia del programa.


- Investigar y nombrar distintas maneras de realizar el mismo.

* Una primera opcion mas eficiente es usar el algoritmo de Fisher-Yates, su concepto es generar todos los numeros aleatorios en orden y luego mezclarlos. En este approach se recorre el array una unica vez para mezclar, y al haber generado los numeros previamente nos aseguramos de su unicidad.

* Una segunda opcion puede ser mantener un array con todos los numeros disponibles para generar, en cada iteracion elegir una posicion aleatoria, tomar ese numero y eliminarlo, asegurandonos la unicidad de los resultados.


- Ejecutarlo varias veces e identificar, desde consola, si se ejecuta con el mismo PID o no (ver comando PS).

* Si lo ejecutamos varias veces desde distintas terminales el programa presenta distintos PID.

- Hacer que reciba el DESDE y HASTA desde parametros.

* Implementado.

- A partir del código realizado en el punto 1, confeccionar una función genérica que obtenga
valores no repetitivos que sirva para futuros ejercicios (por ejemplo, puede devolver un vector
con dichos valores).

---

Para ejecutar:

- Ejecutar el comando make para construir el ejecutable
make

- Ejecutar el programa, con parametros si asi se lo desea
./programa [10 20] -> parametros opcionales.

