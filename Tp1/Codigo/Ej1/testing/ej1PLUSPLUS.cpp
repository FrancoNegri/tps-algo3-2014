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
		auto begin = std::chrono::high_resolution_clock::now();
                if(!check_solution(puente,largo_del_salto)){
                        //cout << "no" << endl;;
                        continue;
                }
		// cout << n << " " << largo_del_salto << " ";
		// for(int i = 0 ; i< n ; i++){
		// 	cout << puente[i] << " ";
		// }
		// cout << endl; 
                if(largo_del_salto > n){
                        //cout << "1 " << n+1 << endl;
                        continue;
                }
                
                int posActual = largo_del_salto-1; 
                list<int> recorrido;
                bool llegue = false;
		int iteraciones = 0;
		while(posActual<n&&posActual>=0){
			iteraciones++;
			if(puente[posActual]==0){
				recorrido.push_back(posActual+1); 
				posActual = posActual + largo_del_salto;        
		        }else{
				posActual--;
			}
		}
		recorrido.push_back(n+1);
	     auto end = std::chrono::high_resolution_clock::now();
	    std::cout << n << ' ' << std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
	    cout << std::endl;

	    //imprimir_vector(recorrido);
  }
  return 0;
}
