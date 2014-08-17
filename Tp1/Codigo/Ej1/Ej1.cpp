#include "Ej1.h"

using namespace std;

void imprimir_vector(vector<int> vec)
{
  for (int i = 0; i < vec.size(); ++i)
  {
    if(vec[i] == INT_MAX) {
      cout << "inf ";
    } else if(vec[i] < 0) {
      continue;
    } else {
      cout << vec[i] << " ";  
    }
  }
  cout << "\n";
}

bool check_solution(vector<int> distancias){
  for (int i = 0; i < distancias.size(); ++i)
  {
    if(distancias[i] < 0) {
      return false;
    }
  }
  return true;
}

vector<int> obtener_recorrido(vector<int> distancias, int largo_del_salto)

{
  vector<int> recorrido;
  for (int i = distancias.size() - 1; i > 0;)
  {
    int k;
    if( i - largo_del_salto <= 0){
      k = 0;
    } else {
      k = i - largo_del_salto;
    }

    int pos_salto = min_element(distancias.begin() + k , distancias.begin() + i) - distancias.begin();
    i = pos_salto;
    recorrido.push_back(pos_salto);
  }
  return recorrido;
}

int main()
{
  int n, largo_del_salto;
  cin >> n;
  cin >> largo_del_salto;
  vector<int> puente;
  vector<int> distancias;

  //Creacion del primer elemento artificial con cantidad de saltos 0
/*  distancias.push_back(0);
  puente.push_back(-1);*/

  for (int i = 0; i < n; ++i)
  {
    int tablon;
    cin >> tablon;
    puente.push_back(tablon);
    distancias.push_back(INT_MAX) ; //inicializo todo en inf, que para mi es INT_MAX
  }

  
  //El algoritmo!
  for (int pos_puente = 0; pos_puente < distancias.size(); ++pos_puente)
  {
    //Si el escalon esta roto, lo salteo
    if(puente[pos_puente] != 0) {
      continue;
    }

    //Busco el rango de tablones que puedo pisar
    int pos_puente_inf;
    int dist_min;
    if( pos_puente - largo_del_salto <= 0){
      pos_puente_inf = 0;
      dist_min = 1;
    } else {
      pos_puente_inf = pos_puente - largo_del_salto;
      dist_min = *(min_element(distancias.begin() + pos_puente_inf , distancias.begin() + pos_puente));
      dist_min = dist_min + 1;
    }
    
    distancias[pos_puente] = dist_min;
  }

  cout << "largo del salto: " << largo_del_salto << "\n";
  cout << "puente: ";
  imprimir_vector(puente);

  cout << "distancias: ";
  imprimir_vector(distancias);

  cout << "recorrido: ";
  vector<int> recorrido = obtener_recorrido(distancias, largo_del_salto);
  std::reverse(recorrido.begin(),recorrido.end());

  imprimir_vector(recorrido);
  /*has_result = true;
  if(has_result) {
    cout << "distancias: ";
    imprimir_vector(distancias);  
    //cout << "recorrido: ";
    vector<int> recorrido = obtener_recorrido(distancias, largo_del_salto);
    imprimir_vector(recorrido);
    cout << "\n";
  } else {
    cout << "no" << "\n";
  }*/
  return 0;
}