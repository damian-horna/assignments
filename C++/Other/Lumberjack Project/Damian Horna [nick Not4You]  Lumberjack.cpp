#include<iostream>
#include<cmath>
#include<cstdio>
#include<ctime>
#include<cstdlib>

using namespace std;

//Classes

class Tree
{
public:

    int x, y, h, d, c, p;
    int val;
    int weight;
    int rvalue;
    int best_cut;
    int state;
    int iftree;

    void add_tree()
    {
        cin>>x>>y>>h>>d>>c>>p;
    }

};

//Global variables

int t, n, k;
int *pk = &k;
int *bx, *by, *b2y, *b2x, *b3y, *b3x, *b4x, *b4y;
int *dir;
int lumb_x = 0,lumb_y = 0;
int **in_range = new int*[10001];
unsigned long long *values;
int **moves;
int pom1;
int war = 1200;
float parameter = 3;
int parameter2 = 85;
int parameter3 = 3000;

//Functions

int fUP(Tree tree, Tree **d);
int fDOWN(Tree tree, Tree **d);
int fLEFT(Tree tree, Tree **d);
int fRIGHT(Tree tree, Tree **d);
int best_val_possible(Tree tree, Tree **d, int *pdir);
int in_the_way(int lumb_x, int lumb_y, int d1x, int d1y, int d2x, int d2y, Tree **d);
void find_best_tree(int **in_range, int lumb_x, int lumb_y, Tree **d, int ile);
void recalculate(Tree &tree, Tree **d, int ile, int **in_range);
void zerosUP(Tree &tree, Tree **d);
void zerosDOWN(Tree &tree, Tree **d);
void zerosRIGHT(Tree &tree, Tree **d);
void zerosLEFT(Tree &tree, Tree **d);


