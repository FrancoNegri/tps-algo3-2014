#include <sys/time.h>
#include <iostream>
#include <sys/timeb.h>
#include <vector>
#include <stack>
#include <chrono>

using namespace std;


struct Solucion
{
    int peso;
    vector< stack <int> > conjuntos;
};

//definiciones de las funciones q usa el backtracking
int check(vector < vector<int> > &adyacencias, Solucion &solParcial, Solucion &solFinal, int numeroVertice);
//bool tieneCajasVacias(Solucion& sol);
//bool tieneMasBolitasElPredecesor(Solucion& sol);
void inicializarPeorSol(Solucion &sol, int n, vector < vector<int> > &adyacencias);
int calcularPeso(Solucion &sol , vector< vector <int> > &adyacencias );
void imprimirResultado(Solucion &solParcial, int n);
void calcularNuevoPeso(Solucion &sol , int index, int vertice, int signo, vector< vector <int> > &adyacencias );


bool backtracking(Solucion &solParcial, Solucion &solFinal, int numeroVertice, int k, vector < vector< int> > &adyacencias)
{
    int resultCheck;

    resultCheck = check(adyacencias, solParcial, solFinal, numeroVertice);
    //cout << "resultado " << resultCheck << endl;
    //cout << "verticeNumero " << numeroVertice << endl;
    if (resultCheck == 0)
    {
        int peso = calcularPeso(solParcial , adyacencias);
        solParcial.peso = peso;
        if (solParcial.peso < solFinal.peso)
        {
            solFinal = solParcial;
            return true;
        }
        return false;
    }
    if (resultCheck == 2)
        return false;

    for (int i = 0; i < k ; i++)
    {
        calcularNuevoPeso(solParcial, i, numeroVertice, 1, adyacencias);
        solParcial.conjuntos[i].push(numeroVertice);
        //imprimirResultado(solParcial);
        backtracking(solParcial, solFinal, numeroVertice + 1, k, adyacencias);
        calcularNuevoPeso(solParcial, i, numeroVertice, -1, adyacencias);
        solParcial.conjuntos[i].pop();
    }// solo para completar casos, es imposible que se llegue a este punto.
    return false;
}

// check:
// si retorna 0 llegue al final
// si retorna 1, la solucion parcial tiene mas peso no vale la pena seguir calculando
// si retorna 3 la solucion no es mejor tengo q seguir calculando
// si retorna 2 es solucion valida
int check(vector < vector<int> > &adyacencias, Solucion &solParcial, Solucion &solFinal, int numeroVertice)
{
    //no termine de agregar vetices sigo
    if (solParcial.peso > solFinal.peso)
    {
        return 2;
    }

    if (adyacencias.size() == numeroVertice)
    {
        return 0;
    }

    //Podas, si tiene cajas vacias no voy a generar una solucion mejor si no una ya generada al igual que mover bolitas entre cajas sucesoras, abort!
    //if(tieneMasBolitasElPredecesor(solParcial))
    //return 0;
    //if(tieneCajasVacias(solParcial))
    //return 1;
    return 1;
}

//Reviso si mi solucion tiene cajas vacias
/*bool tieneCajasVacias(Solucion& sol){*/
//bool res = false;
//for(int i = 0; i < sol.conjuntos.size();i++ ){
//if(sol.conjuntos[i].size() == 0){
//res = true;
//break;
//}
//}
//return res;
/*}*/

//Reviso si en algun caso estoy teniendo dos cajas seguidas donde la segunda tiene mas bolitas
/*bool tieneMasBolitasElPredecesor(Solucion& sol){*/
//bool res = false;
//int cantidadAnterior = sol.conjuntos[0].size();
//for(int i = 1; i < sol.conjuntos.size();i++ ){
//if(sol.conjuntos[i].size()>cantidadAnterior  ){
//res = true;
//break;
//}else{
//cantidadAnterior = sol.conjuntos[i].size();
//}
//}
//return res;
/*}*/
void imprimirResultado(Solucion &solParcial, int n)
{
    // cout << "peso " << solParcial.peso << endl;
    //     for(int i = 0; i < solParcial.conjuntos.size(); i++)
    //     {
    //  cout << "[";
    //  stack<int> copia = solParcial.conjuntos[i];
    //      while(!copia.empty())
    //  {
    //      cout << copia.top()<< ",";
    //                 copia.pop();
    //      }
    //         cout << "]";
    //     }
    // cout << endl;

    //int n = 10;


    //Version modificada que muestra el resultado acorde a lo que se pide

    vector<int> aux;
    aux.resize(n);

    cout << solParcial.peso << endl;
    // for(int i = 0; i < solParcial.conjuntos.size(); i++)
    // {
    // stack<int> copia = solParcial.conjuntos[i];
    //     while(!copia.empty())
    // {
    //  aux[copia.top()] = i;
    //  copia.pop();
    //     }
    // }

    // for(int i = 0; i < aux.size(); i++)
    //  cout << aux[i] + 1 << " ";
    // cout << endl;

}

