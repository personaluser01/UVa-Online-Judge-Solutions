#include <cassert>
#include <cmath>
#include <iostream>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
using namespace std;
#define within(x) (1 <= (x) && (x) <= n)

int is[1 << 16],yes;

int free_spot( int x, int *t, int n ) {
	for ( ;within(x) && is[x] != yes; x += *t );
	assert( within(x) );
	return x;
}

int next_to_open( int x, int *t, int n ) {
	int y;
	for ( x += *t; within(x) && is[x] != yes; x += *t );
	y = x;
	if ( !within(x) ) {
		*t = -*t, x += *t;
		return free_spot(x,t,n);
	}
	else {
		for ( x += *t; within(x) && is[x] != yes; x += *t );
		if ( !within(x) ) {
			*t = -*t;
			return y;
		}
		return x;
	}
}

int f( int n ) {
	int i,j,k,x,ax = n,t = 1;
	for ( ++yes, x = 1; x <= n; is[x++] = yes );
	for ( x = 1; ax > 1; ) {
		assert( is[x] == yes );
		is[x] = 0, --ax;
		// printf("x = %d\n",x);
		x = next_to_open(x,&t,n);
	}
	return x;
}

long long F[9],K;
vector<int> v;

int good( unsigned int *u, int n ) {
	int i,j,k;
	for ( i = 0; i < n; ++i ) {
		for ( j = 0, k = 0; j < 4; ++j )
			k += ((u[j]>>i) & 1);
		if ( k != 2 )
			return 0;
	}
	return 1;
}

int H( int k ) {
	if ( k == 0 )
		return 1;
	return H(k-1) + (k/9)+1;
}

int HH( int k ) {
	int m = (k+1)/9;
	return 9*(m-1)*m/2+k+1+(k+1-9*m)*m;
}

int main() {
	int n,i,j,k,t,l,wx;
	double ax,s;
	unsigned int B[0x400];

	B[0] = 1, B[1] = 1;
	for ( i = 2; i < 0x400; ++i ) {
		if ( (B[i] = B[i-1]^(B[i-2]<<1)) == 1 )
			printf("%d\n",i);
		// printf("B[%d] = %u\n",i,B[i] = B[i-1]^(B[i-2]<<1));
	}
	return 0;

	printf("%d %d\n",H(1977),HH(1977));
	return 0;

	for ( wx = 0, i = 1; i <= 6; ++i )
		for ( j = 1; j <= 6; ++j )
			for ( k = 1; k <= 6; ++k )
				for ( t = 1; t <= 6; ++t )
					for ( l = 1; l <= 6; ++l )
						if ( i+j+k+t+l == 20 )
							++wx;
	printf("%d\n",wx);
	return 0;
	

	for ( n = 3; n <= 8; ++n ) {
		int m = n;
		printf("%d\n",(m-2)*(m-1)*(2*m-3)/3 + (m-1) + 3*(m-1)*(m-2)/2);
	}
	return 0;

	for ( n = 2; n <= 4; ++n ) {
		unsigned int u[4],MASK = 1 << n;
		for ( wx = 0, u[0] = 0; u[0] < MASK; ++u[0] )
			for ( u[1] = u[0]+1; u[1] < MASK; ++1[u] )
				for ( u[2] = u[1]+1; u[2] < MASK; ++2[u] )
					for ( u[3] = u[2]+1; u[3] < MASK; ++3[u] )
						if ( good(u,n) )
							++wx;
		printf("%d %d\n",wx,(int)pow(6.0,n));
	}
	return 0;
	for ( F[0] = 1, K = 1; K <= 8; ++K )
		F[K] = F[K-1]*K;
	for ( n = 1; n <= 4; ++n ) {
		v.clear();
		printf("%lld\n",F[2*n]);
		for ( ax = 0, i = 1; i <= 2*n; v.push_back(i++) );
		for ( k = 1; k <= F[2*n]; ++k ) {
			for ( s = 0, i = 0; i <= 2*n-2; i += 2 )
				s += abs(v[i]-v[i+1]);
			ax += s/F[2*n];
			next_permutation(v.begin(),v.end());
		}
		printf("%lf %lf\n",ax,2*n*(2*n+1)/6.0);
	}
	return 0;
}