int main()
{
    srand(time(NULL));

    cin>>t>>n>>k;

    if(k < 5000 && t < 1500)
    {
        parameter2 = 250;
        parameter3 = 1000;
    }

    //Arrays

    int inx[10001][2];
    values = new unsigned long long [parameter2];
    moves = new int*[parameter2];
    for (int i = 0; i < 10001; i++)
        in_range[i] = new int [2];
    for(int i = 0; i < parameter2; i++)
        moves[i] = new int [parameter3];
    Tree **d = new Tree*[n + 1];
    for (int i = 0; i < n + 1; i++)
        d[i] = new Tree[n + 1];

    int tim = t;

    Tree pomd;

    for(int i = 0; i < *pk; i++)
    {
        pomd.add_tree();
        pomd.val = pomd.p * pomd.h * pomd.d;
        pomd.weight = pomd.c * pomd.h * pomd.d;
        pomd.best_cut = 1;
        pomd.rvalue = 0;
        pomd.state = 1;
        pomd.iftree = 1;
        d[pomd.x][pomd.y] = pomd;
        inx[i][0] = pomd.x;
        inx[i][1] = pomd.y;
    }

    for(int id = 0; id < parameter2; id++)
    {
        values[id] = 0;
        int nr = 0;

        while(t != 0)
        {
            pom1 = t;
            if(t > war) t = war;

            int ile = 0;
            for(int i = 0; i < k; i++)
            {
                if( d[inx[i][0]][inx[i][1]].state != 0 && ( abs( d[inx[i][0]][inx[i][1]].x - lumb_x ) + abs( d[inx[i][0]][inx[i][1]].y - lumb_y ) + d[inx[i][0]][inx[i][1]].d ) <= t )
                {
                    dir = &d[inx[i][0]][inx[i][1]].best_cut;
                    d[inx[i][0]][inx[i][1]].rvalue = best_val_possible(d[inx[i][0]][inx[i][1]], d, dir);
                    in_range[ile][0] = inx[i][0];
                    in_range[ile][1] = inx[i][1];
                    ile++;
                }
            }

            if (ile == 0)
            {
                while(1)
                {
                    moves[id][nr++] = 3;
                    t--;
                    if (t == 0) break;
                    moves[id][nr++] = 4;
                    t--;
                    if (t == 0) break;
                }
                break;
            }

            int best_x;
            int best_y;
            int best2_x;
            int best2_y;
            int best3_x;
            int best3_y;
            int best4_x;
            int best4_y;

            bx = &best_x;
            by = &best_y;
            b2x = &best2_x;
            b2y = &best2_y;
            b3x = &best3_x;
            b3y = &best3_y;
            b4x = &best4_x;
            b4y = &best4_y;

            find_best_tree(in_range, lumb_x, lumb_y, d, ile);

            switch ( (( rand() % 4 ) + 1) )
            {
            case 2:
                best_x = best2_x;
                best_y = best2_y;
                break;
            case 3:
                best_x = best4_x;
                best_y = best4_y;
                break;
            case 4:
                best_x = best3_x;
                best_y = best3_y;
                break;
            }

            for(int i = 0; i < abs(d[best_x][best_y].x - lumb_x); i++)
            {
                if(d[best_x][best_y].x - lumb_x>0) moves[id][nr++] = 3;
                else moves[id][nr++] = 4;
                t--;
                if (t == 0) break;
            }

            for(int i = 0; i < abs(d[best_x][best_y].y - lumb_y); i++)
            {
                if(d[best_x][best_y].y - lumb_y > 0) moves[id][nr++] = 1;
                else moves[id][nr++] = 2;
                t--;
                if (t == 0) break;
            }

            switch (d[best_x][best_y].best_cut)
            {
            case 1:
                moves[id][nr++] = 5;
                break;
            case 2:
                moves[id][nr++] = 6;
                break;
            case 3:
                moves[id][nr++] = 8;
                break;
            case 4:
                moves[id][nr++] = 7;
                break;
            }

            t = t - d[best_x][best_y].d;
            if (t == 0) break;

            lumb_x = d[best_x][best_y].x;
            lumb_y = d[best_x][best_y].y;

            values[id] += d[best_x][best_y].rvalue;

            recalculate(d[best_x][best_y], d, ile, in_range);

            if(pom1 > war) t = pom1 - (war - t);
        }

         moves[id][nr++] = 321; //end

        lumb_x = 0;
        lumb_y = 0;
        t = tim;

        for(int i = 0; i < k; i++)
        {
            d[inx[i][0]][inx[i][1]].state = 1;
            d[inx[i][0]][inx[i][1]].iftree = 1;
            d[inx[i][0]][inx[i][1]].best_cut = 1;
        }
    }

    unsigned long long best_abc = 0;
    int babc = 0;

    for(int i = 0; i < parameter2; i++)
    {
        if(values[i] > best_abc)
        {
            best_abc = values[i];
            babc = i;
        }
    }

    int indexxx = 0;
    while(1)
    {
        switch(moves[babc][indexxx])
        {
        case 1:
            printf("move up\n");
            break;
        case 2:
            printf("move down\n");
            break;
        case 3:
            printf("move right\n");
            break;
        case 4:
            printf("move left\n");
            break;
        case 5:
            printf("cut up\n");
            break;
        case 6:
            printf("cut down\n");
            break;
        case 7:
            printf("cut right\n");
            break;
        case 8:
            printf("cut left\n");
            break;
        case 321:
            return 0;
        }
        indexxx++;
    }
    return 0;
}

int fUP(Tree tree, Tree **d)
{
    int wartosc = 0;
    int cnt = tree.y + tree.h;
    if (cnt >= n) cnt = n;
    for(int i = tree.y + 1; i <= cnt; i++)
    {
        if(d[tree.x][i].weight < tree.weight && d[tree.x][i].iftree == 1 && d[tree.x][i].state != 0)
            return wartosc = tree.val + fUP(d[tree.x][i], d);
    }
    return tree.val;
}

int fDOWN(Tree tree, Tree **d)
{
    int wartosc = 0;
    int cnt;
    cnt = tree.y - tree.h;
    if (cnt <= 0) cnt = 0;
    for(int i = tree.y - 1; i >= cnt; i--)
    {
        if(d[tree.x][i].weight < tree.weight && d[tree.x][i].iftree == 1 && d[tree.x][i].state != 0)
            return wartosc = tree.val + fDOWN(d[tree.x][i], d);
    }
    return tree.val;
}

