#!/bin/bash
# declare STRING variable
echo "Compilando Codigo..."
g++ -std=c++0x Ej3.cpp -o testing/backtrack1
g++ -std=c++0x Ej3_podas_invertidas.cpp -o testing/backtrack_invertido
#g++ -std=c++0x Ej3_random.cpp -o testing/backtrack_random
g++ -std=c++0x fuerzaBruta.cpp -o testing/fuerzaBruta
echo "OK!"

back1="backtrack"
back2="backtrack_invertido"
back3="backtrack_random"
back4="fuerzaBruta"

NOMBRE="testing/tiempoConN"
EXT=".txt"
for VARIABLE in {1..15}
do
	
	python generador.py $VARIABLE
	echo "generada entrada para n:"$VARIABLE
	echo "Corriendo Backtrack..."
	./testing/backtrack1 < testing/testej3.txt > $NOMBRE$VARIABLE$back1$EXT
	echo "Corriendo Backtrack Invertido..."
	./testing/backtrack_invertido < testing/testej3.txt > $NOMBRE$VARIABLE$back2$EXT
	echo "Corriendo Backtrack random..."
	#./testing/backtrack_random < testing/testej3.txt > $NOMBRE$VARIABLE$back3$EXT
	echo "Corriendo Fuerza Bruta..."
	./testing/fuerzaBruta < testing/testej3.txt > $NOMBRE$VARIABLE$back4$EXT
	echo "OK!"
done