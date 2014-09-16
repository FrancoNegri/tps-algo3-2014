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

using namespace std;

struct coordenada
{
  int x;
  int y;
};

coordenada crear_coordenada(int x, int y)
{
	coordenada coord;
	coord.x = x;
	coord.y = y;
	return coord;
}



typedef vector< vector< int > > tablero;

void agregar_nodos_de_profunidad_k_mas_uno(int x, int y,int n,int k, queue<coordenada> &nodos_de_altura_k_mas_uno, vector< vector< vector< int> > >	cantidad_de_saltos_que_tiene_que_dar_el_caballo)
{
	//chequeo el rango, si el caballo salta a una posicion valida y no salte previamente a esta posicion, lo agrego a la cola
	if(x - 2 >= 0)
	{
		if(y - 1 >= 0)
		{
		if(cantidad_de_saltos_que_tiene_que_dar_el_caballo[k][x - 2][y - 1] == INT_MAX)
			nodos_de_altura_k_mas_uno.push(crear_coordenada(x - 2, y - 1));
		}
		if(y + 1 < n)
		{
		if(cantidad_de_saltos_que_tiene_que_dar_el_caballo[k][x - 2][y + 1] == INT_MAX)
			nodos_de_altura_k_mas_uno.push(crear_coordenada(x - 2, y + 1));
		}
	}

	if(x + 2 < n)
	{
		if(y - 1 >= 0)
		{
			if(cantidad_de_saltos_que_tiene_que_dar_el_caballo[k][x + 2][y - 1] == INT_MAX)
				nodos_de_altura_k_mas_uno.push(crear_coordenada(x + 2, y - 1));
		}
		if(y + 1 < n)
		{
			if(cantidad_de_saltos_que_tiene_que_dar_el_caballo[k][x + 2][y + 1] == INT_MAX)
				nodos_de_altura_k_mas_uno.push(crear_coordenada(x + 2, y + 1));
		}
	}
}


int main()
{
	int n;
	int k;
	vector<coordenada> lista_caballos;
	cin >> n;
	cin >> k;

	for(int i = 0; i < k; i++)
	{
		coordenada nuevoCaballo;
		cin >> nuevoCaballo.x;
		cin >> nuevoCaballo.y;
		//para que me quede congruente con las matrices les resto 1
		nuevoCaballo.x--;
		nuevoCaballo.y--;
		lista_caballos.push_back(nuevoCaballo);
	}
	//esta linea magica crea un tablero de n por n
	tablero unTablero(n, vector<int>(n, 0));
	vector<vector< vector< int> > >	cantidad_de_saltos_que_tiene_que_dar_el_caballo(k, vector<vector<int> >(n, vector<int>(n, INT_MAX)));

	for(int i = 0; i < k; i++)
	{
		 queue<coordenada> nodos_de_altura_k;
		 queue<coordenada> nodos_de_altura_k_mas_uno;
		 int k = 0;
		 nodos_de_altura_k.push(lista_caballos[i]);
		 while(!nodos_de_altura_k.empty())
		 {
		 	while(!nodos_de_altura_k.empty())
		 	{
		 	coordenada nodo = nodos_de_altura_k.front();
		 	nodos_de_altura_k.pop();
		 	if(cantidad_de_saltos_que_tiene_que_dar_el_caballo[i][nodo.x][nodo.y] == INT_MAX)
		 		cantidad_de_saltos_que_tiene_que_dar_el_caballo[i][nodo.x][nodo.y] = k;
		 	agregar_nodos_de_profunidad_k_mas_uno(nodo.x, nodo.y,n,i, nodos_de_altura_k_mas_uno, cantidad_de_saltos_que_tiene_que_dar_el_caballo);
		 	agregar_nodos_de_profunidad_k_mas_uno(nodo.y, nodo.x,n,i, nodos_de_altura_k_mas_uno, cantidad_de_saltos_que_tiene_que_dar_el_caballo);
		 	}
		 	nodos_de_altura_k = nodos_de_altura_k_mas_uno;
		 	nodos_de_altura_k_mas_uno = queue<coordenada>();
		 	k++;
		 }
		 
	}

	for(int i = 0; i < k; i++)
	{
	cout << "Saltos necesarios para el caballo: " << i << " llege a la pos de la matriz" << endl << endl;
		for(int j = 0; j < n; j++)
		{
			for(int k = 0; k < n; k++)
			{
				if(cantidad_de_saltos_que_tiene_que_dar_el_caballo[i][j][k] != INT_MAX)
					cout << cantidad_de_saltos_que_tiene_que_dar_el_caballo[i][j][k] << " ";
				else
					cout << "no ";		
			}
			cout << endl;
		}
		cout << endl;
	}
}


