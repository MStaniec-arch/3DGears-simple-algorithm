#include <iostream>
#include <math.h>
#include "zebatki.h"
using namespace std;

double naRad(double stopnie)
{
    return (stopnie*M_PI) / 180.0f;
}

// x, y, z - wspolzedne srodka zebatki
// a  - dlugosc boku wielokata, ktory jest baza zebatki
// zb - liczba zebow w zebatce
// s - wskaznik na zmienna do zapisu rozmiaru

// Generuje tablice punktow dla zebatki
float *genGearPoints(double x, double y, double z, double a, int zb, int *s)
{
    int lpnk = lpnk + zb*8 + 2;         // Liczba punktow
    float *punkty = new float[lpnk*8];  // Tablica z danymi
    *s = lpnk*8;                        // Rozmiar tablicy
    //cout << "Rozmiar: " << *s << endl;

    for(int i=0;i<lpnk*8;i++)
    {
        punkty[i] = 0.0;
    }


    // koordynaty: 3, kolory: 3, wspolzedne tekstury: 2
    // Razem: 8

    // Koordynaty
    punkty[0]    = x;
    punkty[1]    = (a/3) + y;
    punkty[2]    = z;

    punkty[lpnk*4]   = x;
    punkty[1+(lpnk*4)] = -(a/3) + y;
    punkty[2+(lpnk*4)] = z;
/*
    cout << "Koordy:" << endl;
    cout << "X:\t" << punkty[0] << endl;
    cout << "Y:\t" << punkty[1] << endl;
    cout << "U:\t" << punkty[6] << endl;
    cout << "V:\t" << punkty[7] << endl;
*/
    int licz = 8;

    double stopnie = 360;
    stopnie = stopnie/(zb*2);
    double alfa = stopnie/2;
    double R1 = (a/2)/sin(naRad(alfa));

    for(int i=0; i<zb*2; i++)
    {
        //cout << i << "\t" << licz << endl;

        // Koordynaty
        punkty[licz]    = x + R1 * cos(naRad(stopnie*i));
        punkty[licz+1]  = (a/3) + y;
        punkty[licz+2]  = z + R1 * sin(naRad(stopnie*i));

        punkty[licz+lpnk*4]    = x + R1 * cos(naRad(stopnie*i));
        punkty[licz+1+(lpnk*4)]  = -(a/3) + y;
        punkty[licz+2+(lpnk*4)]  = z + R1 * sin(naRad(stopnie*i));

        // Tekstura
        punkty[licz+6]  = 0.5 + R1 * cos(naRad(stopnie*i));
        punkty[licz+7]  = 0.5 + R1 * sin(naRad(stopnie*i));

        punkty[licz+6+(lpnk*4)]  = 0.5 + R1 * cos(naRad(stopnie*i));
        punkty[licz+7+(lpnk*4)]  = 0.5 + R1 * sin(naRad(stopnie*i));
/*
        cout << "Koordy:" << endl;
        cout << "X:\t" << punkty[licz] << endl;
        cout << "Y:\t" << punkty[licz+1] << endl;
        cout << "U:\t" << punkty[licz+6] << endl;
        cout << "V:\t" << punkty[licz+7] << endl;
        cout << endl;
*/
        licz = licz + 8;
    }

    double R2 = R1 + a;

    for(int i=0; i<zb; i++)
    {
        // Pomocnicze punkty
        double xp = x + R2 * cos(naRad(alfa+stopnie*i*2));
        double zp = z + R2 * sin(naRad(alfa+stopnie*i*2));
        double xt = 0.5 + R2 * cos(naRad(alfa+stopnie*i*2));
        double zt = 0.5 + R2 * sin(naRad(alfa+stopnie*i*2));

        //cout << i << "\t" << licz << endl;

        // Koordynaty
        punkty[licz]    = xp + a/3 * cos(naRad(alfa-90+stopnie*i*2));
        punkty[licz+1]  = (a/3) + y;
        punkty[licz+2]  = zp + a/3 * sin(naRad(alfa-90+stopnie*i*2));

        punkty[licz+(lpnk*4)]    = xp + a/3 * cos(naRad(alfa-90+stopnie*i*2));
        punkty[licz+1+(lpnk*4)]  = -(a/3) + y;
        punkty[licz+2+(lpnk*4)]  = zp + a/3 * sin(naRad(alfa-90+stopnie*i*2));

        // Tekstura
        punkty[licz+6]  = xt + a/3 * cos(naRad(alfa-90+stopnie*i*2));
        punkty[licz+7]  = zt + a/3 * sin(naRad(alfa-90+stopnie*i*2));

        punkty[licz+6+(lpnk*4)]  = xt + a/3 * cos(naRad(alfa-90+stopnie*i*2));
        punkty[licz+7+(lpnk*4)]  = zt + a/3 * sin(naRad(alfa-90+stopnie*i*2));
/*
        cout << "Koordy:" << endl;
        cout << "X:\t" << punkty[licz] << endl;
        cout << "Y:\t" << punkty[licz+1] << endl;
        cout << "U:\t" << punkty[licz+6] << endl;
        cout << "V:\t" << punkty[licz+7] << endl;
        cout << endl;
*/
        licz = licz + 8;


        //cout << i << "\t" << licz << endl;

        // Koordynaty
        punkty[licz]    = xp + a/3 * cos(naRad(alfa+90+stopnie*i*2));
        punkty[licz+1]  = (a/3) + y;
        punkty[licz+2]  = zp + a/3 * sin(naRad(alfa+90+stopnie*i*2));

        punkty[licz+(lpnk*4)]    = xp + a/3 * cos(naRad(alfa+90+stopnie*i*2));
        punkty[licz+1+(lpnk*4)]  = -(a/3) + y;
        punkty[licz+2+(lpnk*4)]  = zp + a/3 * sin(naRad(alfa+90+stopnie*i*2));

        // Tekstura
        punkty[licz+6]  = xt + a/3 * cos(naRad(alfa-90+stopnie*i*2));
        punkty[licz+7]  = zt + a/3 * sin(naRad(alfa-90+stopnie*i*2));

        punkty[licz+6+(lpnk*4)]  = xt + a/3 * cos(naRad(alfa-90+stopnie*i*2));
        punkty[licz+7+(lpnk*4)]  = zt + a/3 * sin(naRad(alfa-90+stopnie*i*2));
/*
        cout << "Koordy:" << endl;
        cout << "X:\t" << punkty[licz] << endl;
        cout << "Y:\t" << punkty[licz+1] << endl;
        cout << "U:\t" << punkty[licz+6] << endl;
        cout << "V:\t" << punkty[licz+7] << endl;
        cout << endl;
*/
        licz = licz + 8;
    }


    for(int i=0;i<lpnk;i++) // Nie wiem po co to tutaj jest
    {                       // ale proba usuniecia tej petli
                            // powoduje, ze punkty sie nie
    }                       // generuja

    //Debugowanie
    //cout << "Tablica punktow:" << endl;
    for(int i=0;i<lpnk;i++)
    {
        /*cout << i << "\tX: " << punkty[i*8] << endl;
        cout << "\tY: " << punkty[i*8+1] << endl;
        cout << "\tZ: " << punkty[i*8+2] << endl;

        cout << "\tA: " << punkty[i*8+3] << endl;
        cout << "\tB: " << punkty[i*8+4] << endl;
        cout << "\tC: " << punkty[i*8+5] << endl;

        cout << "\tU: " << punkty[i*8+6] << endl;
        cout << "\tV: " << punkty[i*8+7] << endl;
        cout << endl;*/
    }
    /* */

    //punkty[6] = punkty[0] + 0.5;
    //punkty[7] = punkty[1] + 0.5;


    return punkty;
}


