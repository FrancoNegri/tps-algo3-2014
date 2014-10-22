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



	//busqueda local
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

	//Grasp: O(kn^2), Una iteracion de busquedaLocal: O(kn^2)

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