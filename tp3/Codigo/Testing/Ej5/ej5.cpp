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
#include "../Ej4/busqueda_local2.cpp"
//#include <chrono>

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

		en_que_subconjunto_esta_cada_nodo = busqueda_local2(matriz_de_adyacencias, subconjuntos, k, n, en_que_subconjunto_esta_cada_nodo);

		en_que_subconjunto_esta_cada_nodo = busqueda_local(matriz_de_adyacencias, subconjuntos, k, n, en_que_subconjunto_esta_cada_nodo);



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

	//lo que hace este algoritmo es usar primero greedy para obtener una sol y despues en base a esa sol
	//por busqueda local, buscar una mejora


	en_que_subconjunto_esta_cada_nodo = grasp(matriz_de_adyacencias, subconjuntos, k, n);

/*	//busqueda local
	subconjuntos[0].push_back(0);
	en_que_subconjunto_esta_cada_nodo.push_back(0);
	for(int i = 1; i < n; i++ )
	{
		int menorSuma = INFINITO;
		int menorConjunto = 0;
		for(int j = 0; j < k; j++)
		{
			int aux = 0;
			for(int w = 0; w < subconjuntos[j].size(); w++)
			{
				aux += matriz_de_adyacencias[j][subconjuntos[j][w]];
			}
			if(aux < menorSuma)
			{
				menorSuma = aux;
				menorConjunto = j;
			}
		}

		//acá en vez de elegir el mejor tendría que elegir de manera random uno de los "alfa" mejores
		//ver teorica: http://www.dc.uba.ar/materias/aed3/2014/2c/teorica/algo3_euler.pdf

		cout << endl << "***** Warning: Goloso random not implemented *********" << endl;


		subconjuntos[menorConjunto].push_back(i);
		en_que_subconjunto_esta_cada_nodo.push_back(menorConjunto);
	}

	cout << endl << "Rta Obtenida por Goloso: " << endl;
	for(int i = 0; i < n; i++)
		cout << en_que_subconjunto_esta_cada_nodo[i] + 1 << " ";
	cout << endl;





	//BusquedaLocal
	bool SeEncontroMejorSol = true;
	while(SeEncontroMejorSol)
	{
		SeEncontroMejorSol = false;
		for(int i = 0; i < n; i++)
		{
			int conjuntoActualDe_i = en_que_subconjunto_esta_cada_nodo[i];
			int sumaDelConjuntoDe_i = 0;
			for(int j = 0; j < subconjuntos[conjuntoActualDe_i].size(); j++)
				sumaDelConjuntoDe_i += matriz_de_adyacencias[i][subconjuntos[conjuntoActualDe_i][j]];
			for(int j = 0; j < k; j++)
			{
				int sumaPoniendoA_i_enOtroConjunto = 0;
				if(j != conjuntoActualDe_i)
				{
					for(int w = 0; w < subconjuntos[j].size(); w++)
							sumaPoniendoA_i_enOtroConjunto += matriz_de_adyacencias[i][subconjuntos[j][w]];
					if(sumaPoniendoA_i_enOtroConjunto < sumaDelConjuntoDe_i)
					{
						en_que_subconjunto_esta_cada_nodo[i] = j;
						subconjuntos[j].push_back(i);
						for(int aux = 0; aux < subconjuntos[conjuntoActualDe_i].size(); aux++)
							if(subconjuntos[conjuntoActualDe_i][aux] == i)
							{
								subconjuntos[conjuntoActualDe_i].erase(subconjuntos[conjuntoActualDe_i].begin() + aux);
								break;
							}

						SeEncontroMejorSol = true;
						break;
					}
				}
			}
		}
	}
*/
	//Grasp: O(kn^2), Una iteracion de busquedaLocal: O(kn^2)

	// cout << "Respuesta Final:" << endl;

	// for(int i = 0; i < n; i++)
	// 	cout << en_que_subconjunto_esta_cada_nodo[i] + 1 << " ";
	// cout << endl;

	// cout << endl << "Datos Utiles:" << endl;

	int total = 0;
	for(int j = 0; j < k; j++)
	{
		int aux = 0;
		for(int i = 0; i < subconjuntos[j].size(); i++)
			for(int w = i; w < subconjuntos[j].size(); w++)
				aux += matriz_de_adyacencias[subconjuntos[j][i]][subconjuntos[j][w]];
		//cout <<"El Conjunto " << j+1 << " pesa: " <<  aux << endl;
		total += aux;
	}
	cout << total << endl;






	return 0;
}
