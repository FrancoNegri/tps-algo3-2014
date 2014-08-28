#! /usr/bin/env python
import sys
from random import randint

fo = open("testing/testej3.txt", "wb")
cota_peligrosidad = int(sys.argv[1])
cantidad_de_productos = 8
for w in range(1, 40):
	fo.write(str(cantidad_de_productos) + " " + str(cota_peligrosidad) + "\n")
	for i in range(1, cantidad_de_productos):
	    for j in range(i, cantidad_de_productos):
	        peligrosidad = randint(0, cota_peligrosidad)
	        fo.write(str(peligrosidad) + " ")
		fo.write("\n")
fo.write("0")
fo.close()
