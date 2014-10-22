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
//#include <chrono>

using namespace std;

#define INFINITO INT_MAX


//idea: en cada paso, tomo un vertice, me fijo en que subconjunto minimiza la suma, y lo agrego ahí.

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

	//hasta aca cree todos las estructuras de datos que voy a necesitar.

	subconjuntos[0].push_back(0);

	//meto el nodo 1 en cualquiera de los conjuntos, por ahora son todos iguales.
	
	en_que_subconjunto_esta_cada_nodo.push_back(0);

	//del punto de arriba, el nodo 1 va a ir en el subconjunto 1, asi que tambien digo eso.

	for(int i = 1; i < n; i++ )
	{
		//tomo el vertice i
		int menorSuma = INFINITO;
		int menorConjunto = 0;

		for(int j = 0; j < k; j++)
		{
			//para cada conjunto
			int aux = 0;
			for(int w = 0; w < subconjuntos[j].size(); w++)
			{
				//veo cuanto "peso" suma agregar este vertice a este conjunto determinado
				aux += matriz_de_adyacencias[j][subconjuntos[j][w]];
			}
			//me guardo el conjunto que minimiza la suma
			if(aux < menorSuma)
			{
				menorSuma = aux;
				menorConjunto = j;
			}
		}
		//agrego el verice i al conjunto que minimiza la suma
		subconjuntos[menorConjunto].push_back(i);

		//esto es para dar la respuesta de una y no tener que andar buscando los valores despues
		en_que_subconjunto_esta_cada_nodo.push_back(menorConjunto);
	}
	//complejidad O(kn^2) creo.

	cout << "Respuesta que hay que dar:" << endl;

	for(int i = 0; i < n; i++)
		cout << en_que_subconjunto_esta_cada_nodo[i] + 1 << " ";
	cout << endl;

	//save it for the mornig after


	cout << endl << "Datos Utiles:" << endl;

	int total = 0;
	for(int j = 0; j < k; j++)
	{
		int aux = 0;
		for(int i = 0; i < subconjuntos[j].size(); i++)
			for(int w = i; w < subconjuntos[j].size(); w++)
				aux += matriz_de_adyacencias[subconjuntos[j][i]][subconjuntos[j][w]];
		cout <<"El Conjunto " << j+1 << " pesa: " <<  aux << endl;
		total += aux;
	}
	cout << "Peso total: " << total << endl;

	return 0;
}