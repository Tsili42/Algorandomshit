#include <iostream>
using namespace std;
#include <vector>
#include <cmath>
#include <algorithm>
#include <stdio.h>
#define BSIZE 1<<15

char buffer[BSIZE];
long bpos = 0L, bsize = 0L;

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

struct myTuple{
    int key;
    int pos;
};

bool myComp(myTuple A, myTuple B){ return A.key < B.key; }

int main(int argc, char **argv){

    int N, i, a, b;
    N = readLong();
    vector<myTuple> Hor, Ver;

    for (i = 0; i < N; i++){
        a = readLong();
        b = readLong();
        Hor.push_back(myTuple());
        Ver.push_back(myTuple());

        Ver[i].key = a;
        Ver[i].pos = i;

        Hor[i].key = b;
        Hor[i].pos = i;
    }

    sort(Hor.begin(), Hor.end(), myComp);
    sort(Ver.begin(), Ver.end(), myComp);

    unsigned long long Distance, minD = 100000000000000000;
    vector<unsigned long long> DistH, DistV;
    for (i = 0; i < N; i++){
        DistH.push_back(0);
        DistV.push_back(0);
    }

    for (vector<myTuple>::iterator it = Ver.begin(); it != Ver.end(); it++){
        DistV[Ver[0].pos] += abs(it->key - Ver[0].key);
    }

    Distance = DistV[Ver[0].pos];
    for (vector<myTuple>::iterator it = Ver.begin() + 1; it != Ver.end(); it++){
        DistV[it->pos] = Distance + (it->key - (it-1)->key)*(2*(it-Ver.begin())-N);
        Distance = DistV[it->pos];
    }


    for (vector<myTuple>::iterator it = Hor.begin(); it != Hor.end(); it++){
        DistH[Hor[0].pos] += abs(it->key - Hor[0].key);
    }

    Distance = DistH[Hor[0].pos];
    for (vector<myTuple>::iterator it = Hor.begin() + 1; it != Hor.end(); it++){
        DistH[it->pos] = Distance + (it->key - (it-1)->key)*(2*(it-Hor.begin())-N);
        Distance = DistH[it->pos];
    }

    for (i = 1; i < N; i++){
        Distance = DistH[i] + DistV[i];
        if (Distance < minD) minD = Distance;
    }

    cout << minD << endl;

    return 0;
}
