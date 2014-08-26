#!/bin/bash
# declare STRING variable

for VARIABLE in {10..13}
do
	NOMBRE="testing/salida"
	EXT=".txt"
	python generador.py $VARIABLE
	NOMBRE=$NOMBRE$VARIABLE$EXT
	./a.out < testing/testej3.txt > $NOMBRE
done