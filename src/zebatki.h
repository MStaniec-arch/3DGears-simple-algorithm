#include <iostream>
#include <math.h>
using namespace std;

// Przelicza stopnie na radiany
double naRad(double stopnie);

// Generuje tablice punktow dla zebatki
float *genGearPoints(double x, double y, double z, double a, int zb, int *s);

// Generuje tablice trojkatow dla zebatki
unsigned int *genGearTriangles(int zb, int *s);

// Dla dwoch powyzszych:
// x, y, z - wspolzedne srodka zebatki
// a  - dlugosc boku wielokata, ktory jest baza zebatki
// zb - liczba zebow w zebatce
// s - wskaznik na zmienna do zapisu rozmiaru
