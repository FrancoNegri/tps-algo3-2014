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
#include "goloso.cpp"
#include <chrono>

using namespace std;

int main()
{
	int n,m,k;
	cin >> n;
	cin >> m;
	cin >> k;

	vector< vector< int> > matriz_de_adyacencias  = vector< vector< int> >(n, vector<int> (n, 0));
	vector< vector< int> > subconjuntos;
	vector<int> en_que_subconjunto_esta_cada_nodo;

	for(int i = 0; i < k; i++)
	{
		vector< int> aux;
		subconjuntos.push_back(aux);
	}


	for(int i = 0; i < m; i++)
	{
		int j,h,p;
		cin >> j;
		cin >> h;
		cin >> p;
		matriz_de_adyacencias[j-1][h-1] = p;
		matriz_de_adyacencias[h-1][j-1] = p;
	}

					//PARA MEDIR TIEMPOS
					auto begin = std::chrono::high_resolution_clock::now();
					//PARA MEDIR TIEMPOS

	en_que_subconjunto_esta_cada_nodo = goloso(matriz_de_adyacencias, subconjuntos, k, n);






					//PARA MEDIR TIEMPOS
					auto end = std::chrono::high_resolution_clock::now();
				  	cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count() << " ";
					//PARA MEDIR TIEMPOS








	// cout << "Respuesta que hay que dar:" << endl;

	// for(int i = 0; i < n; i++)
	// 	cout << en_que_subconjunto_esta_cada_nodo[i] + 1 << " ";
	// cout << endl;

	//save it for the mornig after


	//cout << endl << "Datos Utiles:" << endl;

	// int total = 0;
	// for(int j = 0; j < k; j++)
	// {
	// 	int aux = 0;
	// 	for(int i = 0; i < subconjuntos[j].size(); i++)
	// 		for(int w = i; w < subconjuntos[j].size(); w++)
	// 			aux += matriz_de_adyacencias[subconjuntos[j][i]][subconjuntos[j][w]];
	// 	//cout <<"El Conjunto " << j+1 << " pesa: " <<  aux << endl;
	// 	total += aux;
	// }
	// cout << total << endl;

	return 0;
}