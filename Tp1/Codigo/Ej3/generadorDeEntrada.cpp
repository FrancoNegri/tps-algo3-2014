#include <iostream> // library that contain basic input/output functions
#include <fstream>  // library that contains file input/output functions
#include <stdlib.h>
using namespace std;

int main(int argc, char *argv[])
{ 
	ofstream fout("test.txt");
	int n;
	int m;
	m = 10;
	n = atoi(argv[1]);
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