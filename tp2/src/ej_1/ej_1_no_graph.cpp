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

using namespace std;

struct vuelo
{
  int ini;
  int fin;
  int origen;
  int destino;
};

void encontrar_camino(vector<vuelo> vuelo_tomado_para_llegar_a_esta_ciudad, int destino, int origen);

void imprimir_vector(vector<vuelo> vec)
{
  for (std::vector<vuelo>::iterator it = vec.begin(); it != vec.end(); ++it)
  {
      cout << it->origen << " " << it->destino << " " << it->ini << " " << it->fin << endl ;
  }
}

void dijstra_sin_grafo(vector<vuelo> vector_vuelos,int origen,int destino)
{
	set<int> ciudades_visitadas;
	vector<int> costo_de_llegar_a_esta_ciudad;
	vector<vuelo> vuelo_tomado_para_llegar_a_esta_ciudad;
	ciudades_visitadas.insert(origen);
	vuelo_tomado_para_llegar_a_esta_ciudad.resize(vector_vuelos.size());//en realidad esto es cantidad de ciudades, cambiar
	for(int i = 0; i < vector_vuelos.size(); i++)//en realidad esto es cantidad de ciudades, cambiar
	{
		costo_de_llegar_a_esta_ciudad.push_back(INT_MAX);
	}

	costo_de_llegar_a_esta_ciudad[origen] = 0;

	for(int i = 0; i < vector_vuelos.size(); i++)
	{
		int min_costo = INT_MAX;
		vuelo vuelo_de_costo_min;
		for(int j = 0; j < vector_vuelos.size(); j++)
		{
			//si el origen esta en las ciudades visitadas
			if(ciudades_visitadas.find(vector_vuelos[j].origen) != ciudades_visitadas.end() && vector_vuelos[j].ini < vector_vuelos[j].fin + 2)
			{
				min_costo = min(min_costo, costo_de_llegar_a_esta_ciudad[vector_vuelos[j].origen] + vector_vuelos[j].fin + 2 - vector_vuelos[j].ini);
				vuelo_de_costo_min = vector_vuelos[j];
			}
		}
	costo_de_llegar_a_esta_ciudad[vuelo_de_costo_min.destino] = min_costo;
	ciudades_visitadas.insert(vuelo_de_costo_min.destino);
	vuelo_tomado_para_llegar_a_esta_ciudad[vuelo_de_costo_min.origen] = vuelo_de_costo_min;
	}
	encontrar_camino(vuelo_tomado_para_llegar_a_esta_ciudad, destino, origen);
}

void encontrar_camino(vector<vuelo> vuelo_tomado_para_llegar_a_esta_ciudad,int destino,int origen)
{
	vector<vuelo> resultado;
	resultado.push_back(vuelo_tomado_para_llegar_a_esta_ciudad[destino]);
	bool fin = false;
	int ciudadAnterior = (vuelo_tomado_para_llegar_a_esta_ciudad[destino].origen);
	while(!fin)
	{
		 vuelo vueloQueTomo = vuelo_tomado_para_llegar_a_esta_ciudad[ciudadAnterior];
		 resultado.push_back(vueloQueTomo);
		 if(ciudadAnterior == origen)
		 	fin = true;
		 ciudadAnterior = vueloQueTomo.origen;
	}
	reverse(resultado.begin(),resultado.end());

	imprimir_vector(resultado);
}



int main(int argc, char *argv[]){
  int cant_vuelos;
  string origen, destino;
  cin >> origen;
  cin >> destino;
  cin >> cant_vuelos;
  map< string, int> dict_ciudad_vector_distancias;
  vector< vuelo > vector_vuelos;

  int cantidad_de_ciudades = 0;

  for (int i = 0; i < cant_vuelos; i++) {
    vuelo v;
    string origen_vuelo, destino_vuelo;

    cin >> origen_vuelo;
    cin >> destino_vuelo;

    //checkeo si tengo los destinos en mi vector de coordenadas
    if(dict_ciudad_vector_distancias.find(origen_vuelo) == dict_ciudad_vector_distancias.end()) {
      dict_ciudad_vector_distancias[origen_vuelo] = cantidad_de_ciudades;
      cantidad_de_ciudades++;
    }
    

    if(dict_ciudad_vector_distancias.find(destino_vuelo) == dict_ciudad_vector_distancias.end()) {
      dict_ciudad_vector_distancias[destino_vuelo] = cantidad_de_ciudades;
      cantidad_de_ciudades++; 
    }

    // cada ciudad es representada con un numero que a su vez se guarda en un diccionario.
    v.origen = dict_ciudad_vector_distancias[origen_vuelo];
    v.destino = dict_ciudad_vector_distancias[destino_vuelo];

    cin >> v.ini;
    cin >> v.fin;
    vector_vuelos.push_back(v);
  }

  dijstra_sin_grafo(vector_vuelos, dict_ciudad_vector_distancias[origen], dict_ciudad_vector_distancias[destino]);
  return 0;
}