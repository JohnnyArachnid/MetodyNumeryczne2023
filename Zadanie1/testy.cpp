// Autor: Daniel Szarek
//=====================
#include <iostream>
#include <cmath>
#include <chrono>

const double E = 0.0000000001; //Dokladnosc Bledu podana w poleceniu

const long int iteracja = 10000000; //Wartosc iteratora do obliczenia sum obu wzorow

using namespace std;

int main(){
    double suma1 = 0;
    double suma2 = suma1;
    int x = 1;
    auto begin = std::chrono::high_resolution_clock::now(); //Mierzenie czasu dla pierwotnego wzoru
    for(int i=0;i<iteracja;i++){
        suma1+=pow(sin(i*pow(x,4)),2)*exp(-i)+cos(i*pow(x,4))*exp(-4*i); // 1.7 sekund dla 3 prób średnia
    }
    auto end = std::chrono::high_resolution_clock::now(); //Mierzenie czasu dla pierwotnego wzoru
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin); //Mierzenie czasu dla pierwotnego wzoru
    printf("Wartosc sumy dla pierwotnego wzoru: %.9f\n",suma1);
    printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);
    begin = std::chrono::high_resolution_clock::now(); //Mierzenie czasu dla drugiej wersji wzoru
    for(int i=0;i<iteracja;i++){
        suma2+=exp(-i)*(1-cos(i*pow(x,4))*(cos(i*pow(x,4))-exp(-3*i))); //1.3 Sekundy dla 3 prób średnia, bardziej optymalna wersja od pierwotnej
    }
    end = std::chrono::high_resolution_clock::now(); //Mierzenie czasu dla drugiej wersji wzoru
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin); //Mierzenie czasu dla drugiej wersji wzoru
    printf("Wartosc sumy dla zoptymalizowanego wzoru: %.9f\n",suma1);
    printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);
    double pierwsze_wywolanie_funkcji, drugie_wywolanie_funkcji; //Deklaracja f(n) i f(n+1) w celu obliczenia maksymalnego N
    int licznik_iteracji; //Wartosc n
    for(licznik_iteracji=0;licznik_iteracji<=1;licznik_iteracji++) pierwsze_wywolanie_funkcji+=exp(-licznik_iteracji)*(1-cos(licznik_iteracji*pow(1,4))*(cos(licznik_iteracji*pow(1,4))-exp(-3*licznik_iteracji))); //Obliczanie wartosci dla f(1)
    drugie_wywolanie_funkcji = pierwsze_wywolanie_funkcji + exp(-(licznik_iteracji+1))*(1-cos((licznik_iteracji+1)*pow(1,4))*(cos((licznik_iteracji+1)*pow(1,4))-exp(-3*(licznik_iteracji+1)))); //Obliczanie wartosci dla f(2)
    licznik_iteracji++;
    while(fabs(pierwsze_wywolanie_funkcji-drugie_wywolanie_funkcji) > E) { //Wyznaczenie wartosci maksymalnej N
        licznik_iteracji++; // n=n+1
        drugie_wywolanie_funkcji = pierwsze_wywolanie_funkcji; //Obliczanie wartosci dla f(n)
        drugie_wywolanie_funkcji += exp(-licznik_iteracji)*(1-cos(licznik_iteracji*pow(1,4))*(cos(licznik_iteracji*pow(1,4))-exp(-3*licznik_iteracji))); //Obliczanie wartosci dla f(n+1)
    }
    cout<<"Wartosc bledu po maksymalnym N: "<<drugie_wywolanie_funkcji-pierwsze_wywolanie_funkcji<<endl; //Wypisanie wartosci bledu dla maksymalnej N
    cout<<"Wartosc maksymalnego N: "<<licznik_iteracji<<endl; //Wypisanie wartosci maksymalnej N
    return 0;
}