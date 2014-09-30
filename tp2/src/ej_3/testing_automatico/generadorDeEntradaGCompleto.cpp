#include <iostream> // library that contain basic input/output functions
#include <fstream>  // library that contains file input/output functions
#include <stdlib.h>
using namespace std;

int main(int argc, char *argv[])
{ 
        ofstream fout("testing/test.txt");
        int n;
        int m;
        n = atoi(argv[1]);
        m = n*(n-1)/2;
        if(fout.is_open())
        {
                fout << n << " " << m << endl;
                int enlace1, enlace2, costo;
                for(int j = 0; j < n; j++)
                {
					for(int w = j+1; w < n; w++)
					{
			 			costo = rand() % 100;
                        fout << j+1 << " " << w+1 << " " << " " << costo <<  endl;
					}
               }            
        }
        else //file could not be opened
        {
                cout << "error al intentar escribir el archivo!";
        }
        return 0;
}
