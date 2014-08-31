#include <iostream> // library that contain basic input/output functions
#include <fstream>  // library that contains file input/output functions
#include <stdlib.h>
using namespace std;

//argumentos que recibe: ruta en la que escribir, n, m
int main(int argc, char *argv[])
{ 
	ofstream fout( "testingPeorCaso/test.txt");
	int n;
	int m;
	n = atoi(argv[1]);
	m = atoi(argv[2]);
	
	if(fout.is_open())
	{
		for(int nueroDeTests = 0; nueroDeTests < 40; nueroDeTests++)
		{
			fout << n << " " << m << endl;
			int valor;
			for(int j = 1; j < n; j++)
			{
				for(int i = j; i < n; i++)
				{
      				valor = rand() % m+9;
      				fout << valor;
      				fout << " ";
				}
				fout << endl;
			}
		}
		fout << "0";		
	}
	else //file could not be opened
	{
		cout << "error!";
	}
	return 0;
}