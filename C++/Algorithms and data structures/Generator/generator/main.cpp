#include <stdio.h>
#include<ctime>
#include<cmath>
#include<cstdlib>
#include<fstream>

using namespace std;

int main()
{
    int n;
    long k;

    printf("Jaki ciag wygenerowac?\n1. Rosnacy.\n2. Malejacy.\n3. Staly.\n4. Losowy.\n5. Aksztaltny.\nWybrany ciag: ");
    scanf("%d",&n);
    printf("Ile liczb: ");
    scanf("%ld",&k);

    int *tab;
    tab = new int [k];

    srand(time(NULL));

    switch(n)
    {
    case 1:
        for(int i=0; i<k;i++)
        {
            tab[i] = n;
            n++;
        }
        break;
    case 2:
        for(int i=0; i<k;i++)
        {
            tab[i] = n;
            n--;
        }
        break;
    case 3:
        for(int i=0; i<k;i++)
            tab[i] = n;
        break;
    case 4:
        for(int i=0; i<k;i++)
            tab[i] = (( rand() % 1000) + 1);
        break;
    case 5:
        for(int i=0;i<k/2; i++)
        {
            tab[i] = n;
            n+=2;
        }
        for(int i=k/2;i<k;i++)
        {
            tab[i] = n-1;
            n-=2;
        }
        break;
    }

    fstream file("ciag",ios::out);
    if(file.good())
    {
        file<<k<<" ";
        for(int i=0;i<k;i++)
        {
            file<<tab[i]<<" ";
            file.flush();
        }
        file.close();
    }

    printf("Zmiany zostaly zapisane do pliku.");
    delete [] tab;
    return 0;

}