void calcularNuevoPeso(Solucion &sol , int index, int vertice, int signo, vector< vector <int> > &adyacencias )
{
    int peso = 0;
    int pesoVertice = 0;
    //agarro el conjunto donde voy a agregar el vertice.
    stack <int> cajaActual = sol.conjuntos[index];
    //calculo el peso del conjunto que deberia restarle al total
    while (!cajaActual.empty())
    {
        stack <int> resto = cajaActual;
        pesoVertice += adyacencias[vertice][cajaActual.top()];
        cajaActual.pop();
    }
    sol.peso += signo * pesoVertice;
}

int calcularPeso(Solucion &sol , vector< vector <int> > &adyacencias )
{
    int peso = 0;
    for (int k = 0; k < sol.conjuntos.size() ; k++)
    {
        //agarro una caja
        stack <int> cajaActual = sol.conjuntos[k];
        while (!cajaActual.empty())
        {
            stack <int> resto = cajaActual;
            while (!resto.empty())
            {
                //cout << cajaActual.top() << "," << resto.top() << endl;
                peso += adyacencias[cajaActual.top()][resto.top()];
                //cout << "peso " << peso<< endl;
                resto.pop();
            }

            cajaActual.pop();
        }
    }
    return peso;
}

void inicializarPeorSol(Solucion &sol, int n, vector < vector<int> > &adyacencias)
{
    stack<int> inicial;
    for (int i = 0; i < n; i++)
        inicial.push(i);
    sol.conjuntos[0] = inicial;
    sol.peso =  calcularPeso(sol, adyacencias);
}

void imprimirAdyacencias(vector < vector <int> > adyacencias)
{

    for (int i = 0 ; i < adyacencias[0].size(); i++)
    {
        for (int j = 0 ; j < adyacencias[0].size(); j++)
        {
            cout << adyacencias[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{

    int n, m, k;
    cin >> n;
    cin >> m;
    cin >> k;


    //PARA MEDIR TIEMPOS
    auto begin = std::chrono::high_resolution_clock::now();
    //PARA MEDIR TIEMPOS


    vector< vector< int> >adyacencias  = vector< vector< int> >(n, vector<int> (n, 0));
    vector< stack< int> > subconjuntos;

    for (int i = 0; i < k; i++)
    {
        stack< int> aux;
        subconjuntos.push_back(aux);
    }


    for (int i = 0; i < m; i++)
    {
        int j, k, p;
        cin >> j;
        cin >> k;
        cin >> p;
        adyacencias[j - 1][k - 1] = p;
        adyacencias[k - 1][j - 1] = p;
    }

    timeval tm1, tm2;
    gettimeofday(&tm1, NULL);
    //while(true){
    Solucion solParcial;
    solParcial.peso = 0;
    solParcial.conjuntos = subconjuntos;
    Solucion solFinal;
    solFinal.conjuntos = subconjuntos;
    inicializarPeorSol(solFinal, n, adyacencias);
    Solucion x;
    //cout << "entre!!" << endl;
    //imprimirAdyacencias(adyacencias);
    //imprimirResultado(solFinal);
    bool sol = backtracking(solParcial, solFinal, 0, k, adyacencias);
    //return sol;







    //PARA MEDIR TIEMPOS
    auto end = std::chrono::high_resolution_clock::now();
    auto tiempo_total = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();

    //PARA MEDIR TIEMPOS







    //cout << n << " ";
    imprimirResultado(solFinal, n);
    cout << tiempo_total << endl;
    //[>solParcial.clear();<]
    //[>solFinal.clear();<]
    //break;
    //}



    return 0;
}
