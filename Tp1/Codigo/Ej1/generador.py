#! /usr/bin/env python
from random import randint

fo = open("testej1.txt", "wb")
n = 100
c = 10
cantidad_de_tablones = 1000
for x in range(1, cantidad_de_tablones):
    fo.write(str(x) + " " + str(randint(1, x)) + " ")
    for i in range(0, x):
        tablon = randint(0, 1)
        fo.write(str(tablon) + " ")
        fo.write("")
    fo.write("\n")

fo.write("\n")
fo.write("0")
fo.close()
