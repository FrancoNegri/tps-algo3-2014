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

using namespace std;

struct vuelo
{
  int ini;
  int fin;
  string origen;
  string destino;
};

typedef vector< vector< vector< vuelo > > > matriz_vuelos;

struct itinerario
{
  string origen;
  string destino;
  int cant_vuelos;
  vector< vector< vector< vuelo > > > m;
};

vector< vector< vector< vuelo > > > crear_matriz_de_vuelos(vector< vuelo > vector_vuelos, map< string, int> dict_ciudad_vector_distancias){

  int size_matrix = dict_ciudad_vector_distancias.size();
  vector< vector< vector< vuelo > > > m( size_matrix, vector< vector< vuelo > >(size_matrix));


  for (int i = 0; i < dict_ciudad_vector_distancias.size(); ++i) {
    vector < vector < vuelo > > v;
    m.push_back(v);
    for (int j = 0; j < dict_ciudad_vector_distancias.size(); ++j)
    {
      vector<vuelo> vector_vuelos;
      m[i][j] = vector_vuelos;
    }
  }

  for (std::vector<vuelo>::iterator i = vector_vuelos.begin(); i != vector_vuelos.end(); ++i) {
    vuelo v =(*i);
    m[dict_ciudad_vector_distancias[v.origen]][dict_ciudad_vector_distancias[v.destino]].push_back(v);
  }
  return m; 
}

void imprimir_matriz(vector< vector< vector< vuelo > > > m)
{
 for (int i = 0; i < m.size(); i++)
 {
   vector< vector<vuelo> > v = m[i];
   for (int j = 0; j < v.size(); j++)
   {
      cout << m[i][j].size() << " ";
      /*if(m[i][j].size() == 0 ) {
       cout << " -- --;" ; 
      }*/
      /*for (int k = 0; k < m[i][j].size(); ++k)
      {

        cout << " " << m[i][j][k].ini << " " << m[i][j][k].fin << ";" ;
      }*/
   }
   cout << endl;
 }
 cout << endl;
}


void imprimir_vector(vector<vuelo> vec)
{
  for (std::vector<vuelo>::iterator it = vec.begin(); it != vec.end(); ++it)
  {
      cout << it->origen << " " << it->destino << " " << it->ini << " " << it->fin << endl ;
  }
}

void imprimir_map(map < string, int > mapa ) {
  for(map<string, int >::const_iterator it = mapa.begin(); it != mapa.end(); ++it) {
      cout << it->first << " " << it->second  << endl;
  }
}


int main(int argc, char *argv[]){
  itinerario it;
  cin >> it.origen;
  cin >> it.destino;
  cin >> it.cant_vuelos;
  map< string, int> dict_ciudad_vector_distancias;
  vector< vuelo > vector_vuelos;
  string origen;
  string destino;
  int cantidad_de_ciudades = 0;

  for (int i = 0; i < it.cant_vuelos; ++i) {
    vuelo v;
    cin >> v.origen;
    cin >> v.destino;

    //checkeo si tengo los destinos en mi vector de coordenadas
    if(dict_ciudad_vector_distancias.find(v.origen) == dict_ciudad_vector_distancias.end()) {
      dict_ciudad_vector_distancias[v.origen] = cantidad_de_ciudades;
      cantidad_de_ciudades++;
    }

    if(dict_ciudad_vector_distancias.find(v.destino) == dict_ciudad_vector_distancias.end()) {
      dict_ciudad_vector_distancias[v.destino] = cantidad_de_ciudades;
      cantidad_de_ciudades++; 
    }

    cin >> v.ini;
    cin >> v.fin;
    vector_vuelos.push_back(v);
  }

  matriz_vuelos m = crear_matriz_de_vuelos(vector_vuelos, dict_ciudad_vector_distancias);
  vector_camino_minimo = 
  /*imprimir_vector(vector_vuelos);
  imprimir_map(dict_ciudad_vector_distancias);*/
  imprimir_matriz(m);
  return 0;
}