// Autor: Daniel Szarek
//=====================
#include <iostream>
#include <cmath>

using namespace std;

int main(){
    double wartosc_funkcji = 0;
    for(int i = 0; i <= 20; i++) {
        double wartosc_cos = cos(i);
        double wartosc_e = exp(-i);
        wartosc_funkcji += wartosc_e*(1-wartosc_cos*(wartosc_cos-(wartosc_e)*(wartosc_e)*(wartosc_e)));
    }
    printf("Wartosc funkcji dla f(1): %.9f\n",wartosc_funkcji);
}