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
#include <chrono>


//capaz habría que cambiar los nombes
#define NODO_NO_MARCADO 6000
#define NODO_MARCADO 7000



using namespace std;

struct coordenada
{
  int x;
  int y;
};

struct tablero
{
  vector< vector< int> > casillas;
  int n;
};

coordenada crear_coordenada(int x, int y)
{
	coordenada coord;
	coord.x = x;
	coord.y = y;
	return coord;
}

tablero crear_tablero(int n)
{
	tablero nuevoTablero;
	nuevoTablero.casillas  = vector< vector< int> >(n, vector<int> (n, NODO_NO_MARCADO));
	nuevoTablero.n = n;
	return nuevoTablero;
}


void agregar_nodos_de_profunidad_k_mas_uno(coordenada nodo, queue<coordenada> *nodos_de_altura_k_mas_uno, tablero unTablero)
{
	//chequeo el rango, si el caballo salta a una posicion valida y no salte previamente a esta posicion, lo agrego a la cola
	//me aseguro de no meter dos veces en la cola el mismo nodo 'maracandolo', asi, si de dos nodos de altura k puedo saltar al mismo nodo de altura k+1, solo lo agrego la primera vez

	//muy cabeza
	

	if(nodo.x - 2 >= 0)
	{
		if(nodo.y - 1 >= 0)
		{
		if(unTablero.casillas[nodo.x - 2][nodo.y - 1] == NODO_NO_MARCADO)
			{
				
				unTablero.casillas[nodo.x - 2][nodo.y - 1] = NODO_MARCADO;
				(*nodos_de_altura_k_mas_uno).push(crear_coordenada(nodo.x - 2, nodo.y - 1));
			}
		}
		if(nodo.y + 1 < unTablero.n)
		{
			if(unTablero.casillas[nodo.x - 2][nodo.y + 1] == NODO_NO_MARCADO)
			{

				unTablero.casillas[nodo.x - 2][nodo.y + 1] = NODO_MARCADO;
				(*nodos_de_altura_k_mas_uno).push(crear_coordenada(nodo.x - 2, nodo.y + 1));				
			}
		}
	}

	if(nodo.x + 2 < unTablero.n)
	{
		if(nodo.y - 1 >= 0)
		{
			if(unTablero.casillas[nodo.x + 2][nodo.y - 1] == NODO_NO_MARCADO)
			{
				unTablero.casillas[nodo.x + 2][nodo.y - 1] = NODO_MARCADO;
				(*nodos_de_altura_k_mas_uno).push(crear_coordenada(nodo.x + 2, nodo.y - 1));				
			}
		}
		if(nodo.y + 1 < unTablero.n)
		{
			if(unTablero.casillas[nodo.x + 2][nodo.y + 1] == NODO_NO_MARCADO)
			{
				unTablero.casillas[nodo.x + 2][nodo.y + 1] = NODO_MARCADO;
				(*nodos_de_altura_k_mas_uno).push(crear_coordenada(nodo.x + 2, nodo.y + 1));
			}
		}
	}
	if(nodo.x - 1 >= 0)
	{
		if(nodo.y - 2 >= 0)
		{
			if(unTablero.casillas[nodo.x - 1][nodo.y - 2] == NODO_NO_MARCADO)
			{
				unTablero.casillas[nodo.x - 1][nodo.y - 2] = NODO_MARCADO;
				(*nodos_de_altura_k_mas_uno).push(crear_coordenada(nodo.x - 1, nodo.y - 2));
			}	
		}
		if(nodo.y + 2 < unTablero.n)
		{
			if(unTablero.casillas[nodo.x - 1][nodo.y + 2] == NODO_NO_MARCADO)
			{
				unTablero.casillas[nodo.x - 1][nodo.y + 2] = NODO_MARCADO;
				(*nodos_de_altura_k_mas_uno).push(crear_coordenada(nodo.x - 1, nodo.y + 2));			
			}
		}
	}

	if(nodo.x + 1 < unTablero.n)
	{
		if(nodo.y - 2 >= 0)
		{
			if(unTablero.casillas[nodo.x + 1][nodo.y - 2] == NODO_NO_MARCADO)
			{
				unTablero.casillas[nodo.x + 1][nodo.y - 2] = NODO_MARCADO;
				(*nodos_de_altura_k_mas_uno).push(crear_coordenada(nodo.x + 1, nodo.y - 2));
			}
		}
		if(nodo.y + 2 < unTablero.n)
		{
			if(unTablero.casillas[nodo.x + 1][nodo.y + 2] == NODO_NO_MARCADO)
			{
				unTablero.casillas[nodo.x + 1][nodo.y + 2] = NODO_MARCADO;
				(*nodos_de_altura_k_mas_uno).push(crear_coordenada(nodo.x + 1, nodo.y + 2));				
			}
		}
	}
}



