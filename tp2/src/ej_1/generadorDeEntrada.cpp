#include <iostream> // library that contain basic input/output functions
#include <fstream>  // library that contains file input/output functions
#include <stdlib.h>
using namespace std;

int main(int argc, char *argv[])
{
        char ciudades[] = {'a','b','c','d','q','e','t','y','u','o','r','l','m','z'};
        ofstream fout("testing/test.txt");
        int n;
        n = atoi(argv[1]);

        if(fout.is_open())
        {
                fout << "a b " << n << endl;
                int valor;
                for(int j = 0; j < n; j++)
                {
                        fout << ciudades[rand() %14] << " ";
                        fout << ciudades[rand() %14] << " ";
                        valor = rand() % 100 + 1;
                        fout << valor << " ";
                        valor = rand() % 100 + 1;
                        fout << valor << endl;
                }            
        }
        else //file could not be opened
        {
                cout << "error!";
        }
        return 0;
}