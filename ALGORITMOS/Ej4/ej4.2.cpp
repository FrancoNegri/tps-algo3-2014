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
#include "busqueda_local2.cpp"

using namespace std;

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
		int j,h,p;
		cin >> j;
		cin >> h;
		cin >> p;
		matriz_de_adyacencias[j-1][h-1] = p;
		matriz_de_adyacencias[h-1][j-1] = p;
	}

	srand (time(NULL));

	//cout << "Parto de esta solucion: " << endl;
	for(int i = 0; i < n; i++)
	{
		int conjuntoRandom = rand() % k;
	//	cout << conjuntoRandom + 1 << " ";
		en_que_subconjunto_esta_cada_nodo.push_back(conjuntoRandom);
	}
	//cout << endl;

	//esta estructura es mas comoda para revisar las sumas
	for(int i = 0; i < n; i++)
	{
		subconjuntos[en_que_subconjunto_esta_cada_nodo[i]].push_back(i);
	}


	en_que_subconjunto_esta_cada_nodo = busqueda_local2(matriz_de_adyacencias, subconjuntos, k, n, en_que_subconjunto_esta_cada_nodo);
	//Una iteracion: O(n^2 + n*k*(n + n)) = O(k*n^2) good

	 for(int i = 0; i < n; i++)
		cout << en_que_subconjunto_esta_cada_nodo[i] + 1 << " ";
	 cout << endl;

	// cout << endl << "Datos Utiles:" << endl;

	return 0;
}