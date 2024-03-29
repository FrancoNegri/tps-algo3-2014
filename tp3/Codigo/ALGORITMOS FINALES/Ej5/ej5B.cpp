#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <sys/time.h>
#include <set>
#include <map>
#include <cstdlib>
#include <ctime>
#include <sys/timeb.h>
#include <climits>
#include <algorithm>
#include <queue>
#include <set>
#include "../Ej3/goloso.cpp"
#include "../Ej4/busqueda_local.cpp"
#include "../Ej4/busqueda_local3.cpp"

using namespace std;

#ifndef INFINITO
#define INFINITO INT_MAX
#endif

vector <int> grasp(vector< vector< int> > &matriz_de_adyacencias, vector< vector< int> > &subconjuntos, int k, int n)
{

	srand(unsigned(time(NULL)));
	int cantidadDeVecesQueSeLlegoAmejorSol = 0;
	int min_total = INFINITO;
	vector <int> mejor_solucion;
	vector <int> en_que_subconjunto_esta_cada_nodo;
	
	//for (int h = 0; h < 10000000; ++h)
	while(cantidadDeVecesQueSeLlegoAmejorSol < 1000 )
	{
		en_que_subconjunto_esta_cada_nodo = goloso(matriz_de_adyacencias, subconjuntos, k, n);

		en_que_subconjunto_esta_cada_nodo = busqueda_local(matriz_de_adyacencias, subconjuntos, k, n, en_que_subconjunto_esta_cada_nodo);

		en_que_subconjunto_esta_cada_nodo = busqueda_local3(matriz_de_adyacencias, subconjuntos, k, n, en_que_subconjunto_esta_cada_nodo);



		int total = 0;
		for(int j = 0; j < k; j++)
		{
			int aux = 0;
			for(int i = 0; i < subconjuntos[j].size(); i++)
				for(int w = i; w < subconjuntos[j].size(); w++)
					aux += matriz_de_adyacencias[subconjuntos[j][i]][subconjuntos[j][w]];
			total += aux;
		}

		if(total < min_total)
		{
			min_total = total;
			mejor_solucion = en_que_subconjunto_esta_cada_nodo;
			cantidadDeVecesQueSeLlegoAmejorSol = 0;
		}
		else
			cantidadDeVecesQueSeLlegoAmejorSol++;
	}
	return mejor_solucion;
}

int main()
{
	int n,m,k;
	cin >> n;
	cin >> m;
	cin >> k;

	vector< vector< int> > matriz_de_adyacencias  = vector< vector< int> >(n, vector<int> (n, 0));
	vector< vector< int> > subconjuntos;
	vector <int> en_que_subconjunto_esta_cada_nodo;

	for(int i = 0; i < k; i++)
	{
		vector< int> aux;
		subconjuntos.push_back(aux);
	}


	for(int i = 0; i < m; i++)
	{
		int j,k,p;
		cin >> j;
		cin >> k;
		cin >> p;
		matriz_de_adyacencias[j-1][k-1] = p;
		matriz_de_adyacencias[k-1][j-1] = p;
	}


	en_que_subconjunto_esta_cada_nodo = grasp(matriz_de_adyacencias, subconjuntos, k, n);


	for(int i = 0; i < n; i++)
	 	cout << en_que_subconjunto_esta_cada_nodo[i] + 1 << " ";
	 cout << endl;


	return 0;
}
