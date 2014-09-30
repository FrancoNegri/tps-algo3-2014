
g++ generadorDeEntrada.cpp -o generador.exe
g++ -std=c++0x ej1PLUSPLUS.cpp -o ej1.exe
./generador.exe
./ej1.exe < testPeorCaso.txt > tests.txt