#include <iostream>
using namespace std;
#include <list>
#include <cmath>
#include <stdio.h>
#define BSIZE 1<<15

char buffer[BSIZE];
long bpos = 0L, bsize = 0L;
//FILE *infile;
long readLong()
{
	long d = 0L, x = 0L;
	char c;

	while (1)  {
		if (bpos >= bsize) {
			bpos = 0;
			if (feof(stdin)) return x;
			bsize = fread(buffer, 1, BSIZE, stdin);
		}
		c = buffer[bpos++];
		if (c >= '0' && c <= '9') { x = x*10 + (c-'0'); d = 1; }
		else if (d == 1) return x;
	}
	return -1;
}

struct par{
    int time;
    int vel;
    int pos;
    par(int t, int v, int p){
        time = t;
        vel = v;
        pos = p;
    }
};

double precision = double(1)/double(1);
int breakSign, prevA = -1, prevB = -1, optVar;
bool flag1, flag2;
list<par>::iterator itemA, itemB;
void calcFirst (list<par> &parA, list<par> &parB, int N, long double Left, long double Right, long double L){
    if (Right < precision + Left){
        cout << itemA->pos << " " << itemB->pos << endl;
        list<par>::const_iterator getA = parA.erase(itemA);
        list<par>::const_iterator getB = parB.erase(itemB);
        return;
    }

    list<par>::iterator it;
    long double mid = (Left+Right)/2;
    long double tkA, tkB, minA = 1000000, minB = 10000000;
    list<par>::iterator minASoFar = parA.begin(), minBSoFar = parB.begin();
    for (it = parA.begin(); it != parA.end(); it++){
        tkA = (mid / (it->vel)) + it->time;
        if (tkA < minA){
            minA = tkA;
            minASoFar = it;
        }
    }

    for (it = parB.begin(); it != parB.end(); it++){
        tkB = ((L-mid) / it->vel) + it->time;
        if (tkB < minB){
            minB = tkB;
            minBSoFar = it;
        }
    }

    if (minA < minB){
        breakSign++;
        if (prevA != minASoFar->pos){
            flag1 = true;
            itemA = minASoFar;
            prevA = itemA->pos;
            breakSign = 1;
        }
        else if (breakSign > optVar && flag2 == true){
            cout << itemA->pos << " " << itemB->pos << endl;
            list<par>::const_iterator getA = parA.erase(itemA);
            list<par>::const_iterator getB = parB.erase(itemB);
            return;
        }
        calcFirst(parA, parB, N, mid, Right, L);
    }
    else {
        breakSign++;
        if (prevB != minBSoFar->pos){
            flag2 = true;
            itemB = minBSoFar;
            prevB = itemB->pos;
            breakSign = 1;
        }
        else if (breakSign > optVar && flag1 == true){
            cout << itemA->pos << " " << itemB->pos << endl;
            list<par>::const_iterator getA = parA.erase(itemA);
            list<par>::const_iterator getB = parB.erase(itemB);
            return;
        }
        calcFirst(parA, parB, N, Left, mid, L);
    }


}

int main(int argc, char **argv){
    int N, K, a, b;
    long double L;
    N = readLong();
    L = readLong();
    K = readLong();

    list<par> parA, parB;
    for (int i = 0; i < N; i++){
        a = readLong();
        b = readLong();
        parA.emplace_front(par(a, b, i+1));
    }

    for (int i = 0; i < N; i++){
        a = readLong();
        b = readLong();
        parB.emplace_front(par(a, b, i+1));
    }

    int initK = K;
    while (K > 0){
        breakSign = 0;
        flag1 = false;
        flag2 = false;

        if (K > initK/3) optVar = 9;
        else optVar = 14;

        calcFirst(parA, parB, N, 0, L, L);
        K--;
    }

    return 0;
}
