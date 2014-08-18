#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <sys/time.h>
#include <set>

#include    <cstdlib>
#include    <ctime>
#include    <sys/timeb.h>

using namespace std;
unsigned long long operaciones;

struct edificio{
        int id;
        int izq;
        int alt;
        int der;
};



struct sol{
    int x;
    int alt;
};

bool operator <(const edificio& a, const edificio& b){
  return a.alt < b.alt;
}
vector<sol> resolver(int cantEdificios, edificio* edificiosIzq, edificio* edificiosDer);


void merge(edificio*,edificio*,int,int,int,int);
void mergesort(edificio *a,edificio *b, int low, int high,int control)
{

	int pivot;
    if(low<high)
    {
		pivot=(low+high)/2;
        mergesort(a,b,low,pivot,control);
        mergesort(a,b,pivot+1,high,control);
        merge(a,b,low,pivot,high,control);
    }
}
void merge(edificio *a,edificio *b, int low, int pivot, int high,int control)
{
    int k;
    int h=low;
    int i=low;
    int j=pivot+1;
    int elemento_h;
    int elemento_j;
    while((h<=pivot)&&(j<=high))
    {
      if(control == 0){
        elemento_h = a[h].izq;
        elemento_j = a[j].izq;
      }else{
        elemento_h = a[h].der;
        elemento_j = a[j].der;
      }

        if( elemento_h < elemento_j  )
        {
            b[i]=a[h];
            h++;
        }else{
            b[i]=a[j];
            j++;
        }
        i++;
    }
    if(h>pivot)
    {
        for(k=j; k<=high; k++)
        {
            b[i]=a[k];
            i++;
        }
    }else{
        for(k=h; k<=pivot; k++)
        {
            b[i]=a[k];
            i++;
        }
    }
    for(k=low; k<=high; k++) {
                a[k]=b[k];
    }
}


/*
unsigned long long int ordenaredificios(edificio* edificios, int cantEdificios){

        unsigned long long int perdida = 0;

        edificio* auxiliarParaOrdenar = new edificio[cantEdificios];

        operaciones += cantEdificios+1;

        mergesort(edificios,auxiliarParaOrdenar,0, cantEdificios-1);

        //Guardo la sumatoria de los di para evitar calcularla varias veces
        unsigned long long int sumatoriaCostos = 0;
        for(int k = 0; k<cantEdificios ; k++)
                sumatoriaCostos += edificios[k].costo;


        for(int k = 0;k<cantEdificios;k++){
        //SUM di * tk  para la joya k la perdida es la suma de los di por el tiempo de construccion de la joya k
        perdida += sumatoriaCostos * edificios[k].tiempo;
        //resto a la suma de los di la joya que se construyo
        //Sum di - dk para sacar la que ya construi
        sumatoriaCostos -= edificios[k].costo;
    }
        return perdida;

}

*/


vector< sol > resolver(int cantEdificios, edificio* edificiosIzq, edificio* edificiosDer){
  vector<sol> res;
  //ordernar por izq
  edificio* auxiliarParaOrdenar = new edificio[cantEdificios];

  mergesort(edificiosIzq,auxiliarParaOrdenar,0, cantEdificios-1,0);

  //SOlo para test
    cout << "orden por izq \n";
    for(int i = 0; i<cantEdificios; i++){
      cout <<"( " << edificiosIzq[i].id  << "," ;
      cout << edificiosIzq[i].izq  << ",";
      cout << edificiosIzq[i].alt  << ",";
      cout << edificiosIzq[i].der  << ");";

    }
    cout << "\n";
  //FIN TEST


  //ordenar por derecha
  mergesort(edificiosDer,auxiliarParaOrdenar,0, cantEdificios-1,1);

  //Solo para test
    cout << "orden por der \n";
    for(int i = 0; i<cantEdificios; i++){
      cout <<"( " << edificiosDer[i].id  << ",";
      cout << edificiosDer[i].izq  << ",";
      cout <<  edificiosDer[i].alt  << ",";
      cout << edificiosDer[i].der  << ");";
    }
    cout << "\n";
  //FIN TEST

  multiset<edificio> magiheap;
  int posDer = 0;
  int posIzq =0;
  edificio max = {0,0,0,0};
  int posMax = 0;
/*
//Busco mi primer salto
  int actual = 1 ;

  while( edificiosIzq[actual].izq == max.izq ){
    if(edificiosIzq[actual].alt >max.alt){
      posMax = actual;
      max = edificiosIzq[actual];
    }
    actual++;
  }
  max = *(magiheap.insert(edificiosIzq[posMax]));
  sol nueva = {max.izq,max.alt};
  res.push_back(nueva);
  posIzq++;
*/
  sol nueva = {0,0};
  bool finIzq = false;
  while(posDer != cantEdificios){
        if((finIzq) || (edificiosIzq[posIzq].izq > edificiosDer[posDer].der)){
          //Saco edificio o edificios
          int base = posDer;
          int maxAnt = max.alt;
          while ((edificiosDer[posDer].der == edificiosDer[base].der) && (posDer != cantEdificios)){
            multiset<edificio>::iterator it = magiheap.lower_bound(edificiosDer[posDer]);
            if (it->id == max.id){
              if(magiheap.begin()!=it){
              it--;
              max = *(it);
              }else{
              max.id = 0;
              max.izq = 0;
              max.alt = 0;
              max.der = 0;
              }           
            }
            magiheap.erase(edificiosDer[posDer]);
            posDer++;
          }
          if (maxAnt > max.alt){
              nueva.x = edificiosDer[base].der;
              nueva.alt = max.alt;
              res.push_back(nueva);
          }
        }else{
          //Agrego edificio o edificios
          int base = posIzq;
          int maxAnt = max.alt;
          while ((edificiosIzq[posIzq].izq == edificiosIzq[base].izq) && (posIzq != cantEdificios)){
            edificio nuevoEdi = *(magiheap.insert(edificiosIzq[posIzq]));
            if (nuevoEdi.alt > max.alt){
              max = nuevoEdi;
            }
            posIzq++;
          }
          if (maxAnt < max.alt){
              nueva.x = max.izq;
              nueva.alt = max.alt;
              res.push_back(nueva);
          }
          if (posIzq==cantEdificios){
            finIzq = true;
          }
        }
  }

  cout << "Resultado \n";
  for(int i = 0; i < res.size();i++){
    cout << "(" << res[i].x << ",";
    cout << res[i].alt  << ");" ;
  }
  cout << "\n";
  return res;

}


