/*
 * 242. Stamps
 * tOPIC: dp, coin change
 * status: Accepted
 */
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#define S 0x10
#define N 0x80
#define Q 0x400
using namespace std;

int ts,n;
bool z[S][S][Q];

typedef struct {
	int len,*x,coverage;
} nb;


bool operator < ( const nb &a, const nb &b ) {
	if ( a.coverage < b.coverage ) 
		return false;
	if ( a.coverage > b.coverage )
		return true;
	if ( a.len == b.len ) {
		for ( int i = a.len-1; i >= 0; --i )
			if ( a.x[i] != b.x[i] ) {
				return a.x[i] < b.x[i];
			}
		return false;
	}
	return a.len < b.len;
}

vector<nb> v;
int is[Q],ys;

int main() {
	int i,j,k,m,l,e;
	nb *a;
	while ( 1 == scanf("%d",&ts) && ts > 0 ) {
		scanf("%d",&n), v.clear();
		for ( i = 0; i < n; ++i ) {
			scanf("%d",&m);
			a = (nb *)malloc(sizeof *a);
			a->len = m;
			a->x = (int *)malloc(m*sizeof *(a->x));
			for ( j = 0; j < m; ++j ) 
				scanf("%d",&a->x[j]);
			v.push_back(*a);
			for ( j = 0; j <= ts; ++j )
				for ( k = 0; k < Q; ++k )
					for ( l = 0; l <= m; ++l )
						z[l][j][k] = false;
			for ( z[0][0][0] = true, l = 1; l <= m; ++l )
				for ( k = 0; k < Q; ++k )
					for ( j = 0; j <= ts; ++j )
						if ( z[l-1][j][k] )
							for ( e = 0; e+j <= ts; ++e )
								if ( e*v[i].x[l-1]+k < Q )
									z[l][e+j][e*v[i].x[l-1]+k] = true;
			for ( ++ys, k = 0; k < Q; ++k )
				for ( j = 0; j <= ts; ++j )
					if ( z[m][j][k] ) is[k] = ys;
			for ( k = 0; k < Q && is[k] == ys; ++k );
			v[i].coverage = k-1;
		}
		sort(v.begin(),v.end());
		printf("max coverage = %3d :",v[0].coverage);
		for ( i = 0; i < v[0].len; ++i )
			printf(" %2d",v[0].x[i]);
		putchar('\n');
	}
	return 0;
}