int main()
{
	int n;
	int cantidad_de_caballos;
	vector<coordenada> lista_caballos;
	cin >> n;
	cin >> cantidad_de_caballos;


	//mido tiempos

	auto begin = std::chrono::high_resolution_clock::now();



	for(int i = 0; i < cantidad_de_caballos; i++)
	{
		coordenada nuevoCaballo;
		cin >> nuevoCaballo.x;
		cin >> nuevoCaballo.y;
		//para que me quede congruente con las matrices les resto 1
		nuevoCaballo.x--;
		nuevoCaballo.y--;
		lista_caballos.push_back(nuevoCaballo);
	}

	// en este tablero voy guardando cuanto le cuesta al caballo i, llegar a la pocision (x,y) del tablero
	vector<tablero> tablero_para_caballo_i(cantidad_de_caballos,crear_tablero(n));

	int contadorDeCasillas = 0;
	for(int caballo_i = 0; caballo_i < cantidad_de_caballos; caballo_i++)
	{
		 queue<coordenada> *nodos_de_altura_k = new queue<coordenada>;
		 queue<coordenada> *nodos_de_altura_k_mas_uno = new queue<coordenada>;
		 int k = 0;
		 
		 //meto el primer nodo de todos (donde esta el caballo inicialmente)
		 (*nodos_de_altura_k).push(lista_caballos[caballo_i]);

		 while(! (*nodos_de_altura_k).empty())
		 {
		 	//mientras haya casillas de altura k, las recorro y agrego los nodos validos de altura k+1
		 	while(! (*nodos_de_altura_k).empty())
		 	{
			 	
			 	coordenada nodo = (*nodos_de_altura_k).front();
			 	
			 	(*nodos_de_altura_k).pop();
			 	
			 	//tengo asegurado que esto esto solo se va a asignar una vez, no necesito ifs
				 tablero_para_caballo_i[caballo_i].casillas[nodo.x][nodo.y] = k;

				 agregar_nodos_de_profunidad_k_mas_uno(nodo, nodos_de_altura_k_mas_uno, tablero_para_caballo_i[caballo_i]);
				 //contadorDeCasillas++;
				 //cout << "casillas en esta profundidad" << contadorDeCasillas << endl;
		 	}
		 	//ok, ya no hay nodos de altura k, ahora paso a k+1, (que va a ser el nuevo k), y borro lo que había en k+1
		 	//cout << "salto de k a k+1." << endl;
		 	//cout << "k:" << k << endl;

		 	delete nodos_de_altura_k;

		 	nodos_de_altura_k = nodos_de_altura_k_mas_uno;

		 	nodos_de_altura_k_mas_uno = new queue<coordenada>(); 
		 	
		 	k++;
		 }
		 
	}


	//esto es para ver las matrices que quedan despues de hacer todos los bfeses.
	
	for(int i = 0; i <  cantidad_de_caballos;i++)
	{
	cout << "Saltos necesarios para el caballo: " << i << " salte al casillero" << endl << endl;
		for(int j = 0; j < n; j++)
		{
			for(int k = 0; k < n; k++)
			{
				if(tablero_para_caballo_i[i].casillas[j][k] > NODO_MARCADO)
				{
					cout << tablero_para_caballo_i[i].casillas[j][k] << " ";
				}
				else
				{
					cout << "no ";	
				}
			}
			cout << endl;
		}
		cout << endl;
	}
	
	int suma_min = INT_MAX;
	coordenada nodo_minimo;

	for(int j = 0; j < n; j++)
	{
		for(int k = 0; k < n; k++)
		{
			//para cada casilla voy sumando cuantos saltos le cuesta llegar a todos los caballos ahí
			int acum = 0;
			for(int i = 0; i <  cantidad_de_caballos;i++)
			{
				if(tablero_para_caballo_i[i].casillas[j][k] < INT_MAX-1)
				{
					acum += tablero_para_caballo_i[i].casillas[j][k];
				}
				else
				{
					acum = INT_MAX;
					break;
				}
			}
			// si es menor, actualizo, ahora tengo una manera de llegar que cuesta menos saltos
			if(suma_min > acum)
			{
				suma_min = acum;
				nodo_minimo.x = j;
				nodo_minimo.y = k;
			}
		}
	}


	// mido tiempos
	auto end = std::chrono::high_resolution_clock::now();
  	std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count() << " ";


  	//Descomentar a la hora de entregaaaaar!!!!
	// si el minimo es NODO_NO_MARCADO, no hay manera de que todos los caballos lleguen a la misma pocicion
	/*if(suma_min == INT_MAX)
		cout << "no" << endl;
	else
		cout << nodo_minimo.x + 1 << " " << nodo_minimo.y + 1 << " " << suma_min << endl;
	return 0;*/
}


