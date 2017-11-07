#include <iostream>
using namespace std;
//#include <vector>
#include <list>
#include <cmath>
#include <unordered_set>
#include <stdio.h>
#define BSIZE 1<<15

char buffer[BSIZE];
long bpos = 0L, bsize = 0L;
FILE *infile;
long readLong()
{
	long d = 0L, x = 0L;
	char c;

	while (1)  {
		if (bpos >= bsize) {
			bpos = 0;
			if (feof(infile)) return x;
			bsize = fread(buffer, 1, BSIZE, infile);
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
};

double precision = double(2)/double(1);

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
        //else cout << "Bingo!" << endl;
        tkB = ((L-mid) / it->vel) + it->time;
        if (tkB < minB){
            minB = tkB;
            minBSoFar = it;
        }

        //cout << tkA << " " << tkB << endl;
    }

    //cout << "FuckM: " << minASofar << " " << minBSofar<<endl;

//    cout << "Mistake ahere: " << mid << endl;

    //cout <<"Wanring: " << FstPar << " " << SndPar <<endl;
    if (minA < minB){
        itemA = minASoFar;
        cout << "Space is: " << mid << " " << Right << endl;
        calcFirst(parA, parB, N, mid, Right, L);
    }
    else {
        itemB = minBSoFar;
        cout << "Space is: " << Left << " " << mid << endl;
        calcFirst(parA, parB, N, Left, mid, L);
    }


}

int main(int argc, char **argv){
    int N, K, a, b;
    long double L;
    infile = fopen(argv[1], "r");

    N = readLong();
    L = readLong();
    K = readLong();

    list<par> parA, parB;
    par temp;
    for (int i = 0; i < N; i++){
        a = readLong();
        b = readLong();
        temp.time = a;
        temp.vel = b;
        temp.pos = i + 1;
        parA.emplace_front(temp);
    }

    for (int i = 0; i < N; i++){
        a = readLong();
        b = readLong();
        temp.time = a;
        temp.vel = b;
        temp.pos = i + 1;
        parB.emplace_front(temp);
    }

    while (K > 0){
        calcFirst(parA, parB, N, 0, L, L);
        K--;
    }

    return 0;
}