int fRIGHT(Tree tree, Tree **d)
{
    if(k == 100)
    {
        int wartosc = 0;
        int cnt = tree.x + tree.h;
        if (cnt >= n) cnt = n;
        for(int i = tree.x + 1; i <= cnt; i++)
        {
            if(d[i][tree.y].weight < tree.weight && d[i][tree.y].iftree == 1 && d[i][tree.y].state != 0 && d[i][tree.y].y <= tree.x + tree.h)
                return wartosc = tree.val + fRIGHT(d[i][tree.y], d);
        }
        return tree.val;
    }

    else
    {
        int wartosc = 0;
        int cnt = tree.x + tree.h;
        if (cnt >= n) cnt = n;
        for(int i = tree.x + 1; i <= cnt; i++)
        {
            if(d[i][tree.y].weight < tree.weight && d[i][tree.y].iftree == 1 && d[i][tree.y].state != 0)
                return wartosc = tree.val + fRIGHT(d[i][tree.y], d);
        }
        return tree.val;
    }
}

int fLEFT(Tree tree, Tree **d)
{
    int wartosc = 0;
    int cnt = tree.x - tree.h;
    if (cnt <= 0) cnt = 0;
    for(int i = tree.x - 1; i >= cnt; i--)
    {
        if(d[i][tree.y].weight < tree.weight && d[i][tree.y].iftree == 1 && d[i][tree.y].state != 0)
            return wartosc = tree.val + fLEFT(d[i][tree.y], d);
    }
    return tree.val;
}

int best_val_possible(Tree tree, Tree **d, int *pdir)
{
    int vUP = fUP(tree, d), vDOWN = fDOWN(tree, d),
        vRIGHT = fRIGHT(tree, d), vLEFT = fLEFT(tree, d);

    int direction;
    int pion = (vUP > vDOWN)? vUP : vDOWN;
    int poziom = (vRIGHT > vLEFT)? vRIGHT : vLEFT;
    int maksimum = (pion > poziom)? pion : poziom;

    if (maksimum == pion && vDOWN - vUP > 0)
        direction = 2;
    else if (maksimum == pion && vUP - vDOWN >= 0)
        direction = 1;
    else if (maksimum == poziom && vLEFT - vRIGHT > 0)
        direction = 3;
    else if (maksimum == poziom && vRIGHT - vLEFT >= 0)
        direction = 4;

    *pdir = direction;
    return maksimum;
}

void find_best_tree(int **in_range, int lumb_x, int lumb_y, Tree **d, int ile)
{
    int quant = ile + 1;
    int counter = 0;

    int **index = new int*[quant];
    for(int i = 0; i < quant; i++)
        index[i] = new int[2];

    float tempx = 0;
    float time1 = 0;
    float time2 = 0;

    if(k < 10000) parameter = 1;

    for(int i = 0; i < ile; i++)
    {
        float czas = abs(d[in_range[i][0]][in_range[i][1]].x - lumb_x) + abs(d[in_range[i][0]][in_range[i][1]].y - lumb_y) + d[in_range[i][0]][in_range[i][1]].d;
        float wynik = d[in_range[i][0]][in_range[i][1]].rvalue / czas;
        if(wynik > tempx && d[in_range[i][0]][in_range[i][1]].state != 0)
        {

            tempx = wynik;
            index[0][0] = in_range[i][0];
            index[0][1] = in_range[i][1];
            counter++;
            if(counter > 0)
            {
                index[counter][0] = index[0][0];
                index[counter][1] = index[0][1];
            }
        }
    }

    *bx = index[0][0];
    *by = index[0][1];
    *b4x = index[0][0];
    *b4y = index[0][1];

    if(counter > 1)
    {
        for(int i = 1; i < counter; i++)
        {
            if(in_the_way(lumb_x, lumb_y, index[0][0], index[0][1], index[i][0], index[i][1], d))
            {
                index[0][0] = index[i][0];
                index[0][1] = index[i][1];

            }
        }
    }

    *b3x = index[0][0];
    *b3y = index[0][1];

    if(counter > 1)
    {
        time1 = abs(d[index[counter - 1][0]][index[counter - 1][1]].x - lumb_x) +
                abs(d[index[counter - 1][0]][index[counter - 1][1]].y - lumb_y) +
                d[index[counter - 1][0]][index[counter - 1][1]].d;

        time2 = abs(d[index[counter][0]][index[counter][1]].x - lumb_x) +
                abs(d[index[counter][0]][index[counter][1]].y - lumb_y) +
                d[index[counter][0]][index[counter][1]].d;

        if(time1 < time2)
            if(time1 < (time2 / parameter))
                if(d[index[counter - 1][0]][index[counter - 1][1]].best_cut == d[index[counter][0]][index[counter][1]].best_cut)
                {
                    index[0][0] = index[counter - 1][0];
                    index[0][1] = index[counter - 1][1];
                }
        *b4x = index[counter - 1][0];
        *b4y = index[counter - 1][1];
    }

    time1 = 0;
    time2 = 0;

    *b2x = index[0][0];
    *b2y = index[0][1];
}

