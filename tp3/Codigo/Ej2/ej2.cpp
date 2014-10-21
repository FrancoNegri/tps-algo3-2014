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
//#include <chrono>

using namespace std;

#define INFINITO INT_MAX

struct coordenada
{
  int x;
  int y;
};

void agregar_nodos_de_profunidad_k_mas_uno(int nodo, queue<int> *nodos_de_altura_k_mas_uno, vector< vector< int> >  &matriz)
{

	for(int i = 0; i < n; i++)
	{
		if(matriz[nodo.x][i] != 0)
		{
			nodos_de_altura_k_mas_uno.push_back(i);
			//que jodido que es esto, no se me ocurre como seguir
			for()			
		}

	}

}


int main()
{

	int k,n,m;
	cin >> n; //vertices
	cin >> m; //aristas
	cin >> k; //cantidad de particiones

	vector< vector< int> > matriz  = vector< vector< int> >(n, vector<int> (n, 0));

	for(int i = 0; i < m; i++)
	{
		int u,v,w;
		cin >> u;
		cin >> v;
		cin >> w;
		matriz[u-1][v-1] = w;
		matriz[v-1][u-1] = w;
	}

	queue<coordenada> *nodos_de_altura_k = new queue<coordenada>;
	queue<coordenada> *nodos_de_altura_k_mas_uno = new queue<coordenada>;
	int k = 0;
	 
	//meto el primer nodo de todos
	(*nodos_de_altura_k).push(1);

	while(! (*nodos_de_altura_k).empty())
	{
	 	//mientras haya casillas de altura k, las recorro y agrego los nodos validos de altura k+1
	 	while(! (*nodos_de_altura_k).empty())
		 	{
			 	int nodo = (*nodos_de_altura_k).front();
			 	
			 	(*nodos_de_altura_k).pop();

				 agregar_nodos_de_profunidad_k_mas_uno(nodo, nodos_de_altura_k_mas_uno, matriz);
				 //acá tengo que asignarles un conjunto y poner los nodos siguientes
		 	}
		 	delete nodos_de_altura_k;

		 	nodos_de_altura_k = nodos_de_altura_k_mas_uno;

		 	nodos_de_altura_k_mas_uno = new queue<coordenada>(); 

	 }
	return 0;
}