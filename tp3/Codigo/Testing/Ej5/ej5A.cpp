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
#include "../Ej4/busqueda_local.cpp"
#include "../Ej4/busqueda_local2.cpp"
#include <chrono>

using namespace std;

#ifndef INFINITO
#define INFINITO INT_MAX
#endif

#define PORCENTAJEDEMEJORES 40

vector<int> goloso(vector< vector< int> > &matriz_de_adyacencias, vector< vector< int> > &noseusa, int k, int n){
	
	int cuantosMejores = (PORCENTAJEDEMEJORES*n)/100;

	int resultados[cuantosMejores];
	int indices[cuantosMejores];
	

	vector< vector< int> > subconjuntos;

	for(int i = 0; i < k; i++)
	{
		vector< int> aux;
		subconjuntos.push_back(aux);
	}

	vector<int> en_que_subconjunto_esta_cada_nodo;

	//meto el nodo 1 en cualquiera de los conjuntos, por ahora son todos iguales.
	en_que_subconjunto_esta_cada_nodo.push_back(0);
	//del punto de arriba, el nodo 1 va a ir en el subconjunto 1, asi que tambien digo eso.
	en_que_subconjunto_esta_cada_nodo.resize(n);
	subconjuntos[0].push_back(0);
	for(int i = 1; i < n; i++ )
	{

		for(int i = 0; i < cuantosMejores ; i++)
		{
			resultados[i] = INFINITO;
			indices[i] = -1; 
		}

		//tomo el vertice i

		for(int j = 0; j < k; j++)
		{
			//para cada conjunto
			int aux = 0;
			for(int w = 0; w < subconjuntos[j].size(); w++)
			{
				//veo cuanto "peso" suma agregar este vertice a este conjunto determinado
				int candidato = subconjuntos[j][w];
				aux += matriz_de_adyacencias[i][candidato];
			}

			//me guardo los x conjuntos que minimizan la suma
			
			for(int w = 0; w < cuantosMejores; w++)
			{
				if(aux < resultados[w])
				{
					resultados[w] = aux;
					indices[w] = j;
					break;
				}
			}
		}

		int valorQueTomo = rand() % cuantosMejores; // tomo un valor Al Azar entre estos valores

		//agrego el verice i al conjunto que minimiza la suma
		subconjuntos[indices[valorQueTomo]].push_back(i);
		//esto es para dar la respuesta de una y no tener que andar buscando los valores despues
		en_que_subconjunto_esta_cada_nodo[i] = indices[valorQueTomo];
	}
	noseusa = subconjuntos;
	//complejidad O(kn^2) creo.
	return en_que_subconjunto_esta_cada_nodo;
}




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

		en_que_subconjunto_esta_cada_nodo = busqueda_local2(matriz_de_adyacencias, subconjuntos, k, n, en_que_subconjunto_esta_cada_nodo);

		//en_que_subconjunto_esta_cada_nodo = busqueda_local(matriz_de_adyacencias, subconjuntos, k, n, en_que_subconjunto_esta_cada_nodo);

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


					//PARA MEDIR TIEMPOS
					auto begin = std::chrono::high_resolution_clock::now();
					//PARA MEDIR TIEMPOS


	//lo que hace este algoritmo es usar primero greedy para obtener una sol y despues en base a esa sol
	//por busqueda local, buscar una mejora


	en_que_subconjunto_esta_cada_nodo = grasp(matriz_de_adyacencias, subconjuntos, k, n);


					//PARA MEDIR TIEMPOS
					auto end = std::chrono::high_resolution_clock::now();
				  	cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count() << " ";
					//PARA MEDIR TIEMPOS







	cout << "Respuesta Final:" << endl;

	for(int i = 0; i < n; i++)
		cout << en_que_subconjunto_esta_cada_nodo[i] + 1 << " ";
	cout << endl;

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


