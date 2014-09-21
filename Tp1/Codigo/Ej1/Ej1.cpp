#include "Ej1.h"

using namespace std;

void imprimir_vector(list<int> vec)
{
  for ( std::list<int>::iterator it=vec.begin(); it != vec.end(); ++it)
  {
    if((*it) == INT_MAX) {
      cout << "inf ";
    } else if((*it) < 0) {
      continue;
    } else {
      cout << (*it) << " ";
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
		//Creacion del primer elemento artificial con cantidad de saltos 0
		for (int i = 0; i < n; ++i)
		{
		      int tablon;
		      cin >> tablon;
		      puente.push_back(tablon);
		}
		    //miro si tiene solucion
		if(!check_solution(puente,largo_del_salto)){
			cout << "no" << endl;;
			continue;
		}

		if(largo_del_salto > n){
			cout << "1 " << n+1 << endl;
			continue;
		}
		//auto begin = std::chrono::high_resolution_clock::now();
		
	        int posActual = -1; 
		list<int> recorrido;
		bool llegue = false;
		while(!llegue){
			if(posActual + largo_del_salto > n-1){
			       	llegue = true; 
				recorrido.push_back(n+1);
			}else{
				bool encontreEscalon = false;
				int nuevoActual;
				for(int i = posActual + largo_del_salto ; (i > posActual) && !encontreEscalon ;i--){
					if(puente[i]==0){
						encontreEscalon = true;
						recorrido.push_back(i+1);
						nuevoActual = i;
						break;
					}	
				}
				if(nuevoActual > n-1){
					llegue =true;
				}	
				posActual = nuevoActual;	
			}	
	       }
	    //auto end = std::chrono::high_resolution_clock::now();
	   // std::cout << n << ' ' << std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
	   // cout << std::endl;

	    //std::reverse(recorrido.begin(),recorrido.end());
	    imprimir_vector(recorrido);
  }
  return 0;
}
