#! /usr/bin/env python
import sys
from random import randint

fo = open("testingPeorCaso/testej3.txt", "wb")
cota_peligrosidad = 10
cantidad_de_productos = int(sys.argv[1])
for w in range(1, 40):
	fo.write(str(cantidad_de_productos) + " " + str(cota_peligrosidad) + "\n")
	for i in range(1, cantidad_de_productos):
		for j in range(1, cantidad_de_productos ):
			peligrosidad = str(randint(0, 1))
	    	fo.write(peligrosidad + " ")
	    	fo.write("")    
	fo.write("\n")
fo.write("0")
fo.close()
