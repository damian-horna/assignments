#include "header.hpp"

double selsort(int *tab, int param, int n)
{
    bool swapp;
    double time;
    clock_t start, stop;
    if(param==1)
    {
        int minn,temp,index;
        start=clock();
        for(int i=0; i<n; i++)
        {
            swapp=false;
            minn=tab[i];
            for(int j=i+1; j<n; j++)
                if(tab[j]<minn)
                {
                    minn=tab[j];
                    index=j;
                    swapp=true;
                }
            if(swapp)
            {
                temp=tab[i];
                tab[i]=tab[index];
                tab[index]=temp;
            }
        }
        stop=clock();
        time=(double)(stop-start)/(double)CLOCKS_PER_SEC;
        return time;
    }
    else
    {
        int maxx,temp,index;
        start=clock();
        for(int i=0; i<n; i++)
        {
            swapp=false;
            maxx=tab[i];
            for(int j=i+1; j<n; j++)
                if(tab[j]>maxx)
                {
                    maxx=tab[j];
                    index=j;
                    swapp=true;
                }
            if(swapp)
            {
                temp=tab[i];
                tab[i]=tab[index];
                tab[index]=temp;
            }

        }
        stop=clock();
        time=(double)(stop-start)/(double)CLOCKS_PER_SEC;
        return time;
    }
}

double inssort(int *tab, int param, int n)
{

    double time;
    clock_t start, stop;
    int temp;
    if(param==1)
    {
        start=clock();
        for(int i=1; i<n; i++)
        {

            if(tab[i]>=tab[i-1])
                continue;
            else
                for(int j=i; j>=1; j--)
                    if(tab[j]<tab[j-1])
                    {
                        temp=tab[j-1];
                        tab[j-1]=tab[j];
                        tab[j]=temp;
                    }
                    else break;
        }
        stop=clock();
        time=(double)(stop-start)/(double)CLOCKS_PER_SEC;
        return time;
    }
    else
    {
        start=clock();
        for(int i=1; i<n; i++)
        {

            if(tab[i]<=tab[i-1])
                continue;
            else
                for(int j=i; j>=1; j--)
                    if(tab[j]>tab[j-1])
                    {
                        temp=tab[j-1];
                        tab[j-1]=tab[j];
                        tab[j]=temp;
                    }
                    else break;
        }
        stop=clock();
        time=(double)(stop-start)/(double)CLOCKS_PER_SEC;
        return time;
    }
}

double shellsort(int *tab, int param, int n)
{
    double time;
    clock_t start, stop;
    int gap=1,temp;
    if(param==1)
    {

        start = clock();
        gap=calculate_gap(n,gap);
        for(int h=gap; h>=1;)
        {
            for(int k=0; k<h; k++)
                for(int i=k+h; i<n; i+=h)
                    if(tab[i]>=tab[i-h])
                        continue;
                    else
                        for(int j=i; j>=k+h; j-=h)
                            if(tab[j]<tab[j-h])
                            {
                                temp=tab[j-h];
                                tab[j-h]=tab[j];
                                tab[j]=temp;
                            }
                            else break;
            if(h==1)
                break;
            if((h/3)<1)
                h=1;
            else h/=3;
        }
        stop=clock();
        time=(double)(stop-start)/(double)CLOCKS_PER_SEC;
        return time;
    }
    else
    {
        start = clock();
        gap=calculate_gap(n,gap);
        for(int h=gap; h>=1;)
        {
            for(int k=0; k<h; k++)
                for(int i=k+h; i<n; i+=h)
                    if(tab[i]<=tab[i-h])
                        continue;
                    else
                        for(int j=i; j>=k+h; j-=h)
                            if(tab[j]>tab[j-h])
                            {
                                temp=tab[j-h];
                                tab[j-h]=tab[j];
                                tab[j]=temp;
                            }
                            else break;
            if(h==1)
                break;
            if((h/3)<1)
                h=1;
            else h/=3;
        }
        stop=clock();
        time=(double)(stop-start)/(double)CLOCKS_PER_SEC;
        return time;
    }
}
int calculate_gap(int n, int h)
{
    if(h>n)
        if(h/9<1)
            return 1;
        else return h/9;
    h=3*h+1;
    calculate_gap(n,h);
}


void ** build_tabs(int**tab, int n, int k)
{
    for(int i=0; i<k; i++)
    {
        tab[0][i] = n;
        n++;
    }
    n=1000;
    for(int i=0; i<k; i++)
    {
        tab[1][i] = n;
        n--;
    }
    n=1000;
    for(int i=0; i<k; i++)
        tab[2][i] = n;
    n=1000;
    for(int i=0; i<k; i++)
        tab[3][i] = (( rand() % 100000) + 1);

    n=1000;
    for(int i=0; i<k/2; i++)
    {
        tab[4][i] = n;
        n+=2;
    }
    n=1000;
    for(int i=k/2; i<k; i++)
    {
        tab[4][i] = n-1;
        n-=2;
    }
}
double quicksort_time(int tab[], int left, int right)
{
    double time;
    clock_t start, stop;
    start=clock();
    quicksort(tab,left,right);
    stop=clock();
    time=(double)(stop-start)/(double)CLOCKS_PER_SEC;
    return time;
}
double quicksort_random_time(int tab[], int left, int right)
{
    double time;
    clock_t start, stop;
    start=clock();
    quicksort_random(tab,left,right);
    stop=clock();
    time=(double)(stop-start)/(double)CLOCKS_PER_SEC;
    return time;
}
void quicksort( int tab[], int left, int right )
{
    int i = left;
    int j = right;
    int x = tab[left];
    int temp;
    do
    {
        while( tab[ i ] < x )
             i++;

        while( tab[ j ] > x )
             j--;

        if( i <= j )
        {
            temp=tab[i];
            tab[i] = tab[j];
            tab[j]=temp;
            i++;
            j--;
        }
    } while( i <= j );

    if( left < j ) quicksort( tab, left, j );
    if( right > i ) quicksort( tab, i, right );
    return;
}
void quicksort_random( int tab[], int left, int right )
{

    int i = left;
    int j = right;
    int x = tab[(rand()%(right-left))+left];
    int temp;
    do
    {
        while( tab[ i ] < x )
             i++;

        while( tab[ j ] > x )
             j--;

        if( i <= j )
        {
            temp=tab[i];
            tab[i] = tab[j];
            tab[j]=temp;
            i++;
            j--;
        }
    } while( i <= j );

    if( left < j ) quicksort_random( tab, left, j );
    if( right > i ) quicksort_random( tab, i, right );
    return;
}

double heapsort(int *tab, int n)
{
    double time;
    clock_t start, stop;
    start=clock();
    int i;
    for(i = n/2; i >= 1; i--)
    {
        max_heapify(tab, i, n);
    }
    int temp;
    for (i = n; i >= 2; i--)
    {
        temp = tab[i];
        tab[i] = tab[1];
        tab[1] = temp;
        max_heapify(tab, 1, i - 1);
    }
    stop=clock();
    time=(double)(stop-start)/(double)CLOCKS_PER_SEC;
    return time;
}
void max_heapify(int *a, int i, int n)
{
    int j;
    int temp;
    temp = a[i];
    j = 2*i;
    while (j <= n)
    {
        if (j < n && a[j+1] > a[j])
            j = j+1;
        if (temp > a[j])
            break;
        else if (temp <= a[j])
        {
            a[j/2] = a[j];
            j = 2*j;
        }
    }
    a[j/2] = temp;
    return;
}



