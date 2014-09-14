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
  string origen;
  string destino;
  int orden;
};

typedef vector< vector< vector< vuelo > > > matriz_vuelos;

struct itinerario
{
  string origen;
  string destino;
  int cant_vuelos;
  vector< vector< vector< vuelo > > > m;
};


void imprimir_matriz(vector< vector< vector< vuelo > > > m)
{
 for (int i = 0; i < m.size(); i++)
 {
   vector< vector<vuelo> > v = m[i];
   for (int j = 0; j < v.size(); j++)
   {
      /*cout << m[i][j].size() << " ";*/
      for (int k = 0; k < m[i][j].size(); ++k)
      {

        cout << " " << m[i][j][k].ini << " " << m[i][j][k].fin << "," ;
      }

      if(m[i][j].size() == 0 ) {
       cout << " -- --;" ; 
      } else {
        cout  << ";";
      }
   }
   cout << endl;
 }
 cout << endl;
}

void imprimir_map(map < string, int > mapa ) {
  for(map<string, int >::const_iterator it = mapa.begin(); it != mapa.end(); ++it) {
      cout << it->first << " " << it->second  << endl;
  }
}

void imprimir_vector(vector<vuelo> vec)
{
  for (std::vector<vuelo>::iterator it = vec.begin(); it != vec.end(); ++it)
  {
      cout << it->origen << " " << it->destino << " " << it->ini << " " << it->fin << endl ;
  }
}

void imprimir_previous(vector<int> vec){
  for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
  {
      cout << (*it) << " ";
  }
   cout << endl ;
}


void impimir_vuelo(vuelo v){
  cout << v.origen << " " << v.destino << " " <<  v.ini << " " << v.fin << endl;
}

bool min_vuelo(vuelo i, vuelo j) {
  return i.fin < j.fin; 
}

vector<vuelo> filtrar_vuelos_con_ini_mayor_a_costo_de_llegar_a_la_ciudad(vector<vuelo> vuelos_sin_filtrar, int costo, set<int> ciudades_visitadas, map< string, int> dict_ciudad_vector_distancias, int ciudad){
  vector<vuelo> res;
  for (vector<vuelo>::iterator i = vuelos_sin_filtrar.begin(); i != vuelos_sin_filtrar.end(); ++i)
  {
    vuelo v = (*i);
    
    if(dict_ciudad_vector_distancias[v.origen] != ciudad) {
      continue;
    }

    vuelo nuevo = v;

    if(v.ini > costo){
      if(ciudades_visitadas.find(dict_ciudad_vector_distancias[v.destino]) == ciudades_visitadas.end())
      {
        res.push_back(nuevo);
      }
    }
  }
  return res;
}

vuelo buscar_eje_minimo(vector<vuelo> vector_vuelos, set<int> ciudades_visitadas, vector<int> distancias_a_ciudades, map< string, int> dict_ciudad_vector_distancias){
  set<int>::iterator it;
  vuelo vuelo_min;
  vuelo_min.orden = INT_MAX;
  vuelo_min.fin = INT_MAX;
  vuelo candidato_vuelo_min;

  //por cada ciudad visitada, filtro los ejes que puedo tomar, que depende de lo que me costo llegar a la ciudad
  for (it = ciudades_visitadas.begin(); it != ciudades_visitadas.end(); ++it)
  {
      int ciudad = *it;
      int costo_de_llegar_a_la_ciudad = distancias_a_ciudades[ciudad];


      vector<vuelo> vector_vuelos_filtrados_por_costo_llegada = filtrar_vuelos_con_ini_mayor_a_costo_de_llegar_a_la_ciudad(vector_vuelos, costo_de_llegar_a_la_ciudad, ciudades_visitadas, dict_ciudad_vector_distancias, ciudad);
      
      cout << vector_vuelos_filtrados_por_costo_llegada.size() << endl;

      if(vector_vuelos_filtrados_por_costo_llegada.size() != 0){
        candidato_vuelo_min = *min_element(vector_vuelos_filtrados_por_costo_llegada.begin(), vector_vuelos_filtrados_por_costo_llegada.end(),min_vuelo);

        if(candidato_vuelo_min.fin < vuelo_min.fin){
          vuelo_min = candidato_vuelo_min;
        }
      }
  }

  if(vuelo_min.orden == INT_MAX) {
    cout << "no" << endl;
    exit(0);
  }

  return vuelo_min;
}


vector<string> buscar_caminimo_min(string origen, string destino, vector< vector< vector< vuelo > > > m, map< string, int>dict_ciudad_vector_distancias, vector< vuelo > vector_vuelos){

  // no visite ninguna ciudad  
  set<int> ciudades_no_visitadas;
  for (int i=0; i<dict_ciudad_vector_distancias.size(); ++i) {
    ciudades_no_visitadas.insert(i);   
  }
  ciudades_no_visitadas.erase(dict_ciudad_vector_distancias[origen]);

  // inicializo el vector de distancias a inf
  vector<int> distancias_a_ciudades(dict_ciudad_vector_distancias.size(), INT_MAX);
  // excepto la distancia origen
  distancias_a_ciudades[dict_ciudad_vector_distancias[origen]] = 0;


  // vector de ciudades visitadas, solamente con la ciudad origen al principio
  set<int> ciudades_visitadas;
  ciudades_visitadas.insert(dict_ciudad_vector_distancias[origen]);

  vuelo vuelo_minimo;

  vector<int> previous(dict_ciudad_vector_distancias.size(), 0);


  while(!ciudades_no_visitadas.empty()){
    //Busco el minimo eje con una pata en las ciudades visitadas
    vuelo_minimo = buscar_eje_minimo(vector_vuelos,ciudades_visitadas, distancias_a_ciudades, dict_ciudad_vector_distancias);

    //En caso de que la ciudad destino no haya sido visitada, la agrego al dijstra
    ciudades_visitadas.insert(dict_ciudad_vector_distancias[vuelo_minimo.destino]);
    ciudades_no_visitadas.erase(dict_ciudad_vector_distancias[vuelo_minimo.destino]);
    distancias_a_ciudades[dict_ciudad_vector_distancias[vuelo_minimo.destino]] = vuelo_minimo.fin + 2;
    previous[dict_ciudad_vector_distancias[vuelo_minimo.destino]] = vuelo_minimo.orden;

/*    if(ciudades_no_visitadas.find(dict_ciudad_vector_distancias[vuelo_minimo.destino]) != ciudades_no_visitadas.end())
    {
    }*/
  }

  imprimir_previous(previous);
  vector<string> res;
  return res;
}

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
    v.orden = i;
    vector_vuelos.push_back(v);
  }

  matriz_vuelos m = crear_matriz_de_vuelos(vector_vuelos, dict_ciudad_vector_distancias);
  vector <string> resultado = buscar_caminimo_min(it.origen, it.destino, m, dict_ciudad_vector_distancias, vector_vuelos);
  /*imprimir_vector(vector_vuelos);
  imprimir_map(dict_ciudad_vector_distancias);*/
  /*imprimir_matriz(m);*/
  return 0;
}