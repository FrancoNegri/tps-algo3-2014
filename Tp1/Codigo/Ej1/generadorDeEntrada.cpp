#include <iostream> // library that contain basic input/output functions
#include <fstream>  // library that contains file input/output functions
#include <stdlib.h>
#include <cmath> 
using namespace std;

int main(int argc, char *argv[])
{

        ofstream fout("testPeorCaso.txt");
        int n = 500;
        int k = 5;
        for (k = 10; k < 500 ; k+= 10)
        {
                fout << n <<" " << k;
                for(int j = 0; j < n; j++)
                {
                        if(fmod(j,k) == 0)
                                fout << " " << 1;
                        else
                                fout << " " << 0;
                }    
                fout << endl;   
        }
        fout << 0 << endl;
        return 0;
}