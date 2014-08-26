#! /usr/bin/env python

from random import randint

fo = open("random.in", "wb")
for j in range(100):
        #obtengo un random para la cantidad de joyas
        n = randint(4, 40)
        #primer linea la cantidad de joyas n
        fo.write(str(n) + "\n")
        #para cada joya genero un di ti random y lo escribo
        for i in range(n):
                izq = randint(1, 40)
                alt = randint(1, 40)
                der = izq
                while der <= izq:
                        der = randint(1, 60)
                fo.write(str(izq) + " " + str(alt) + " " + str(der) + "\n")
#ultima linea es un 0 y cierro el archivo
fo.write("0")
fo.close()


fo = open("variacionAlturas.in", "wb")
for j in range(100):
        #obtengo un random para la cantidad de joyas
        n = randint(4, 60)
        #primer linea la cantidad de joyas n
        fo.write(str(n) + "\n")
        #para cada joya genero un di ti random y lo escribo
        for i in range(n):
                izq = randint(1, 10)
                alt = randint(1, 10000)
                der = izq
                while der <= izq:
                        der = randint(1, 30)
                fo.write(str(izq) + " " + str(alt) + " " + str(der) + "\n")
#ultima linea es un 0 y cierro el archivo
fo.write("0")
fo.close()


fo = open("variacionDistancias.in", "wb")
for j in range(100):
        #obtengo un random para la cantidad de joyas
        n = randint(4, 60)
        #primer linea la cantidad de joyas n
        fo.write(str(n) + "\n")
        #para cada joya genero un di ti random y lo escribo
        for i in range(n):
                izq = randint(1, 1000)
                alt = randint(1, 40)
                der = izq
                while der <= izq:
                        der = randint(1, 3000)
                fo.write(str(izq) + " " + str(alt) + " " + str(der) + "\n")
#ultima linea es un 0 y cierro el archivo
fo.write("0")
fo.close()

