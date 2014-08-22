#! /usr/bin/env python

from random import randint

fo = open("testej2.txt", "wb")
for j in range(1):
        #obtengo un random para la cantidad de joyas
        n  = randint(1,10)
        #primer linea la cantidad de joyas n
        fo.write( str(n) + "\n")
        #para cada joya genero un di ti random y lo escribo
        for i in range(n):
                izq = randint(1,20)
                alt = randint(1,50)
                der = izq
                while der <= izq:
                	der=randint(1,20)
                fo.write( str(izq) + " " + str(alt) + " " + str(der) + "\n")
#ultima linea es un 0 y cierro el archivo
fo.write("0")
fo.close()