void recalculate(Tree &tree,Tree **d, int ile, int **in_range)
{
    if(tree.best_cut == 1) zerosUP(tree, d);
    if(tree.best_cut == 2) zerosDOWN(tree, d);
    if(tree.best_cut == 4) zerosRIGHT(tree, d);
    if(tree.best_cut == 3) zerosLEFT(tree, d);
    for (int i = 0; i < ile; i++)
    {
        d[in_range[i][0]][in_range[i][1]].rvalue = 0;
    }
}

void zerosUP(Tree &tree, Tree **d)
{
    int cnt = tree.y + tree.h;
    if (cnt >= n) cnt = n;
    for(int i = tree.y + 1; i <= cnt; i++)
    {
        if(d[tree.x][i].weight < tree.weight && d[tree.x][i].iftree == 1 && d[tree.x][i].state != 0)
        {
            d[tree.x][i].state = 0;
            zerosUP(d[tree.x][i], d);
        }
    }
    tree.state = 0;
    return;
}

void zerosDOWN(Tree &tree, Tree **d)
{
    int cnt = tree.y - tree.h;
    if (cnt <= 0) cnt = 0;
    for(int i = tree.y - 1; i >= cnt; i--)
    {
        if(d[tree.x][i].weight < tree.weight && d[tree.x][i].iftree == 1 && d[tree.x][i].state != 0)
        {
            d[tree.x][i].state = 0;
            zerosDOWN(d[tree.x][i], d);
        }
    }
    tree.state = 0;
    return;
}

void zerosRIGHT(Tree &tree, Tree **d)
{
    int cnt = tree.x + tree.h;
    if (cnt >= n) cnt = n;
    for(int i = tree.x + 1; i <= cnt; i++)
    {
        if(d[i][tree.y].weight < tree.weight && d[i][tree.y].iftree == 1 && d[i][tree.y].state != 0)
        {
            d[i][tree.y].state = 0;
            zerosRIGHT(d[i][tree.y], d);
        }
    }
    tree.state = 0;
    return;
}

void zerosLEFT(Tree &tree, Tree **d)
{
    int cnt = tree.x - tree.h;
    if (cnt <= 0) cnt = 0;
    for(int i = tree.x - 1; i >= cnt; i--)
    {
        if(d[i][tree.y].weight < tree.weight && d[i][tree.y].iftree == 1 && d[i][tree.y].state != 0)
        {
            d[i][tree.y].state = 0;
            zerosLEFT(d[i][tree.y], d);
        }
    }
    tree.state = 0;
    return;
}

int in_the_way(int lumb_x, int lumb_y, int d1x, int d1y, int d2x, int d2y, Tree **d)
{
    if(d1x > lumb_x && d1y > lumb_y && d2x > lumb_x && d2y > lumb_y && d2x < d1x && d2y < d1y && d[d2x][d2y].best_cut != 1 && d[d2x][d2y].best_cut != 4) return 1;
    if(d1x < lumb_x && d1y > lumb_y && d2x < lumb_x && d2y > lumb_y && d2x > d1x && d2y < d1y && d[d2x][d2y].best_cut != 1 && d[d2x][d2y].best_cut != 3) return 1;
    if(d1x > lumb_x && d1y < lumb_y && d2x > lumb_x && d2y < lumb_y && d2x < d1x && d2y > d1y && d[d2x][d2y].best_cut != 2 && d[d2x][d2y].best_cut != 4) return 1;
    if(d1x < lumb_x && d1y < lumb_y && d2x < lumb_x && d2y < lumb_y && d2x > d1x && d2y > d1y && d[d2x][d2y].best_cut != 2 && d[d2x][d2y].best_cut != 3) return 1;
    return 0;
}
