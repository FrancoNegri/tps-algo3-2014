#!/usr/bin/python

from random import shuffle
from random import randint

nombre = "completos.in"
fo = open(nombre, "wb")
for z in range(1):
	n = randint(0,5)
	k = 10
	m = (n * (n-1) )/2 
	fo.write(str(n) + " " + str(m) + " " + str(k) + '\n')
	for i in range(n):
		for j in range(n):	
			if i<j:
				fo.write(str(i+1) + " " + str(j+1) + " " + str(randint(1,50)) + '\n')
fo.write('0' + '\n')
fo.close()


nombre = "sinAristas.in"
fo = open(nombre, "wb")
for z in range(100):
	n = randint(0,23)
	k = 10
	m = (n * n-1 )/2 
	fo.write(str(n) + " " + str(m) + " " + str(k) + '\n')
fo.write('0' + '\n')
fo.close()


nombre = "cambiandoK.in"
fo = open(nombre, "wb")
n = 15
for z in range(100):
	k = range(0,15)
	m = (n * n-1 )/2 
	fo.write(str(n) + " " + str(m) + " " + str(k))
	for i in range(n):
		for j in range(n):	
			if i<j:
				fo.write(str(i) + " " + str(j) + " " + str(randint(1,100)) + '\n')
	
fo.write('0' + '\n')
fo.close()
	

nombre = "random.in"
fo = open(nombre, "wb")

for z in range(100):
	n = randint(0,23)
	k = 10
	m = (n * n-1 )/2 
	arr = []
	for i in range(n):
		for j in range(n):	
			if i<j:
				nuevo = []
				nuevo.append(i)
				nuevo.append(j)
				nuevo.append(randint(1,100))
				arr.append(nuevo)

	shuffle(arr)
	limite =randint(0,len(arr))
	fo.write(str(n) + " " + str(limite) + " " + str(k) + '\n' )
	for i in range(limite):
		fo.write(str(arr[i][0]) + " " + str(arr[i][1]) + " " + str(arr[i][2]) + '\n')
fo.write('0' + '\n')
fo.close()
