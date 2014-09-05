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

bool check_solution(vector<int> puente, int largo_del_salto){
  int contador_de_escalones_rotos_seguidos = 0;
  for (int i = 0; i < puente.size(); ++i)
  {
    if(puente[i] == 1) {
      contador_de_escalones_rotos_seguidos++;
    } else{
      contador_de_escalones_rotos_seguidos = 0;
    } 
    if(contador_de_escalones_rotos_seguidos == largo_del_salto) {
      return false;
    }
  }
  return true;
}

vector<int> obtener_recorrido(vector<int> distancias, int largo_del_salto)
{
  vector<int> recorrido;
  recorrido.push_back(distancias.size() + 1);
  for (int i = (distancias.size()); i > 0;)
  { 

    
    int inicio_del_recorrido = 0;
    int pos_salto = 0;
    if ( i - largo_del_salto < 0) {
      pos_salto = min_element( distancias.begin(), distancias.begin() + i) - distancias.begin();
        
    } else {
        
      pos_salto = min_element( distancias.begin() + i - largo_del_salto, distancias.begin() + i) - distancias.begin();
        
    }

    //cout << "valor: " << distancias[i] << " i: " << i <<  " minimo en: " << pos_salto << "\n";
    i = pos_salto;

    if( i > 0 ) {
      recorrido.push_back(pos_salto + 1);
    }
  }
  return recorrido;
}

int main()
{
  while(true){
    int n, largo_del_salto;
    cin >> n;
    if(n == 0) {
      return 0;
    }

    cin >> largo_del_salto;

    vector<int> puente;
    vector<int> distancias;

    //Creacion del primer elemento artificial con cantidad de saltos 0
    for (int i = 0; i < n; ++i)
    {
      int tablon;
      cin >> tablon;
      puente.push_back(tablon);
      distancias.push_back(INT_MAX) ; //inicializo todo en inf, que para mi es INT_MAX
    }

    //miro si tiene solucion
    if(!check_solution(puente,largo_del_salto)){
    //  cout << "no\n";
      continue;
    }


    if(largo_del_salto > n){
   //   cout << "1 " << n+1 << endl;
      continue;
    }
      auto begin = std::chrono::high_resolution_clock::now();

    //El algoritmo!

    for (int pos_puente = 0; pos_puente < n; ++pos_puente)
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
        //dist_min = *(min_element(distancias.begin() + pos_puente_inf , distancias.begin() + pos_puente));
          bool encontreMin = false;
          int min = pos_puente_inf;
          for(int i = pos_puente_inf; i< pos_puente;i++){
              if(puente[i]!=0){
                  encontreMin = true;
                  min = i;
                  break;
              }
          }
          if(encontreMin)
              dist_min = distancias[min] + 1;
      }
      distancias[pos_puente] = dist_min;
    }
   // vector<int> recorrido = obtener_recorrido(distancias, largo_del_salto);
    //recorrido.push_back(recorrido.size());
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << n << ' ' << std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
    cout << std::endl;

    //std::reverse(recorrido.begin(),recorrido.end());

  //  imprimir_vector(recorrido);
  }
  return 0;
}
