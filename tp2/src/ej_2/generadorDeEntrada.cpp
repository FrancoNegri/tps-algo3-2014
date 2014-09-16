#include <iostream> // library that contain basic input/output functions
#include <fstream>  // library that contains file input/output functions
#include <stdlib.h>
using namespace std;

int main(int argc, char *argv[])
{ 
        ofstream fout("testing/test.txt");
        int n;
        int k;
        n = 10;
        k = atoi(argv[1]);
        if(fout.is_open())
        {
                fout << n << " " << k << endl;
                int valor;
                for(int j = 0; j < k; j++)
                {
                        valor = rand() % n + 1;
                        fout << valor;
                        fout << " ";
                        valor = rand() % n + 1;
                        fout << valor;
                        fout << endl;
                }            
        }
        else //file could not be opened
        {
                cout << "error!";
        }
        return 0;
}