// Generuje tablice trojkatow dla zebatki
unsigned int *genGearTriangles(int zb, int *s)
{
    int ltrk = 0;
    ltrk = ltrk + zb*4 + zb*4 + zb*8; // gorna podstawa + dolna podstawa + scianki boczne
    unsigned int *trojkaty = new unsigned int[ltrk*3];

    for(int i=0;i<(ltrk*3);i++)
    {
        trojkaty[i] = 0;
    }

// 1/4 tablicy - gorna podstawa
    int pom = zb * 2;
    for(int i=0;i<zb;i++)   // Tworzy cztery trojkaty na raz
    {
        trojkaty[i*12] = 0;
        trojkaty[i*12+1] = i*2+1;
        trojkaty[i*12+2] = i*2+1+pom;

        trojkaty[i*12+3] = 0;
        trojkaty[i*12+4] = i*2+1+pom;
        trojkaty[i*12+5] = i*2+2+pom;

        trojkaty[i*12+6] = 0;
        trojkaty[i*12+7] = i*2+2+pom;
        trojkaty[i*12+8] = i*2+2;

        trojkaty[i*12+9] = 0;
        trojkaty[i*12+10] = i*2+2;
        trojkaty[i*12+11] = i*2+3;

        trojkaty[i*12+11] = trojkaty[i*12+11] % pom;
    }

// 1/4 tablicy - dolna podstawa
    for(int i=0;i<(zb*4*3);i++) // Kopiuje zawartosc pierwszej czesci
    {
        trojkaty[i+(zb*4*3)] = 1 + (zb*4) + trojkaty[i];
    }

// 2/4 tablicy - œcianki boczne (do poprawki)
    int p=(zb*4+1), q=zb*2;
        // p i q - pomocnicze oznaczające przesuniecia
        // zalezne od ilosci zebow w zebatce
    for(int i=0;i<zb;i++) // Tworzy 8 trojkatow na raz
    {
        trojkaty[i*24 + zb*8*3]    = i*2 + 1;
        trojkaty[i*24 + zb*8*3+1]  = i*2 + 1+p;
        trojkaty[i*24 + zb*8*3+2]  = i*2 + 1+q;

        trojkaty[i*24 + zb*8*3+3]  = i*2 + 1+p;
        trojkaty[i*24 + zb*8*3+4]  = i*2 + 1+q;
        trojkaty[i*24 + zb*8*3+5]  = i*2 + 1+p+q;

        trojkaty[i*24 + zb*8*3+6]  = i*2 + 1+q;
        trojkaty[i*24 + zb*8*3+7]  = i*2 + 2+q;
        trojkaty[i*24 + zb*8*3+8]  = i*2 + 1+q+p;

        trojkaty[i*24 + zb*8*3+9]  = i*2 + 2+q;
        trojkaty[i*24 + zb*8*3+10] = i*2 + 1+q+p;
        trojkaty[i*24 + zb*8*3+11] = i*2 + 2+q+p;

        trojkaty[i*24 + zb*8*3+12] = i*2 + 2+q;
        trojkaty[i*24 + zb*8*3+13] = i*2 + 2;
        trojkaty[i*24 + zb*8*3+14] = i*2 + 2+q+p;

        trojkaty[i*24 + zb*8*3+15] = i*2 + 2;
        trojkaty[i*24 + zb*8*3+16] = i*2 + 2+q+p;
        trojkaty[i*24 + zb*8*3+17] = i*2 + 2+p;

        trojkaty[i*24 + zb*8*3+18] = i*2 + 2;
        trojkaty[i*24 + zb*8*3+19] = i*2 + 3;
        trojkaty[i*24 + zb*8*3+20] = i*2 + 2+p;

        trojkaty[i*24 + zb*8*3+21] = i*2 + 3;
        trojkaty[i*24 + zb*8*3+22] = i*2 + 2+p;
        trojkaty[i*24 + zb*8*3+23] = i*2 + 3+p;
    }
    //zb*8*3 - polowa tablicy

// Korekta ostatnich punktow
    //trojkaty[ltrk*3-6] = 1;
    trojkaty[ltrk*3-5] = 1;
    //trojkaty[ltrk*3-4] = 1;

    trojkaty[ltrk*3-3] = 1;
    //trojkaty[ltrk*3-2] = 1;
    trojkaty[ltrk*3-1] = 1+p;


    // Zwracanie rozmiaru tablicy
    *s = ltrk*3;

    /*// Debugowanie
    cout << "Tablica trojkatow:" << endl;
    for(int i=0;i<ltrk;i++)
    {
        cout << trojkaty[i*3] << "\t";
        cout << trojkaty[i*3+1] << "\t";
        cout << trojkaty[i*3+2] << endl;
    }
    /* */

    return trojkaty;
}
