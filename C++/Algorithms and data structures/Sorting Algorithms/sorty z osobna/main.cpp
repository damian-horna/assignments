#include "header.hpp"

using namespace std;

#define nadpisz "w"
#define dopisz "a"
#define ilosc_obiegow 3
#define ciag 2 // 0 - rosnacy, 1- malejacy, 2- staly, 3-losowy, 4-aksztaltny



int main()
{
    FILE * fp = fopen("mydata.csv", dopisz);
    fprintf(fp,"\n\nHEAPSORT\n\n");
    fprintf(fp,"elementy\trosnacy\tmalejacy\tstaly\tlosowy\taksztaltny\n");
    fclose(fp);

    for(int i=0;i<ilosc_obiegow;i++)
    {
    int n=1000;
    int k;
    printf("Ile liczb: ");
    scanf("%ld",&k);
    int **tab1 = new int*[5];

    for(int i=0; i<5; i++)
    {
        tab1[i] = new int [k];
    }

    srand(time(NULL));

    build_tabs(tab1,n,k);

    printf("Wygenerowano ciągi.\n");

    printf("Sortowanie...\n");
    fp=fopen("mydata.csv",dopisz);
    fprintf(fp,"%d\t%f\t%f\t%f\t%f\t%f\n",k,heapsort(tab1[0],k),heapsort(tab1[1],k),heapsort(tab1[2],k),heapsort(tab1[3],k),heapsort(tab1[4],k));
    fclose(fp);

    for (int i=0; i<5; i++)
    {
        delete tab1[i];
    }
    delete tab1;
    }
    printf("Zakonczono.\n");
    return 0;
    }

