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

//BACKTRACKKKKKKK

int backtrack();
int check();


vector< vector< int> > matriz_de_adyacencias  = vector< vector< int> >(n, vector<int> (n, 0));
vector< vector< int> > subconjuntos;
vector <int> en_que_subconjunto_esta_cada_nodo;

vector <int> rta_final;

int main()
{
	int n,m,k;
	cin >> n;
	cin >> m;
	cin >> k;

	

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


	//inicializo la solución final con cualquier cosa para tener algo contra lo que comparar en las podas
	for(int i = 0; i < n; i++)
	{
		rta_final.push_back(rand() % k);
	}

	//backtrack
	backtrack();

	cout << "Respuesta que hay que dar:" << endl;

	for(int i = 0; i < n; i++)
		cout << rta_final[i] + 1 << " ";
	cout << endl;

	return 0;
}


int backtrack()
{
	int respuesta = check();

	if(respuesta == 1)
		return 0;

	if(respuesta == 0)
	{
		//me fijo si la respuesta es mejor
	}
	for(int i = 0; i < ; subconjuntos.size() ; i++)
	{
		subconjuntos[i].push_back(subconjuntos.size() + 1);

		en_que_subconjunto_esta_cada_nodo.push_back(subconjuntos.size() + 1);

		backtrack(matriz_de_adyacencias,subconjuntos,en_que_subconjunto_esta_cada_nodo);

		subconjuntos[i].pop_back();

		en_que_subconjunto_esta_cada_nodo.pop_back();

	}
	return 0;
}



//check
//0 si llegue al final
//1 podo
//2 sigo

int check();
{
	if(matriz_de_adyacencias.size() == en_que_subconjunto_esta_cada_nodo.size())
	{
		//llegue al final
		return 0;
	}

	//no se... hacá hago podas locas
	return 2;
}
>>>>>>> Stashed changes
