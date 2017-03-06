/*
 */
#include <stdio.h>
#include <iostream>
#include <cassert>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
#define M(k) ((1UL << (k))-1UL)
#define enc(x,y,t) ((x) | ((y) << 5) | ((t) << 7))
#define Q (1 << 9)
#define oo 0xfffffffful

queue<unsigned int> q;
unsigned int d[Q];
int n;

void proce( unsigned int u, unsigned int p ) {
	if ( d[u] > d[p] + 1 )
		d[u] = d[p] + 1, q.push(u);
}

void bfs( unsigned int src, unsigned int dst ) {
	unsigned int u,v,x,y,t;

	memset(d,0xff,sizeof(d));
	q.push( src ), d[src] = 0;
	while ( q.size() && !(d[dst] < +oo) ) {
		u = q.front(), q.pop();
		x = u & M(5), y = (u >> 5) & M(2), t = u >> 7;
		if ( t == 0 ) {
			if ( y == 0 ) {
				if ( x > 0 )
					v = enc(x-1,y,1-t), proce(v,u);
			}
			else if ( y == 1 ) {
				v = enc(x,y-1,1-t), proce(v,u);
				if ( x > 0 )
					v = enc(x-1,y,1-t), proce(v,u);
			}
			else if ( y == 2 ) {
				v = enc(x,y-1,1-t), proce(v,u);
				v = enc(x,y-2,1-t), proce(v,u);
				if ( x > 0 )
					v = enc(x-1,y,1-t), proce(v,u);
			}
		}
		else {
			if ( y == 2 ) {
			}
			else if ( y == 1 ) {
				v = enc(x,y+1,1-t), proce(v,u);
				if ( n-x > 0 )
					v = enc(x+1,y,1-t), proce(v,u);
			}
			else if ( y == 0 ) {
				v = enc(x,y+1,1-t), proce(v,u);
				v = enc(x,y+2,1-t), proce(v,u);
				if ( n-x > 0 )
					v = enc(x+1,y,1-t), proce(v,u);
			}
		}
	}
	printf("%u\n",d[dst] / 2);
}

int main() {
	n = 29;
	bfs(enc(n,2,0),enc(0,2,0));
	return 0;
}

