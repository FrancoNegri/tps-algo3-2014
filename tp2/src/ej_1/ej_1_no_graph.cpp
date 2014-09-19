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
#include <chrono>

using namespace std;

struct vuelo
{
  int ini;
  int fin;
  int numeroDeVuelo;
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

vector<vuelo> dijstra_sin_grafo(vector<vuelo> vector_vuelos,int origen,int destino, int cantidad_de_ciudades)
{
	vector<int> costo_de_llegar_a_esta_ciudad;
	vector<vuelo> vuelo_tomado_para_llegar_a_esta_ciudad;
	vuelo_tomado_para_llegar_a_esta_ciudad.resize(cantidad_de_ciudades);
	for(int i = 0; i < cantidad_de_ciudades; i++)
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
			//si el origen esta en las ciudades visitadas y
			//se cumple que el tiempo de arribo a la ciudad es menor que el tiempo de despegue + 2
			if(costo_de_llegar_a_esta_ciudad[vector_vuelos[j].origen] != INT_MAX && vuelo_tomado_para_llegar_a_esta_ciudad[vector_vuelos[j].origen].fin + 2 <= vector_vuelos[j].ini)
			{
				min_costo = min(min_costo, costo_de_llegar_a_esta_ciudad[vector_vuelos[j].origen] + vector_vuelos[j].fin + 2 - vector_vuelos[j].ini);
				vuelo_de_costo_min = vector_vuelos[j];
			}
		}
		// si el costo minimo continua siendo infinito, no existe manera de llegar desde las ciudades ya marcadas al resto de los vertices, detengo dijstra
		if(min_costo == INT_MAX)
		{
			break;	
		}
		costo_de_llegar_a_esta_ciudad[vuelo_de_costo_min.destino] = min_costo;
		vuelo_tomado_para_llegar_a_esta_ciudad[vuelo_de_costo_min.destino] = vuelo_de_costo_min;
	}

	if(costo_de_llegar_a_esta_ciudad[destino] == INT_MAX)
	{
		vuelo_tomado_para_llegar_a_esta_ciudad.erase(vuelo_tomado_para_llegar_a_esta_ciudad.begin(),vuelo_tomado_para_llegar_a_esta_ciudad.end());
	}
	return vuelo_tomado_para_llegar_a_esta_ciudad;
}

void encontrar_camino(vector<vuelo> vuelo_tomado_para_llegar_a_esta_ciudad,int destino,int origen)
{
	vector<vuelo> resultado;
	resultado.push_back(vuelo_tomado_para_llegar_a_esta_ciudad[destino]);
	bool fin = false;
	// partiendo del destino, regenero el camino para llegar a la solucion
	int ciudadAnterior = (vuelo_tomado_para_llegar_a_esta_ciudad[destino].origen);
	while(!fin)
	{
		 vuelo vueloQueTomo = vuelo_tomado_para_llegar_a_esta_ciudad[ciudadAnterior];
		 resultado.push_back(vueloQueTomo);
		 ciudadAnterior = vueloQueTomo.origen;
		 if(ciudadAnterior == origen)
		 	fin = true;
	}
	reverse(resultado.begin(),resultado.end());

	cout << "respuesta que tengo que dar: " << endl;

	cout << resultado[resultado.size() - 1].fin << " " << resultado.size() << " ";
	for(int i; i < resultado.size(); i++)
		cout << resultado[i].numeroDeVuelo << " ";
	cout << endl;
	cout << "estos son los vuelos que toma:" << endl;
	imprimir_vector(resultado);
}



int main(int argc, char *argv[]){


  auto begin = std::chrono::high_resolution_clock::now();

  
  map< string, int> dict_ciudad_vector_distancias;
  int cant_vuelos;
  string origen, destino;
  cin >> origen;
  dict_ciudad_vector_distancias[origen] = 0;
  cin >> destino;
  dict_ciudad_vector_distancias[destino] = 1;
  cin >> cant_vuelos;
  vector< vuelo > vector_vuelos;
  int cantidad_de_ciudades = 2;

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
    v.numeroDeVuelo = i+1;
    vector_vuelos.push_back(v);
  }

  vector<vuelo> vuelo_tomado_para_llegar_a_esta_ciudad = dijstra_sin_grafo(vector_vuelos, dict_ciudad_vector_distancias[origen], dict_ciudad_vector_distancias[destino],cantidad_de_ciudades);


  //para tests:
  auto end = std::chrono::high_resolution_clock::now();
  std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count() << " ";
  //cout << std::endl;


  //linea para imprimir el resultado, descomentar para entregar
  //if(vuelo_tomado_para_llegar_a_esta_ciudad.size() != 0)
  //	encontrar_camino(vuelo_tomado_para_llegar_a_esta_ciudad, dict_ciudad_vector_distancias[destino], dict_ciudad_vector_distancias[origen]);
  //else
  //cout << "no" << endl;
  return 0;
}