int main(int argc, char *argv[]){

        string line;
        bool primerLinea = true; //para saber cuando tomamos la primera linea, el n.
        int cantEdificios = 0;
        edificio* edificiosIzq = NULL;
        edificio* edificiosDer = NULL;
        int leidas = 1;
        //Si no llegue al final del archivo y sigo obteniendo lineas sigo guardando
        while ( getline (cin,line) )
        {
            if(line[0] == '0'){
              break;
            }

            if(primerLinea){
              cantEdificios = atoi(line.c_str()); //El n de la entrada
              edificiosIzq = new edificio[cantEdificios];
              edificiosDer = new edificio[cantEdificios];
              primerLinea = false;
              leidas = 1;
            }else{


              vector<string> entradaSplit;
              int fromIndex = 0;//inicio string
              int length = 0; //longitud string
              for(int i = 0; i<line.length();i++ ){
                    if(i== line.length()-1){
                      length++;
                      entradaSplit.push_back(line.substr(fromIndex, length));
                    }else if(line[i]== ' '){
                      entradaSplit.push_back(line.substr(fromIndex, length));
                      fromIndex = i+1;
                      length = 0;
                    }else{
                      length++;
                    }
                }//Fin for

                int izq = atoi(entradaSplit[0].c_str());
                int alt = atoi(entradaSplit[1].c_str());
                int der = atoi(entradaSplit[2].c_str());
                edificio nueva = {leidas,izq,alt,der};
                //cout << nueva.id << " " << nueva.izq << " ";
                //cout << nueva.alt << " " << nueva.der << "\n";
                edificiosIzq[leidas-1]=nueva;
                edificiosDer[leidas-1]=nueva;

                if(leidas == cantEdificios){
                  primerLinea = true;
                  //Aca llamamos a resolver
  /*                cout << "edificiios izq \n";
                  for(int i = 0; i<cantEdificios;i++){
                      cout << edificiosIzq[i].id << " " << edificiosIzq[i].izq << " ";
                      cout <<  edificiosIzq[i].alt << " " <<  edificiosIzq[i].der << "\n";
                  }

                  multiset<edificio> test;
                  cout << "multiset \n" ;
                  for(int i =0;i<cantEdificios;i++){
                    test.insert(edificiosIzq[i]);
                  }

                  for(multiset<edificio>::iterator it= test.begin();it!=test.end();it++){
                   cout<< (*it).alt << " " ;
                  }
                  cout << "\n";
                  cout << "edificios : ";
                  cout << edificiosIzq[0].id << "\n";

                  multiset<edificio>::iterator altura = test.lower_bound(edificiosIzq[6]);
                  altura--;
                  cout << "lower 64: " << (*altura).alt ;
                  cout << "\n";
*/
                  vector<sol> resultado = resolver(cantEdificios,edificiosIzq,edificiosDer);

                }

                leidas++;

              }
            }



        return 0;

}
