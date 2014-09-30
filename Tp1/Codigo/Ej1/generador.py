#! /usr/bin/env python
from random import randint

fo = open("random.in", "wb")
n = 100
c = 10
cantidad_de_tablones = 100
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

fo = open("sanos.in", "wb")
n = 100
c = 1
cantidad_de_tablones = 100
for x in range(1, cantidad_de_tablones):
    fo.write(str(x) + " " + str(randint(1, x)) + " ")
    for i in range(0, x):
        tablon = 0
        fo.write(str(tablon) + " ")
        fo.write("")
    fo.write("\n")

fo.write("\n")
fo.write("0")
fo.close()