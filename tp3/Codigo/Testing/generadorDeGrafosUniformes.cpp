#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h> 
#include <sys/time.h>
#include <iostream>
#include <sys/timeb.h>
#include <vector>
#include <stack>
#include <algorithm>
#include <iostream>
#include <fstream>

using namespace std;

struct eje
{
    int x, y;

    eje(int paramx, int paramy) : x(paramx), y(paramy) {}
};

vector<eje> ejes;


int main(int argc, char *argv[])
{

	srand(time(NULL));
	int max = 101;

	if(argc < 4)
	{
		cout << "Error, Faltan Parametros" << endl;
		return 1;
	}
	
	int n = atoi(argv[1]);
	int m = atoi(argv[2]);
	int k = atoi(argv[3]);

	//genero todas las posibles aristas del grafo
	for(int i = 0; i < n; i++)
	{
		for(int j = i+1; j < n; j++)
		{
			ejes.push_back(eje(i,j));
		}
	}

	if(ejes.size() < m)
	{
		cout << "Error, no hay suficientes nodos para esta cantidad de ejes" << endl;
		return 0;
	}

	//mezclo todas las posibles aristas del grafo
	random_shuffle (ejes.begin(), ejes.end());

	ofstream myfile;
	myfile.open ("testing/test.txt");

	myfile << n << " " << m << " " << k << endl;

	//tomo las primeras m aristas mezcladas que tengo en el vector.
	for(int i = 0; i < m ; i++)
	{
		myfile << ejes[i].x + 1 << " " << ejes[i].y + 1 << " " << 1 << endl; 
	}

	myfile.close();
	return 0;
}