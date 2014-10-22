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

//idea: genero una solución al azar (es decir, para cada nodo, lo asigno a un subconjunto cualquiera)
//Vecindad 1: Para cada nodo, pruebo con quitarlo del conjunto y agregarlo a uno que mejore el peso.
//Vecindad 2: para cada nodo, lo mismo que 1, pero ademas intento swapear nodos...? ver

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
	
	//genero una sol cualquiera

	//(esto es para obtener semillas random)
	srand (time(NULL));

	cout << "Parto de esta solucion: " << endl;
	for(int i = 0; i < n; i++)
	{
		int conjuntoRandom = rand() % k;
		cout << conjuntoRandom + 1 << " ";
		en_que_subconjunto_esta_cada_nodo.push_back(conjuntoRandom);
	}
	cout << endl;

	//esta estructura es mas comoda para revisar las sumas
	for(int i = 0; i < n; i++)
	{
		subconjuntos[en_que_subconjunto_esta_cada_nodo[i]].push_back(i);
	}


	//aca tengo que empezar a buscar localmente
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
			//Ok, ahora se cuanto peso agrega tener a i en este conjunto en particular
			//hay un conjunto donde i agregue menos peso?
			for(int j = 0; j < k; j++)
			{
				//para cada conjunto hago la suma...
				int sumaPoniendoA_i_enOtroConjunto = 0;
				if(j != conjuntoActualDe_i)
				{
					for(int w = 0; w < subconjuntos[j].size(); w++)
							sumaPoniendoA_i_enOtroConjunto += matriz_de_adyacencias[i][subconjuntos[j][w]];
					//me fijo...
					if(sumaPoniendoA_i_enOtroConjunto < sumaDelConjuntoDe_i)
					{
						//cambio a i de conjunto
						en_que_subconjunto_esta_cada_nodo[i] = j;

						//lo pongo en el conjunto nuevo...
						subconjuntos[j].push_back(i);

						//lo saco del conjunto viejo...
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

	//Una iteracion: O(n^2 + n*k*(n + n)) = O(k*n^2) good


	cout << "Respuesta que hay que dar:" << endl;

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